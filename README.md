# BGFX Model Loader

## Introduction

This is a fun introductory project for me to get into 3D graphics. My last C++ project, a 2D collision engine, was pretty fun, and I wanted to get into 3D. The previous stack used GLFW for window management, GLAD for loading OpenGL functions, and fmt for printing to console.

This time, I decided to stick with GLFW for window management. Although I had originally intended to use SDL3, it simply wasn't working with Conan, so I just used the same library as last time. 

However, I decided that I wouldn't be using OpenGL for this project. This time, we're using the [BGFX library](https://github.com/bkaradzic/bgfx). This doesn't load OpenGL specifically. Instead, it detects what platform you're on and loads the graphics API that'd work best with your system.

| Platform/OS | Graphics API |
| --- | --- |
| Windows | Direct3D 11/12 |
| Linux | OpenGL/Vulkan |
| macOS | Metal |

I chose BGFX because this would allow me to make my future projects more cross-platform, and the fact that this project is running the Metal Graphics API under the hood for my machine is pretty exciting.

## Build Instructions

You'll need the Conan package manager to build this project. If you're on MacOS, you can simply

```bash
brew install conan
```

However, if you're on Windows or Linux, I'd recommend making a Python virtual environment in the project root and then running

```bash
pip install conan
```

Because we're using Conan, you don't have to worry about manually installing libraries. First run

```bash
conan profile detect --force
```

This gives Conan an idea of your system's architecture, OS, and compiler. Next, install all libraries with

```bash
conan install . --output-folder=build --build=missing
```

Now build with CMake.

```bash
cmake --preset conan-release
cmake --build --preset conan-release
```

An executable file should show up in the build/ directory.
```
```
```
```
```
```
