//// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
//// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
//// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
//
//#include <imgui/imgui.h>
//#ifndef IMGUI_DEFINE_MATH_OPERATORS
//#define IMGUI_DEFINE_MATH_OPERATORS
//#endif
//#include <imgui/imgui_internal.h>
//
//#include "MainFrame.h"
//
//#include <imgui/backends/imgui_impl_opengl3.h>
//#include <imgui/backends/imgui_impl_glfw.h>
//#include <stdio.h>
//#include <string>
//#include <sstream>
//#include <fstream>
//
//// About Desktop OpenGL function loaders:
////  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
////  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
////  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//#include <GL/gl3w.h>    // Initialize with gl3wInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//#include <GL/glew.h>    // Initialize with glewInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//#include <glad/glad.h>  // Initialize with gladLoadGL()
//#else
//#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
//#endif
//
//// Include glfw3.h after our OpenGL definitions
//#include <GLFW/glfw3.h>
//
//// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
//// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
//// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
//#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
//#pragma comment(lib, "legacy_stdio_definitions")
//#endif
//
//static void glfw_error_callback(int error, const char* description)
//{
//	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}
//
//int main(int, char**)
//{
//	// Setup window
//	glfwSetErrorCallback(glfw_error_callback);
//	if (!glfwInit())
//		return 1;
//
//	// Decide GL+GLSL versions
//#if APPLE
//	// GL 3.2 + GLSL 150
//	const char* glsl_version = "#version 150";
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
//#else
//	// GL 3.0 + GLSL 130
//	const char* glsl_version = "#version 130";
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
//#endif
//
//	// Create window with graphics context
//	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
//	if (window == NULL)
//		return 1;
//	glfwMakeContextCurrent(window);
//	glfwSwapInterval(1); // Enable vsync
//
//	// Initialize OpenGL loader
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//	bool err = gl3wInit() != 0;
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//	bool err = glewInit() != GLEW_OK;
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//	bool err = gladLoadGL() == 0;
//#else
//	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
//#endif
//	if (err)
//	{
//		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
//		return 1;
//	}
//
//	IMGUI_CHECKVERSION();
//	ImGui::CreateContext();
//	ImGuiIO& io = ImGui::GetIO(); (void)io;
//	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
//	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Viewport
//	io.FontAllowUserScaling = true; // activate zoom feature with ctrl + mousewheel
//
//	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
//	ImGuiStyle& style = ImGui::GetStyle();
//	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//	{
//		style.WindowRounding = 0.0f;
//		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//	}
//
//	// Setup Dear ImGui style
//	//ImGui::StyleColorsDark();
//	ImGui::StyleColorsClassic();
//
//	// Setup Platform/Renderer bindings
//	ImGui_ImplGlfw_InitForOpenGL(window, true);
//	ImGui_ImplOpenGL3_Init(glsl_version);
//
//	// Load Fonts
//	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
//	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
//	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
//	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
//	// - Read 'docs/FONTS.txt' for more instructions and details.
//	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
//	//io.Fonts->AddFontDefault();
//	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
//	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
//	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
//	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
//	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
//	//IM_ASSERT(font != NULL);
//
//	MainFrame mainFrame;
//
//	mainFrame.Init();
//
//	// Main loop
//	int display_w, display_h;
//	ImVec2 size;
//	while (!glfwWindowShouldClose(window))
//	{
//		// maintain active, prevent user change via imgui dialog
//		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
//	   
//		// Poll and handle events (inputs, window resize, etc.)
//		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
//		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
//		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//		glfwPollEvents();
//
//		glfwGetFramebufferSize(window, &display_w, &display_h);
//
//		// Start the Dear ImGui frame
//		ImGui_ImplOpenGL3_NewFrame();
//		ImGui_ImplGlfw_NewFrame();
//		ImGui::NewFrame();
//
//		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//		{
//			ImGuiViewport* viewport = ImGui::GetMainViewport();
//			if (viewport)
//			{
//				size = viewport->WorkSize;
//			}
//		}
//		else
//		{
//			size = ImVec2((float)display_w, (float)display_h);
//		}
//
//		mainFrame.Display(ImVec2(display_w, display_h));
//
//		// Rendering
//		ImGui::Render();
//		glViewport(0, 0, display_w, display_h);
//		glClearColor(0.5f, 0.8f, 0.2f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//		// Update and Render additional Platform Windows
//		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
//		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//		{
//			GLFWwindow* backup_current_context = glfwGetCurrentContext();
//			ImGui::UpdatePlatformWindows();
//			ImGui::RenderPlatformWindowsDefault();
//			glfwMakeContextCurrent(backup_current_context);
//		}
//
//		glfwSwapBuffers(window);
//	}
//
//	mainFrame.Unit();
//
//	// Cleanup
//	ImGui_ImplOpenGL3_Shutdown();
//	ImGui_ImplGlfw_Shutdown();
//	ImGui::DestroyContext();
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//
//	return 0;
//}
