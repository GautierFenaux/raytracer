# Domain model

State at milestone m1: a scene of shapes, lit by one point light, seen by a pinhole camera.

```mermaid
classDiagram
    class Camera {
        -Vector position
        -double screenWidth
        +rayThroughPixel(column, row, width, height) Ray
        +trace(Ray, Scene) Colour
        +render(Scene, Image)
    }
    class Scene {
        -Light light
        -vector~unique_ptr~Shape~~ shapes
        +add(unique_ptr~Shape~)
        +nearestHit(Ray) optional~Hit~
        +light() Light
    }
    class Shape {
        <<interface>>
        +hit(Ray) optional~Hit~
    }
    class Sphere {
        -Vector center
        -double radius
    }
    class Plane {
        -Vector point
        -Vector normal
    }
    class Material {
        <<interface>>
        +shade(Hit, Light) Colour
    }
    class FlatShader {
        -Colour colour
    }
    class LambertShader {
        -Colour colour
    }
    class Hit {
        <<struct>>
        +double t
        +Vector point
        +Vector normal
        +Material* material
    }
    class Light {
        -Vector position
        -Colour colour
    }
    class Image {
        +setPixel(x, y, Colour)
        +pixel(x, y) Colour
    }
    class ImageSaver {
        <<interface>>
        +save(Image, path)
    }

    Camera ..> Scene : renders
    Camera ..> Image : fills
    Scene *-- "0..*" Shape : owns
    Scene *-- "1" Light
    Shape <|-- Sphere
    Shape <|-- Plane
    Shape --> "1" Material : has
    Material <|-- FlatShader
    Material <|-- LambertShader
    Shape ..> Hit : returns
    Hit --> Material
    ImageSaver <|-- PngSaver
    ImageSaver ..> Image : saves
```

## How a pixel gets its colour

1. `Camera::rayThroughPixel` builds a `Ray` from the eye through the pixel.
2. `Scene::nearestHit` asks each `Shape` for its `Hit` and keeps the one with the smallest `t`.
3. The `Material` in that hit computes the colour with the `Light` (Lambert: `colour × light × max(0, N·L)`).
4. No hit: the pixel is black.

## Ownership

- The **scene owns its shapes** (`unique_ptr`): they are deleted with the scene.
- **Shapes do not own their materials** (`Material*`): materials must outlive the scene. See [ADR 0002](adr/0002-a-shape-has-a-material.md).

## Decisions

- [ADR 0001: Save images as PNG with lodepng](adr/0001-png-library.md)
- [ADR 0002: A shape has a material](adr/0002-a-shape-has-a-material.md)

## Not yet in the model

Shadows, reflections, several lights, other shapes.
