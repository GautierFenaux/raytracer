#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

static const double tolerance = 1e-9;

TEST_CASE("Sphere getters return center, radius and material", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, &material);

    requireVectorsEqual(sphere.center(), Vector(0.0, 0.0, 9.0));
    REQUIRE_THAT(sphere.radius(), Catch::Matchers::WithinAbs(5.0, tolerance));
    REQUIRE(sphere.material() == &material);
}

TEST_CASE("Sphere at (0,0,9) radius 5: ray hit returns closest point, normal and material", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, &material);

    // Solutions t = 5 and t = 15: the closest is t = 5, at (0,0,4)
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 4.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 0.0, -1.0));
    REQUIRE(hit->material == &material);
}

TEST_CASE("Sphere at (10,0,9) radius 5: ray miss returns no hit", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(10.0, 0.0, 9.0), 5.0, &material);

    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere at (0,0,-20) radius 5: sphere behind ray returns no hit", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(0.0, 0.0, -20.0), 5.0, &material);

    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("Sphere at (5,0,9) radius 5: tangent ray hits at the edge", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(5.0, 0.0, 9.0), 5.0, &material);

    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));
    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(10.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 9.0));
    requireVectorsEqual(hit->normal, Vector(-1.0, 0.0, 0.0));
}

TEST_CASE("Sphere: ray starting inside uses the intersection in front", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, &material);

    // Solutions t = -5 and t = 5: only t = 5 is in front of the ray
    Ray ray(Vector(0.0, 0.0, 9.0), Vector(0.0, 0.0, 1.0));
    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(5.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 14.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 0.0, 1.0));
}

TEST_CASE("Sphere: hit point is correct for a non-unit ray direction", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, &material);

    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 2.0));
    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(2.5, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 4.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 0.0, -1.0));
}

TEST_CASE("Sphere: ray starting on the surface does not hit itself at t = 0", "[sphere]") {
    FlatShader material(Colour(1.0, 0.0, 0.0));
    Sphere sphere(Vector(0.0, 0.0, 9.0), 5.0, &material);

    // Solutions t = 0 (the origin itself) and t = 10: only t = 10 counts
    Ray ray(Vector(0.0, 0.0, 4.0), Vector(0.0, 0.0, 1.0));
    std::optional<Hit> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(10.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 0.0, 14.0));
}
