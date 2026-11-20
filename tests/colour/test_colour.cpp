#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "colour/colour.h"

static const double tolerance = 1e-9;

TEST_CASE("Colour getters return r, g, b", "[colour]") {
    Colour colour(1.0, 0.5, 0.25);

    REQUIRE_THAT(colour.r(), Catch::Matchers::WithinAbs(1.0,  tolerance));
    REQUIRE_THAT(colour.g(), Catch::Matchers::WithinAbs(0.5,  tolerance));
    REQUIRE_THAT(colour.b(), Catch::Matchers::WithinAbs(0.25, tolerance));
}

TEST_CASE("Colour * scalar scales each component", "[colour]") {
    Colour colour = Colour(1.0, 0.5, 0.25) * 0.5;

    REQUIRE_THAT(colour.r(), Catch::Matchers::WithinAbs(0.5,   tolerance));
    REQUIRE_THAT(colour.g(), Catch::Matchers::WithinAbs(0.25,  tolerance));
    REQUIRE_THAT(colour.b(), Catch::Matchers::WithinAbs(0.125, tolerance));
}

TEST_CASE("Colour * Colour multiplies component-wise", "[colour]") {
    Colour colour = Colour(1.0, 0.5, 0.25) * Colour(0.5, 1.0, 0.0);

    REQUIRE_THAT(colour.r(), Catch::Matchers::WithinAbs(0.5, tolerance));
    REQUIRE_THAT(colour.g(), Catch::Matchers::WithinAbs(0.5, tolerance));
    REQUIRE_THAT(colour.b(), Catch::Matchers::WithinAbs(0.0, tolerance));
}
