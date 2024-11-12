//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include <chrono>
#include <iostream>

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() :
		moduleManager{std::make_unique<ModuleManager>()} {}

void BlockyEngine::Run() {
	//Prepare variables for tracking FPS
	int frames = 0;
	float accumulatedDelta = 0;
	auto lastTime = std::chrono::high_resolution_clock::now();

	BlockyEngine::isRunning = true;
	while (BlockyEngine::isRunning) {
		//Calculate delta
		auto currentTime = std::chrono::high_resolution_clock::now();
		float delta = static_cast<float>((currentTime - lastTime).count()) / 1000000.f;
		lastTime = currentTime;

		//Update cycle
		moduleManager->Update(delta);

		//Increase fps counter and check if a second has passed
		++frames;
		accumulatedDelta += delta;
		if (accumulatedDelta >= 1000.0f) {
			//Reset fps
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			accumulatedDelta = 0;
		}
	}
}
