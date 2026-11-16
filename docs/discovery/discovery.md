# Discovery report

## Problem statement

The big 3D studios hired "vibe-coders" to built their software :  but their rendering tools, broke one after the other, and no one on staff could explain why.

## Client interview summary

### [Theme]

**Need:** [What the client needs, in your words.]

> **Q (Colleague):** "How many frame per second do you need to render your film ?"
>
> **A:** "We need 24 FPS."

> **Q (Colleague):** "What's the size of the actual farm you using to build a moovie ?"
>
> **A:** "Actually we have a farm of 1000 computers."

> **Q (Me):** "Why does the actual raytracers on the market do not fill your expectations ? "
>
> **A:** "The price is too expensive we had to spend 2 millions dollars in order to use the licence on all our machine."

> **Q (Colleague):** "Actually, which software do you use ?"
>
> **A:** "Maya"

> **Q (Pierre):** "What is the budget for this project ?"
>
> **A:** "Our budget is 500 000 dollars."


**My conclusion:** The client needs to have a software that is easily usable for his team, that takes a picture in entry and render the ray tracing effect on the output. The software must be maintenable.
Their time to build a moovie is around 2 months

### Open questions

- [What you still don't know, and any contradictions you noticed.]

## State of the art

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| Arnold | Autodesk | Proprietary, subscription | About $476 / seat / year, $32,298 for 100 seats (reseller price, checked 2026-11-16) | CPU and GPU path tracer. Integrated in Maya. Used in film production. | [Autodesk](https://www.autodesk.com/products/arnold/overview), [CDW 1 seat](https://www.cdw.com/product/arnold-2026-new-subscription-annual-1-seat/8331003), [CDW 100 seats](https://www.cdw.com/product/arnold-2026-new-subscription-annual-100-seats/9115351) |
| RenderMan | Pixar | Proprietary, perpetual licence + yearly maintenance. Free for non-commercial use. | $595 / licence, then $250 / year maintenance (checked 2026-11-16) | CPU and hybrid CPU+GPU (XPU) path tracer. Plugin for Maya. Used on Pixar films. | [RenderMan store](https://renderman.pixar.com/store/) |
| V-Ray | Chaos | Proprietary, subscription | About $540 / year (Solo), extra render nodes sold separately (checked 2026-11-16) | CPU and GPU ray tracer. Plugin for Maya. Used in VFX and architecture. | [Chaos pricing](https://www.chaos.com/pricing), [V-Ray for M&E](https://www.chaos.com/vray/media-and-entertainment) |
| Redshift | Maxon | Proprietary, subscription | About $289 / year (price from June 2025, checked 2026-11-16) | GPU-first renderer (also CPU). Plugin for Maya. Fast but "biased" (trades accuracy for speed). | [CG Channel](https://www.cgchannel.com/2025/06/maxon-releases-redshift-2025-5/) |
| Cycles | Blender Foundation | Open source (Apache 2.0) | Free (checked 2026-11-16) | CPU and GPU path tracer. Made for Blender, no official Maya plugin. | [Blender announcement](https://code.blender.org/?p=913) |

All the commercial solutions do the job and work with Maya, but they are paid per machine: with a farm of 1000 computers the cost grows very fast and comes back every year (subscription or maintenance). The only free solution, Cycles, does not work in Maya, which is the tool the client's team uses.

So there is a place for a custom ray tracer: no licence cost per machine, and made to fit the client's Maya workflow, inside the 500 000 dollars budget.

## What is ray tracing?

Ray tracing is, on a picture, the art of rendering ligths effects on physical objects.

How it works: for each pixel of the picture, the program sends a ray from the camera into the scene. It looks for the first object the ray hits, then computes the colour of this point from the lights and the material of the object. The ray can bounce again, which gives shadows, reflections and transparency.

It gives realistic pictures but it is slow, because there are millions of rays to compute for one picture.

**Sources:**

- Started from: [Ray tracing (graphics), Wikipedia](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)).
- Reference to come back to: [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) and [Physically Based Rendering](https://pbr-book.org/) (the reference book, free online).

## What is C++?

C++ is an oriented programming language that need to be compiled in order to work.

The compiler turns the code into machine code, so the program is very fast, and the developer controls the memory directly.

### Programming paradigms

C++ is multi-paradigm, it does not force one style:

- Procedural: simple functions and data, like in C.
- Object-oriented (OOP): classes, inheritance, virtual functions.
- Generic: templates, the same code works for several types.
- Functional (a little): lambdas, functions passed as values.

### What to watch out for

- Memory: there is no garbage collector. If I forget to free memory I get a leak, and if I use memory already freed the program crashes.
- Undefined behaviour: some mistakes (reading outside an array, using a variable not initialised) compile without error but give wrong results.
- Copies: passing a big object to a function copies it, which is slow. I should pass it by reference.
- Compilation: the code is split in header and source files, and compiling a big project takes time.

### Shaping the domain model

C++ lets me mix several styles, so I would use each one where it fits:

- Small maths objects (vector, colour, ray) are simple structs that I copy.
- Shapes and materials use OOP: one common interface, and one class per shape (sphere, plane...). Adding a new shape does not change the rest of the code.
- C++ has no garbage collector, so I must decide who owns what: the scene owns its shapes.
- The rendering loop runs millions of times, so I keep it simple and fast.

**Sources:**

- Started from: [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) (a ray tracer built step by step in C++).
- Reference to come back to: [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) and [cppreference](https://en.cppreference.com/w/cpp/language/raii) (RAII and memory ownership), and [undefined behaviour](https://en.cppreference.com/w/cpp/language/ub).
- For the paradigms: [Bjarne Stroustrup's FAQ, "What is multiparadigm programming?"](https://www.stroustrup.com/bs_faq.html#multiparadigm) (by the creator of C++).