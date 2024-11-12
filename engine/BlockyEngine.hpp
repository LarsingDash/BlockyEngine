//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_BLOCKYENGINE_HPP
#define BLOCKYENGINE_BLOCKYENGINE_HPP

#include <memory>
#include "modules/core/ModuleManager.hpp"

class BlockyEngine {
	public:
		BlockyEngine();
		~BlockyEngine() = default;

		BlockyEngine(const BlockyEngine& other) = delete;
		BlockyEngine& operator=(const BlockyEngine& other) = delete;
		BlockyEngine(BlockyEngine&& other) noexcept = delete;
		BlockyEngine& operator=(BlockyEngine&& other) noexcept = delete;

		void Run();
		
		//Game
		static bool isRunning;
		
	private:
		//SceneManager
		ModuleManager& moduleManager;
};

#endif //BLOCKYENGINE_BLOCKYENGINE_HPP
