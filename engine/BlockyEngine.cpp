//
// Created by larsv on 12/11/2024.
//

#include <iostream>
#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"
#include "moduleManager/modules/networking/NetworkingModule.hpp"

bool BlockyEngine::isRunning{false};

BlockyEngine::BlockyEngine() :
		_moduleManager(ModuleManager::CreateInstance()),
		_sceneManager(SceneManager::CreateInstance()),
		_timeUtil(TimeUtil::CreateInstance()) {}

SceneManager& BlockyEngine::GetSceneManager() const { return *_sceneManager; }

void BlockyEngine::Run() {
	BlockyEngine::isRunning = true;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
	while (BlockyEngine::isRunning) {
		// Calculate delta time.
		float delta = _timeUtil->CalculateDeltaTime();

		// Update cycle.
		_sceneManager->Update(delta);
		_moduleManager->Update(delta);
	}
#pragma clang diagnostic pop
}
