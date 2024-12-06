//
// Created by 11896 on 06/12/2024.
//

#include "ImGUIRenderingModule.hpp"
#include "imgui_impl_sdlrenderer2.h"

#include <iostream>

ImGuiRenderingModule::ImGuiRenderingModule(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext context)
		: _window(window), _renderer(renderer), _context(context) {
	Init();
}

void ImGuiRenderingModule::Init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	int width, height;
	SDL_GetWindowSize(_window, &width, &height);

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));


	ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
	ImGui_ImplSDLRenderer2_Init(_renderer);
}

void ImGuiRenderingModule::Render() {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("IMGUI WINDOW");
	ImGui::Text("Test");
	ImGui::End();

	ImGui::Render();
}