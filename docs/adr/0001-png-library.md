# ADR 0001: Save images as PNG with lodepng

- **Status:** Accepted
- **Date:** 2026-11-20

## Context

The raytracer computes an array of colours in memory (`Image`). It must write it to a file that anyone can open, without extra tools. The build must work in the dev container with `make`, without installing system packages by hand.

## Options considered

1. **Write a PPM file by hand.** No dependency, a few lines of code. But many image viewers cannot open PPM, so the client would need a converter.
2. **libpng.** The reference PNG library. But it is a system dependency with a C API, and it needs zlib: more setup for a single `save` call.
3. **stb_image_write.** A single header, simple. Also a good option.
4. **lodepng.** One `.cpp` and one `.h`, no dependency, a C++ API (`lodepng::encode`).

## Decision

Use **lodepng**, fetched by CMake with `FetchContent` and pinned to a fixed commit, built as a small static library (`lodepng_lib`).

lodepng is only used in `PngSaver`. The rest of the code depends on the `ImageSaver` interface, not on lodepng.

## Consequences

- PNG files open everywhere, and nobody installs anything: CMake downloads the library at the first build.
- The pinned commit gives the same build on every machine.
- The first build needs network access.
- Changing the format (JPEG, PPM...) means adding another `ImageSaver`, without touching the renderer.
