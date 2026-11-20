#include <memory>
#include "math/vector.h"
#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "scene/scene.h"
#include "render/camera.h"
#include "render/image.h"
#include "io/png_saver.h"
#include "material/lambert_shader.h"
#include "light/light.h"

int main() {
    // Position and configure the camera
    Camera camera(Vector(0, 0, -1), 2.0);

    // Materials are declared before the scene: shapes only point to them,
    // so they must outlive the scene (locals are destroyed in reverse order)
    LambertShader ballMaterial(Colour(1.0, 0.0, 0.0));
    LambertShader floorMaterial(Colour(0.8, 0.8, 0.8));

    // Describe the scene: a red ball resting on a grey floor, lit from the top left
    Scene scene(Light(Vector(-10, 10, -5), Colour(1.0, 1.0, 1.0)));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, &ballMaterial));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0), &floorMaterial));

    // Setup memory buffer for final image
    const int imageWidth = 512;
    const int imageHeight = 512;
    Image image(imageWidth, imageHeight);

    // Render the scene into the image
    camera.render(scene, image);

    // Save the rendered image to a file
    PngSaver saver;
    saver.save(image, "image.png");

    return 0;
}
