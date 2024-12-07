//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"
#include <chrono>
#include <iostream>

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() : moduleManager{ModuleManager::getInstance()},
							   sceneManager{std::make_unique<SceneManager>()} {}

void BlockyEngine::Run() {
	TimeUtil timeUtils;

	int frames = 0;
	float accumulatedDelta = 0;

	BlockyEngine::isRunning = true;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
	while (BlockyEngine::isRunning) {
		// Calculate delta time
		float delta = timeUtils.calculateDeltaTime();

		// Update cycle
		sceneManager->Update(delta);
		moduleManager.Update(delta);

		// Increase FPS counter and check if a second has passed
		++frames;
		accumulatedDelta += delta;
		if (accumulatedDelta >= 1.0f) {
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			accumulatedDelta = 0;
		}
	}
#pragma clang diagnostic pop
}
