//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

SceneManager* SceneManager::_instance{nullptr};

SceneManager::SceneManager() : _recalculationList() {}

SceneManager* SceneManager::CreateInstance() {
	auto instance = new SceneManager();
	_instance = instance;
	return instance;
}

void SceneManager::AddScene(std::unique_ptr<GameObject>&& scene) {
	_scenes.emplace_back(std::move(scene));
}

void SceneManager::SwitchScene(const std::string& tag) { _switchTarget = tag; }

void SceneManager::_switchScene() {
	//Find the targeted scene
	auto it = std::find_if(_scenes.begin(), _scenes.end(),
						   [&tag = _switchTarget]
								   (const std::unique_ptr<GameObject>& scene) {
							   return scene->tag == tag;
						   });

	//Switch to scene if found
	if (it != _scenes.end()) {
		//Overriding _activeScene will first unload the whole previous scene, then instantiate the new like a prefab
		_activeScene = std::make_unique<GameObject>(**it);
		
		//Activate separately from copy constructor to allow for prefab creation without them activating instantly
		_activeScene->SetActive(true);
	}
	
	_switchTarget.clear();
}

void SceneManager::Update(float delta) {
	//Check if scene should be switched before starting next cycle
	if (!_switchTarget.empty()) _switchScene();
	
	//Update active scene starting from the root
	if (_activeScene) _activeScene->Update(delta, _recalculationList);

	//Go through all transforms that marked themselves to be recalculated
	for (auto& trans : _recalculationList) {
		auto& cur = trans.get();
		if (cur.isMarkedForRecalculation) cur.RecalculateWorldMatrix();
	}
	_recalculationList.clear();
}
