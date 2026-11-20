#include <catch2/catch_test_macros.hpp>
#include "material/flat_shader.h"
#include "geometry/hit.h"
#include "light/light.h"
#include "test_helpers.h"

TEST_CASE("FlatShader returns its colour regardless of normal and light", "[shader]") {
    FlatShader shader(Colour(1.0, 1.0, 0.0));
    Hit hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, 10.0), Colour(1.0, 1.0, 1.0));  // behind the surface

    requireColoursEqual(shader.shade(hit, light), Colour(1.0, 1.0, 0.0));
}
