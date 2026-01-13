# miniRT (MLX42)

**miniRT** is a small ray tracer written in C as part of the 42 / Codam curriculum.  
The goal is to render a 3D scene described in a `.rt` file by casting rays, computing intersections, and shading surfaces with light.

This implementation uses **MLX42** for windowing and pixel output, and includes a **progressive, multithreaded** renderer with an interactive **preview mode** while moving the camera.

---

## ✨ Features

### Objects
- Sphere
- Plane
- Cylinder
- Cone

### Lighting & materials
- Ambient light + direct lighting with shadows
- **Shininess** and **reflectivity** parameters (normalized `[0..1]`)
- Emissive light objects (renderable “light globe” intersection)

### Rendering
- Progressive accumulation (image refines over time)
- Multithreaded render (thread pool based on CPU cores)
- Two modes:
  - **Preview mode**: `1` ray/sample, `0` bounces (fast feedback while moving)
  - **Full mode**: `MAX_RAYS=20`, `MAX_BOUNCES=10` (higher quality)

---

## ▶️ Build & Run

### Requirements
- C compiler (`cc`)
- `cmake`
- GLFW / OpenGL dependencies required by **MLX42** (platform-dependent)
- `pthread` and math library (`-lm`)

### Build
    make

The Makefile will:
1. Init/update the **MLX42** git submodule
2. Build **MLX42** via CMake
3. Build embedded `libft`
4. Link everything into: `miniRT`

Other targets:
    make clean
    make fclean
    make re

### Run
    ./miniRT <scene.rt>

Example:
    ./miniRT assets/examples/minimal_scene.rt

---

## 🎛️ Controls

- `W / A / S / D` — move the active camera (local forward/right)
- Mouse move — rotate the camera (yaw/pitch)
- `TAB` — switch to the next camera (cycles through all cameras in the scene)
- `ESC` — quit
- Window close button — quit

### Preview behavior
Any movement (WASD or mouse rotation) switches to **preview mode** to keep the UI responsive.  
After ~50ms without movement, the renderer returns to **full mode** and restarts progressive rendering.

---

## 🧾 Scene files (`.rt`)

Scenes are loaded from a `.rt` file passed as the only argument.

This repository includes many ready-to-run examples in:
- `assets/examples/`

You’ll also find “validation” scenes such as invalid camera/ambient/resolution examples.

---

## 🧱 Project structure

### Entry point
- `sources/main.c`
  - Validates args: `./miniRT <scene.rt>`
  - Parses the scene and initializes MLX42
  - Registers hooks (keyboard, mouse, loop, close)
  - Starts progressive rendering and enters `mlx_loop`

### Parsing
- `sources/parsing/*`
  - Scene loader and line/token parsing
  - Element parsers: ambient, camera, light, resolution
  - Object parsers: sphere, plane, cylinder, cone
  - Material parsers: `parse_shininess.c`, `parse_reflectivity.c`
  - Cleanup helpers: `free_scene.c`, token utilities

### Math
- `sources/math/*`
  - Vector operations, camera basis computation
  - Quaternion utilities for smooth orientation updates

### Rendering pipeline
- `sources/rendering/*`
  - `ray_casting.c` — precompute per-pixel ray directions
  - `rendering_pass.c` — main per-pixel render loop (intersection + shading)
  - `preview_mode.c` — fast direct-light + ambient shading
  - `path_tracing.c` — multi-bounce tracing with progressive accumulation
  - `multithreading.c` — thread pool + frame-based restart mechanism
  - `rendering/intersection/*` — object intersection functions
  - `rendering/lighting/*` — light evaluation, shadows, reflectance, sampling
  - `rendering/surface_interaction/*` — compute normals/material response per hit

### Input / hooks
- `sources/hooks/*`
  - `wasd.c` — key handling + camera switching
  - `update_wasd.c` — per-frame movement with delta-time
  - `mouse_input.c`, `mouse_filters.c`, `mouse.c` — mouse rotation with filtering/clamping
  - `loop_hook.c` — auto-exit preview mode when idle

### Dependencies
- `includes/MLX42/` — MLX42 (git submodule, built via CMake)
- `includes/libft/` — embedded libft + ft_printf + get_next_line

---

## ⚙️ How it works (high-level)

1. **Parse**
   - Read the `.rt` file
   - Validate and build `t_scene` (resolution, lights, cameras, objects, materials)

2. **Initialize**
   - Create MLX42 window and image buffer
   - Select `active_cam` (first camera)
   - Start a render thread pool (one worker per CPU core)

3. **Progressive rendering**
   - Rendering is “progressive”: pixels accumulate samples over time
   - Restarting the render (camera move / mode switch) clears buffers and begins a new frame

4. **Preview vs full**
   - While moving: **preview** (fast direct light + ambient)
   - When idle: **full** tracing with multiple rays and bounces for better global illumination-like results

---

## 🧠 What I learned

- Implementing robust ray/object intersections and handling edge cases
- Building a progressive renderer that remains interactive
- Multithreading a per-pixel render workload safely
- Using quaternions for stable camera rotation (yaw/pitch → orientation)
- Designing a strict scene parser with clean failure paths and proper cleanup
