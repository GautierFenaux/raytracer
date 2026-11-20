#include <catch2/catch_test_macros.hpp>
#include "render/camera.h"
#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "light/light.h"
#include "test_helpers.h"

TEST_CASE("rayThroughPixel: center pixel has direction (0,0,1)", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(0.0, 0.0, 1.0));
}

TEST_CASE("rayThroughPixel: top-right pixel has direction (2,1,1)", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(2.0, 1.0, 1.0));
}

TEST_CASE("rayThroughPixel: bottom-left pixel has direction (-2,-1,1)", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(-2.0, -1.0, 1.0));
}

TEST_CASE("rayThroughPixel: top-right pixel with small pixel size (512x256 image, screen width 2)", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 2.0);
    Ray ray = camera.rayThroughPixel(511, 0, 512, 256);

    // pixelSize = 2/512 = 1/256
    // x = (511.5 - 256) / 256 = 511/512
    // y = -(0.5 - 128) / 256 = 255/512
    requireVectorsEqual(ray.direction(), Vector(511.0/512.0, 255.0/512.0, 1.0));
}

// Shared by the trace tests: the camera ray straight ahead, along +z
static const Ray straightAhead(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

TEST_CASE("trace: hit is shaded by the material with the scene light", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    LambertShader red(Colour(1.0, 0.0, 0.0));
    // The ray hits (0,0,4) with normal (0,0,-1). The light at (6,0,-4) is in
    // direction (0.6,0,-0.8) from there, so N.L = 0.8
    Scene scene(Light(Vector(6.0, 0.0, -4.0), Colour(1.0, 1.0, 1.0)));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, &red));

    requireColoursEqual(camera.trace(straightAhead, scene), Colour(0.8, 0.0, 0.0));
}

TEST_CASE("trace: ray missing everything is black", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    FlatShader red(Colour(1.0, 0.0, 0.0));
    Scene scene(Light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0)));
    scene.add(std::make_unique<Sphere>(Vector(6.0, 0.0, 9.0), 5.0, &red));

    requireColoursEqual(camera.trace(straightAhead, scene), Colour(0.0, 0.0, 0.0));
}

TEST_CASE("trace: uses the material of the nearest shape", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    FlatShader red(Colour(1.0, 0.0, 0.0)), blue(Colour(0.0, 0.0, 1.0));
    Scene scene(Light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0)));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, &red));
    // Wall at z = 2, in front of the sphere
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 2.0), Vector(0.0, 0.0, -1.0), &blue));

    requireColoursEqual(camera.trace(straightAhead, scene), Colour(0.0, 0.0, 1.0));
}

TEST_CASE("render: pixels hitting the sphere are shaded, others stay black", "[camera]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Scene scene(Light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0)));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 1.0, &material));
    Image image(5, 3);

    camera.render(scene, image);

    // Center pixel ray (0,0,1) hits the sphere
    requireColoursEqual(image.pixel(2, 1), Colour(1.0, 0.0, 0.0));
    // Top-right pixel ray (2,1,1) misses the sphere
    requireColoursEqual(image.pixel(4, 0), Colour(0.0, 0.0, 0.0));
}
