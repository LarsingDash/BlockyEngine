//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() : moduleManager{ModuleManager::getInstance()}, sceneManager{std::make_unique<SceneManager>()}, timeUtil(TimeUtil::CreateInstance()) {}

void BlockyEngine::Run() {
	BlockyEngine::isRunning = true;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
	while (BlockyEngine::isRunning) {
		// Calculate delta time.
		float delta = timeUtil->CalculateDeltaTime();

		// Update cycle.
		sceneManager->Update(delta);
		moduleManager.Update(delta);
	}
#pragma clang diagnostic pop
}
