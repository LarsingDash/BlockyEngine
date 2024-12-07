//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_BLOCKYENGINE_HPP
#define BLOCKYENGINE_BLOCKYENGINE_HPP

#include <memory>
#include "moduleManager/ModuleManager.hpp"
#include "sceneManager/SceneManager.hpp"
#include "utilities/TimeUtil.hpp"

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
		std::unique_ptr<SceneManager> sceneManager;
		std::unique_ptr<TimeUtil> timeUtil;
		ModuleManager& moduleManager;
};

#endif //BLOCKYENGINE_BLOCKYENGINE_HPP
