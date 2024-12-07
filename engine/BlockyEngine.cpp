//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"
#include <iostream>

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() : moduleManager{ModuleManager::getInstance()}, sceneManager{std::make_unique<SceneManager>()}, timeUtil(TimeUtil::CreateInstance()) {}

void BlockyEngine::Run() {
	int frames = 0;
	float accumulatedDelta = 0;

	BlockyEngine::isRunning = true;
	while (BlockyEngine::isRunning) {
		// Calculate delta time.
		float delta = timeUtil->calculateDeltaTime();

		// Update cycle.
		sceneManager->Update(delta);
		moduleManager.Update(delta);

		// FPS logic.
		++frames;
		accumulatedDelta += delta;
		if (accumulatedDelta >= 1.0f) {
			std::cout << "FPS: " << timeUtil->getFPS() << std::endl;
			frames = 0;
			accumulatedDelta = 0;
		}
	}
}
