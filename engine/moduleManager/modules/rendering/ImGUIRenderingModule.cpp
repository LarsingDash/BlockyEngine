//
// Created by 11896 on 06/12/2024.
//

#include "ImGUIRenderingModule.hpp"


#include <iostream>
#include <SDL_opengl.h>

ImGuiRenderingModule::ImGuiRenderingModule(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext context)
		: _window(window), _renderer(renderer), _context(context) {
	Init();
}

void ImGuiRenderingModule::Init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	if (!ImGui_ImplSDL2_InitForOpenGL(_window, _context)) {
		std::cerr << "Failed to initialize ImGui SDL2 backend" << std::endl;
		return;
	}

	if (!ImGui_ImplOpenGL3_Init("#version 130")) {  // GLSL 130 for OpenGL
		std::cerr << "Failed to initialize ImGui OpenGL backend" << std::endl;
		return;
	}
}

void ImGuiRenderingModule::Render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("IMGUI WINDOW");
	ImGui::Text("Test");
	ImGui::End();

	ImGui::Render();
	glViewport(0, 0, (GLsizei)ImGui::GetIO().DisplaySize.x, (GLsizei)ImGui::GetIO().DisplaySize.y);
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}