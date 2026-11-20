#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "material/lambert_shader.h"
#include "geometry/hit.h"
#include "light/light.h"
#include "test_helpers.h"

static const Colour white(1.0, 1.0, 1.0);

TEST_CASE("LambertShader: light along the normal gives full surface colour", "[shader]") {
    LambertShader shader(Colour(1.0, 0.5, 0.25));
    Hit hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), white);

    requireColoursEqual(shader.shade(hit, light), Colour(1.0, 0.5, 0.25));
}

TEST_CASE("LambertShader: light at 60 degrees from the normal gives half the colour", "[shader]") {
    LambertShader shader(Colour(1.0, 0.5, 0.25));
    Hit hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), &shader};
    // Direction to light (sqrt(3)/2, 1/2, 0): cos(60) = 0.5
    Light light(Vector(std::sqrt(3.0), 1.0, 0.0), white);

    requireColoursEqual(shader.shade(hit, light), Colour(0.5, 0.25, 0.125));
}

TEST_CASE("LambertShader: light perpendicular to the normal gives black", "[shader]") {
    LambertShader shader(Colour(1.0, 0.5, 0.25));
    Hit hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), &shader};
    Light light(Vector(5.0, 0.0, 0.0), white);

    requireColoursEqual(shader.shade(hit, light), Colour(0.0, 0.0, 0.0));
}

TEST_CASE("LambertShader: light behind the surface gives black, not negative", "[shader]") {
    LambertShader shader(Colour(1.0, 0.5, 0.25));
    Hit hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, 10.0), white);

    requireColoursEqual(shader.shade(hit, light), Colour(0.0, 0.0, 0.0));
}

TEST_CASE("LambertShader: light colour tints the surface colour", "[shader]") {
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    Hit hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), Colour(0.5, 1.0, 0.0));

    requireColoursEqual(shader.shade(hit, light), Colour(0.5, 1.0, 0.0));
}

TEST_CASE("LambertShader: direction to light is measured from the hit point", "[shader]") {
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    Hit hit{1.0, Vector(3.0, 4.0, 5.0), Vector(0.0, 1.0, 0.0), &shader};
    Light light(Vector(3.0, 14.0, 5.0), white);  // straight above the hit point

    requireColoursEqual(shader.shade(hit, light), Colour(1.0, 1.0, 1.0));
}
