*This project has been created as part of the 42 curriculum by alisharu, vmakarya.

# miniRT

## Description

`miniRT` is a small real-time ray tracer written in C. It parses a `.rt` scene description file, builds an in-memory representation of the scene, and renders it using basic ray-tracing techniques. The goal is to introduce and practice fundamentals of ray tracing (rays, intersections, normals, lighting, shadows) while following the 42 Norm and using `minilibx` on macOS and Linux.

Supported features (overview):
- Primitives: sphere (`sp`), plane (`pl`), cylinder (`cy`), cone (`co`)
- Lights: ambient light and point lights
- Camera: single perspective camera with configurable position, orientation, and field of view
- Shading: ambient, diffuse and specular lighting, shadows, and simple reflection
- Extras: procedural checkerboard patterns, simple bump/texture mapping, multithreaded rendering

## Instructions

Requirements:
- OS: macOS or Linux
- Compiler: `cc` (compatible with `-Wall -Wextra -Werror`)
- Libraries: `libft` (provided in `libs/libft`) and `minilibx` (`libs/minilibx_macos` or `libs/minilibx-linux`)

Build:
1. From the project root, run:

   ```bash
   make
   ```

   This target builds `libft`, builds the appropriate `minilibx` for your OS, compiles sources into `build/`, and links the final executable `miniRT`.

Useful make targets:
- `make fclean && make` — full rebuild from scratch
- `make clean` — remove object files and library objects
- `make fclean` — remove objects and the `miniRT` executable
- `make norm` — run Norminette checks (if configured)

Run:

- To render a scene, pass a `.rt` file located in `maps/`:

  ```bash
  ./miniRT maps/one.rt
  ```

Controls (implementation-specific — adapt if your build differs):
- ESC or window close: quit the program and free resources
- Arrow keys / WASD: move camera (if implemented)
- Mouse: look/rotate camera (if implemented)

## Features

Mandatory:
- Parsing `.rt` scene files with ambient light, one or more point lights, and a single camera
- Sphere, plane, cylinder, cone primitives with intersection and normal calculations
- Input validation with clear error messages
- Vector math utilities and normalization
- Lighting (ambient + diffuse + specular) and shadow computation
- Proper resource deallocation and clean exit

Implemented extras / bonuses:
- Cone primitive (`co`) with intersection and normal computations
- Multithreaded rendering (see `source/ray_tracing/thread/`)
- Procedural checkerboard for multiple primitives
- Simple bump/texture mapping

## Maps / Examples

Example scene files live in the `maps/` directory (e.g., `maps/mini.rt`, `maps/room.rt`, `maps/solar.rt`). Use these to test different compositions and effects.

## Gallery

Example renders are included in `assets/` (several screenshots demonstrating checkerboards, lighting, multisphere compositions, etc.).

## Resources

Classic references and documentation that were useful while developing this project:
- "Ray Tracing in One Weekend" — Peter Shirley: https://raytracing.github.io/
- Scratchapixel — ray-tracing and shading tutorials: https://www.scratchapixel.com/
- Phong reflection model: https://en.wikipedia.org/wiki/Phong_reflection_model
- LearnOpenGL — Lighting Basics: https://learnopengl.com/Lighting/Basic-Lighting
- miniLibX documentation and examples (for windowing and image usage)

## AI usage

AI tools (primarily Grok and occasionally ChatGPT) were used only as development aids in the following ways:
- Explaining and verifying mathematical concepts (cone/cylinder intersection formulas, normal perturbation for bump mapping, reflection vectors)
- Debugging parsing edge cases and floating-point comparisons
- Suggesting improvements to cross-platform `Makefile` handling and build setup
- Helping to clarify and improve README wording and documentation

No production code was directly copied from AI outputs. All intersection logic, shading calculations, threading implementation, parsing rules, and utilities were hand-written and tested by the authors. AI was used as an educational reviewer and assistant similar to consulting documentation or asking a peer.
