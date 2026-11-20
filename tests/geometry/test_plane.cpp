#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

static const double tolerance = 1e-9;

TEST_CASE("Plane: ray going down hits the floor", "[plane]") {
    FlatShader material(Colour(0.0, 1.0, 0.0));
    Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), &material);

    // n.D = -4, n.(P - O) = -8, so t = 2 and the point is (0,8,0) + 2*(3,-4,0)
    Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, -4.0, 0.0));
    std::optional<Hit> hit = floor.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(2.0, tolerance));
    requireVectorsEqual(hit->point, Vector(6.0, 0.0, 0.0));
    requireVectorsEqual(hit->normal, Vector(0.0, 1.0, 0.0));
    REQUIRE(hit->material == &material);
}

TEST_CASE("Plane: tilted plane returns a normalised normal", "[plane]") {
    FlatShader material(Colour(0.0, 1.0, 0.0));
    // The plane 3x + 4y = 24, given with a non-unit normal
    Plane plane(Vector(8.0, 0.0, 0.0), Vector(3.0, 4.0, 0.0), &material);

    // n = (0.6, 0.8, 0): n.D = 4.8, n.(P - O) = 9.6, so t = 2
    Ray ray(Vector(-8.0, 0.0, 0.0), Vector(4.0, 3.0, 0.0));
    std::optional<Hit> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, Catch::Matchers::WithinAbs(2.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0.0, 6.0, 0.0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0.0));
}

TEST_CASE("Plane: ray parallel to the plane returns no hit", "[plane]") {
    FlatShader material(Colour(0.0, 1.0, 0.0));
    Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), &material);

    Ray ray(Vector(0.0, 8.0, 0.0), Vector(5.0, 0.0, 0.0));

    REQUIRE_FALSE(floor.hit(ray).has_value());
}

TEST_CASE("Plane: plane behind the ray returns no hit", "[plane]") {
    FlatShader material(Colour(0.0, 1.0, 0.0));
    Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), &material);

    // Going up, away from the floor: t would be -2
    Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, 4.0, 0.0));

    REQUIRE_FALSE(floor.hit(ray).has_value());
}
