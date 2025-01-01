//
// Created by larsv on 29/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_SPAWNERCOMP_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_SPAWNERCOMP_HPP_

#include "components/Component.hpp"
#include "utilities/JsonUtil.hpp"

class SpawnerComp : public Component {
	public:
		SpawnerComp(GameObject* gameObject, const char* tag);
		~SpawnerComp() override;

		SpawnerComp(const SpawnerComp& other);

		void Start() override;
		void Update(float delta) override;
		void End() override;

		JSON_REGISTER_HEADER(SpawnerComp);

	private:
		Component* _clone(const GameObject& parent) override;

		float counter{0};
		std::unique_ptr<GameObject> projectilePrefab;
		GameObject* container;
};

JSON_REGISTER_COMPONENT(SpawnerComp);

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_SPAWNERCOMP_HPP_
