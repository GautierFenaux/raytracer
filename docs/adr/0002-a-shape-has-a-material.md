# ADR 0002: A shape has a material

- **Status:** Accepted
- **Date:** 2026-11-20

## Context

The scene contains several kinds of shapes (sphere, plane, later more) and several kinds of materials (flat colour, Lambert, later mirror, glass...). Any shape can be made of any material. We must decide how the two are linked.

## Options considered

1. **Inheritance: a shape *is* a kind of material.** One class per combination: `FlatSphere`, `LambertSphere`, `LambertPlane`, `MirrorSphere`... With 3 shapes and 4 materials, that is 3 × 4 = 12 classes, and every new material adds one class per shape. The intersection code is copied in each one.
2. **Composition: a shape *has* a material.** A shape only does geometry (`hit`); it holds a material and gives it in the `Hit`. The material only does lighting (`shade`). With 3 shapes and 4 materials, that is 3 + 4 = 7 classes.

## Decision

**Composition.** `Shape` and `Material` are two separate interfaces:

- `Shape::hit(ray)` returns a `Hit`: `t`, point, normal and the material of the shape.
- `Material::shade(hit, light)` returns the colour.
- `Camera::trace` links them: it takes the nearest hit from the scene and asks its material for the colour.

A shape stores its material as a `Material*`, a pointer it does not own. `Material` is an interface (`FlatShader`, `LambertShader`), so it cannot be stored by value, and several shapes can share the same material.

## Consequences

- A new shape or a new material is one new class. No existing class changes (open/closed principle).
- Each class has one job: geometry or lighting (single responsibility).
- The pointer is not owned, so **materials must live longer than the scene**. In `main`, they are declared before the scene, so they are destroyed after it. If this becomes error-prone (for example scenes loaded from a file), the scene could own the materials too, with `std::unique_ptr`.
- Shapes, on the other hand, are owned by the scene (`std::vector<std::unique_ptr<Shape>>`): the scene deletes them when it is destroyed.
