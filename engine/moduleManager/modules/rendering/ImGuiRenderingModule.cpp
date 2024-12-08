//
// Created by 11896 on 06/12/2024.
//

#include "ImGuiRenderingModule.hpp"
#include "imgui_impl_sdlrenderer2.h"
#include <iostream>
#include <utility>

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

	for (auto& [tag, uiComponent] : _uiComponents) {
		uiComponent();
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), _renderer);
}

void ImGuiRenderingModule::AddComponent(const std::string& tag, std::function<void()> uiComponent) {
	_uiComponents[tag] = std::move(uiComponent);
}

void ImGuiRenderingModule::RemoveComponent(const std::string& tag) {
	std::cout << "Removing component: " << tag << std::endl;
	_uiComponents.erase(tag);
}