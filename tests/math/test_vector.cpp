#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "math/vector.h"

TEST_CASE("Vector::operator+", "[vector]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);
    Vector result = a + b;

    REQUIRE(result.x() == Catch::Approx(5.0));
    REQUIRE(result.y() == Catch::Approx(7.0));
    REQUIRE(result.z() == Catch::Approx(9.0));
}

TEST_CASE("Vector::operator*", "[vector]") {
    Vector a(3.0, 4.0, 0.0);
    Vector result = a * -2.0;

    REQUIRE(result.x() == Catch::Approx(-6.0));
    REQUIRE(result.y() == Catch::Approx(-8.0));
    REQUIRE(result.z() == Catch::Approx(0.0));
}

TEST_CASE("Vector::operator-", "[vector]") {
    Vector a(-1.0, 4.0, 0.0);
    Vector b(-5.0, 2.0, 1.0);
    Vector result = a - b;

    REQUIRE(result.x() == Catch::Approx(4.0));
    REQUIRE(result.y() == Catch::Approx(2.0));
    REQUIRE(result.z() == Catch::Approx(-1.0));
}

TEST_CASE("Vector::normalised produces a unit vector", "[vector]") {
    Vector a(3.0, 4.0, 0.0);
    Vector result = a.normalised();

    REQUIRE(result.x() == Catch::Approx(3.0 / 5.0));
    REQUIRE(result.y() == Catch::Approx(4.0 / 5.0));
    REQUIRE(result.z() == Catch::Approx(0.0));
}
