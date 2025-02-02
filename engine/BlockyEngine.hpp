﻿//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_BLOCKYENGINE_HPP
#define BLOCKYENGINE_BLOCKYENGINE_HPP

#include <memory>

#include "moduleManager/ModuleManager.hpp"
#include "sceneManager/SceneManager.hpp"
#include "utilities/TimeUtil.hpp"

/// An instance of Blocky Engine, only one should ever need to be created
class BlockyEngine {
	public:
		/// Blocky Engine configs set from the constructor of BlockyEngine, used throughout the engine for various configuration
		struct BlockyConfigs {
			int windowWidth;
			int windowHeight;
			uint32_t windowFlags;
			std::string defaultFontPath;
		};
		
		inline static const BlockyConfigs* GetConfigs() { return _configs; }
		
		BlockyEngine() = delete;
		explicit BlockyEngine(const BlockyConfigs& configs);
		~BlockyEngine() = default;

		BlockyEngine(const BlockyEngine& other) = delete;
		BlockyEngine& operator=(const BlockyEngine& other) = delete;
		BlockyEngine(BlockyEngine&& other) noexcept = delete;
		BlockyEngine& operator=(BlockyEngine&& other) noexcept = delete;

		/// This should only be used in the place where the BlockyEngine instance is still accessible (the main for example).
		///	The constructions facilitating the Singleton pattern should be used anywhere else instead
		/// \return The SceneManager instance, managed by this BlockyEngine instance. 
		[[nodiscard]] SceneManager& GetSceneManager() const;

		/// Calling this method will trap the calling thread in the BlockyEngine gameloop, till the game closes.
		/// Preparations like building scenes and adding them to the SceneManager should be done before this point.
		void Run();

		//Game
		static bool isRunning;

	private:
		static const BlockyConfigs* _configs;
		
		std::unique_ptr<ModuleManager> _moduleManager;
		std::unique_ptr<SceneManager> _sceneManager;
		std::unique_ptr<TimeUtil> _timeUtil;
};

#endif //BLOCKYENGINE_BLOCKYENGINE_HPP
