#include <catch2/catch_test_macros.hpp>
#include "geometry/ray.h"
#include "test_helpers.h"

TEST_CASE("Ray getters return origin and direction", "[ray]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(3.0, 4.0, 0.0));

    requireVectorsEqual(ray.origin(), Vector(1.0, 2.0, 3.0));
    requireVectorsEqual(ray.direction(), Vector(3.0, 4.0, 0.0));
}

TEST_CASE("Ray::at(0) returns the origin", "[ray]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(3.0, 4.0, 0.0));

    requireVectorsEqual(ray.at(0.0), Vector(1.0, 2.0, 3.0));
}

TEST_CASE("Ray::at(t) returns origin + t * direction", "[ray]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(3.0, 4.0, 0.0));

    requireVectorsEqual(ray.at(2.0), Vector(7.0, 10.0, 3.0));
}
