﻿//
// Created by larsv on 12/11/2024.
//

#include "BlockyEngine.hpp"
#include "utilities/TimeUtil.hpp"

bool BlockyEngine::isRunning{false};
const BlockyEngine::BlockyConfigs* BlockyEngine::_configs{nullptr};

BlockyEngine::BlockyEngine(const BlockyEngine::BlockyConfigs& configs) {
	_configs = &configs;

	_moduleManager = std::unique_ptr<ModuleManager>(ModuleManager::CreateInstance());
	_sceneManager = std::unique_ptr<SceneManager>(SceneManager::CreateInstance());
	_timeUtil = std::unique_ptr<TimeUtil>(TimeUtil::CreateInstance());
}

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
