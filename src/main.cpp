#include <stdio.h>
#include <fmt/core.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>
#define WIN_WIDTH 1280 
#define WIN_HEIGHT 720 

static void glfw_errorCallback(int error, const char *description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

int main(int argc, char **argv)
{
	glfwSetErrorCallback(glfw_errorCallback);
	if (!glfwInit())
		return 1;

	GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Model Loader", nullptr, nullptr);

	if (!window)
		return 1;
  
	bgfx::renderFrame();
	
	bgfx::Init init;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
	init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
	init.platformData.nwh = glfwGetWin32Window(window);
#endif
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	init.resolution.width = (uint32_t)width;
	init.resolution.height = (uint32_t)height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	if (!bgfx::init(init))
		return 1;

  bgfx::RendererType::Enum renderer = bgfx::getRendererType();
  fmt::print("Using the {} graphics API.\n", bgfx::getRendererName(renderer));
	
	const bgfx::ViewId kClearView = 0;
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(window, &width, &height);
		if (width != oldWidth || height != oldHeight) {
      fmt::print("Window resized. {} x {}\n", width, height);

			bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
		}
		
		bgfx::touch(kClearView);
		bgfx::frame();
	}
	
	bgfx::shutdown();
	glfwTerminate();
	return 0;
}
