//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include <chrono>
#include <iostream>

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() : moduleManager(ModuleManager::CreateInstance()),
							   sceneManager(SceneManager::CreateInstance()) {}

SceneManager& BlockyEngine::GetSceneManager() const {return *sceneManager;}

void BlockyEngine::Run() {
	//Prepare variables for tracking FPS
	int frames = 0;
	float accumulatedDelta = 0;
	auto lastTime = std::chrono::high_resolution_clock::now();

	BlockyEngine::isRunning = true;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
	while (BlockyEngine::isRunning) {
		//Calculate delta
		auto currentTime = std::chrono::high_resolution_clock::now();
		float delta = static_cast<float>((currentTime - lastTime).count()) / 1000000000.f;
		lastTime = currentTime;

		//Update cycle
		sceneManager->Update(delta);
		moduleManager->Update(delta);

		//Increase fps counter and check if a second has passed
		++frames;
		accumulatedDelta += delta;
		if (accumulatedDelta >= 1.0f) {
			//Reset fps
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			accumulatedDelta = 0;
		}
	}
#pragma clang diagnostic pop
}
