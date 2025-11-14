cmake_minimum_required(VERSION 3.20)
project(model-loader VERSION 0.1.0 LANGUAGES CXX)

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED CONFIG)
find_package(bgfx REQUIRED CONFIG)
find_package(imgui REQUIRED CONFIG)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} fmt::fmt glfw bgfx::bgfx imgui::imgui) 
