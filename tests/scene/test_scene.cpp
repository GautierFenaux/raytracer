#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "scene/scene.h"
#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

static const double tolerance = 1e-9;
static const Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));

// The ray hits the sphere centred at (0,0,9), radius 5, at t = 5.
// A wall facing the camera at z = 2 is hit at t = 3 (in front of the sphere);
// one at z = 20 is hit at t = 21 (behind it).
// Each case is tested in both orders: a "first hit found" bug would pass one order only.
static const Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

TEST_CASE("Scene: wall in front of the sphere wins, sphere added first", "[scene]") {
    FlatShader red(Colour(1.0, 0.0, 0.0)), blue(Colour(0.0, 0.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, &red));
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 2.0), Vector(0.0, 0.0, -1.0), &blue));

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(3.0, tolerance));
    REQUIRE(hit->material == &blue);
}

TEST_CASE("Scene: wall in front of the sphere wins, wall added first", "[scene]") {
    FlatShader red(Colour(1.0, 0.0, 0.0)), blue(Colour(0.0, 0.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 2.0), Vector(0.0, 0.0, -1.0), &blue));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, &red));

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(3.0, tolerance));
    REQUIRE(hit->material == &blue);
}

TEST_CASE("Scene: sphere in front of the wall wins, sphere added first", "[scene]") {
    FlatShader red(Colour(1.0, 0.0, 0.0)), blue(Colour(0.0, 0.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, &red));
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 20.0), Vector(0.0, 0.0, -1.0), &blue));

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5.0, tolerance));
    REQUIRE(hit->material == &red);
}

TEST_CASE("Scene: sphere in front of the wall wins, wall added first", "[scene]") {
    FlatShader red(Colour(1.0, 0.0, 0.0)), blue(Colour(0.0, 0.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 20.0), Vector(0.0, 0.0, -1.0), &blue));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, &red));

    std::optional<Hit> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5.0, tolerance));
    REQUIRE(hit->material == &red);
}

TEST_CASE("Scene: ray missing every shape returns no hit", "[scene]") {
    FlatShader red(Colour(1.0, 0.0, 0.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(6.0, 0.0, 9.0), 5.0, &red));

    REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}

TEST_CASE("Scene: empty scene returns no hit", "[scene]") {
    Scene scene(light);

    REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}
