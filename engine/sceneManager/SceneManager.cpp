//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

SceneManager::SceneManager() : _recalculationList() {}

void SceneManager::AddScene(std::unique_ptr<GameObject>&& scene) {
	_scenes.emplace_back(std::move(scene));
}

void SceneManager::SwitchScene(const std::string& tag) {
	auto it = std::find_if(_scenes.begin(), _scenes.end(), [&tag](const std::unique_ptr<GameObject>& scene) {
		return scene->tag == tag;
	});
	
	if (it != _scenes.end()) {
		_activeScene = std::make_unique<GameObject>(**it);
		_activeScene->SetActive(true);
	}
}

void SceneManager::Update(float delta) {
	//Update active scene starting from the root
	if (_activeScene) _activeScene->Update(delta, _recalculationList);

	//Go through all transforms that marked themselves to be recalculated
	for (auto& trans : _recalculationList) {
		auto& cur = trans.get();
		if (cur.isMarkedForRecalculation) cur.RecalculateWorldMatrix();
	}
	_recalculationList.clear();
}
