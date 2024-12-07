//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"
#include <iostream>

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() : moduleManager{ModuleManager::getInstance()},
							   sceneManager{std::make_unique<SceneManager>()} {}

void BlockyEngine::Run() {
	TimeUtil timeUtils;

	BlockyEngine::isRunning = true;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
	while (BlockyEngine::isRunning) {
		// Calculate delta time
		float delta = timeUtils.calculateDeltaTime();

		// Update cycle
		sceneManager->Update(delta);
		moduleManager.Update(delta);

		// Get and print FPS
		std::cout << "FPS: " << timeUtils.getFPS() << std::endl;
	}
#pragma clang diagnostic pop
}
