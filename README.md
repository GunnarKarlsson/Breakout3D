# Breakout3D

A 3D take on classic Breakout, built in C++ with a small custom OpenGL engine rather than a third-party game engine.

Bounce the ball with a paddle, clear textured brick layouts, and watch cyan particle explosions (with a matching point light) when a brick breaks. The playfield sits in a cube-mapped skybox, with walls, paddle, ball, and targets rendered as textured cubes under directional plus point lighting.

There are two levels loaded from text files. Clearing a level advances to the next; after the last level it loops back to the first and the ball speeds up.

## Controls

| Key | Action |
| --- | --- |
| Left / Right | Move the paddle |
| P | Trigger a particle effect (debug) |
| Escape | Quit |

## Tech

**Windowing and app:** Qt 5 (`core`, `gui`, `opengl`, `widgets`). The game runs in a `QOpenGLWindow` at 640×640, with a 20 ms update timer.

**Graphics:** OpenGL 4.2 Core Profile and GLSL 4.10. Shaders in `shaders/` are compiled at runtime from Qt resources (`resources.qrc`).

**Math:** [GLM](https://github.com/g-truc/glm) for vectors, matrices, and the camera look-at / perspective setup.

**Images:** [stb_image](https://github.com/nothings/stb) (`stb_image.h`) for loading PNG textures from `assets/` (bundled via Qt resources).

### Custom engine pieces

These are the in-house 3D components the game is built from:

| Component | Role |
| --- | --- |
| `Shader` / `BasicShader` / `SkyboxShader` / `ParticleShader` | Load GLSL from `:/shaders/...`, compile programs, set uniforms |
| `Entity` | Textured cube mesh (VAO/VBO), transform, visibility, paddle/ball motion |
| `Camera` | Euler-angle camera and view matrix (`glm::lookAt`) |
| `AssetManager` | Loads brick, paddle, ball, target, and skybox textures from `:/assets/...` |
| `Skybox` | Cubemap background (six sky faces) |
| `Particle` / `ParticleEffect` | Burst of small cubes plus a decaying point light on brick hits |
| `collision.h` | AABB overlap tests between entities |
| `Level` | Grid of target bricks parsed from `assets/level1.txt` / `assets/level2.txt` (`1` = brick) |

Lighting is a directional light plus an optional point light driven by the particle effect (see `shaders/basic.frag` and `pointlight.h`).

## Requirements

- A C++ compiler (Clang on macOS, or GCC/MSVC)
- [Qt 5](https://www.qt.io/download-qt-installer) with OpenGL / Widgets modules (`qmake` on your `PATH`)
- [GLM](https://github.com/g-truc/glm) headers
- OpenGL 4.2-capable GPU and drivers

## Build and run

The project is a Qt `.pro` app (`Breakout.pro`). Files in `assets/` and `shaders/` are compiled into the binary via `resources.qrc`, so the game does not depend on absolute filesystem paths.

**1. Install GLM** if it is not already on your compiler’s include path:

```bash
# macOS
brew install glm

# Debian/Ubuntu
sudo apt install libglm-dev
```

If GLM lives somewhere else, pass it to qmake:

```bash
qmake Breakout.pro GLM_DIR=/path/to/glm
```

**2. Build:**

```bash
qmake Breakout.pro
make
```

On macOS this produces `Breakout.app`. Run it with:

```bash
open Breakout.app
```

Or from Qt Creator: open `Breakout.pro`, configure a Qt 5 kit, then Build and Run.

## License

MIT. See [LICENSE](LICENSE).

`stb_image.h` is third-party (public domain / MIT-0); GLM is licensed under the Happy Bunny License / MIT.
