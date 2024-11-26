//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_HPP
#define BLOCKYENGINE_GAMEOBJECT_HPP

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <optional>

#include "gameObject/GameObjectTransform.hpp"
#include "components/Component.hpp"

class GameObject {
	public:
		//----- RULE OF FIVE
		explicit GameObject(std::string tag, GameObject* parent = nullptr);
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

		//----- CYCLE
		void Update(float delta, std::vector<std::reference_wrapper<Transform>>& recalculationList);

		//----- CHILD / PARENT
		template<typename... Args>
		GameObject& AddChild(Args&& ... args) {
			//Instantiate new GameObject in this children list
			_children.emplace_back(std::make_unique<GameObject>(std::forward<Args>(args)..., this));

			//Return newly created child
			return *_children.back();
		}

		GameObject* GetChild(const std::string& t);

		bool RemoveChild(GameObject& child);
		bool RemoveChild(const std::string& t);

		inline const std::vector<std::unique_ptr<GameObject>>& GetChildren() const { return _children; };

		//----- COMPONENTS
		using ComponentsList = std::vector<std::unique_ptr<Component>>;

		template<typename T, typename... Args>
		T& AddComponent(const char* componentTag = "Untagged", Args&& ... args) {
			//Perform validity checks
			_componentValidityCheck<T>();
			const auto type = std::type_index(typeid(T));

			//Create component and call Start() on it
			auto typeIt = _components.find(type);
			std::unique_ptr<T> component = std::make_unique<T>(*this, componentTag, std::forward<Args>(args)...);
			component->Start();

			//Find component list, create it if there was none
			if (typeIt == _components.end()) {
				//Create new list with the 
				auto& typeList = _components[type];
				return static_cast<T&>(*typeList.emplace_back(std::move(component)));
			} else {
				//Add new component to existing list
				return static_cast<T&>(*typeIt->second.emplace_back(std::move(component)));
			}
		}

		template<typename T>
		void RemoveComponent(const std::string& componentTag = "") {
			std::optional<ComponentsList::iterator> componentIt = _findComponentByTag<T>(componentTag);

			if (componentIt) {
				//Call End()
				(*componentIt.value())->End();

				//Erase
				auto& typeList = _components[typeid(T)];
				typeList.erase(*componentIt);

				//Remove list if it's empty
				if (typeList.empty()) {
					_components.erase(typeid(T));
				}
			}
		}

		template<typename T>
		T* GetComponent(const std::string& componentTag = "") {
			auto componentIt = _findComponentByTag<T>(componentTag);

			//Return tagged component cast to T* if found
			return componentIt ? static_cast<T*>((**componentIt).get()) : nullptr;
		}

		inline const std::unordered_map<std::type_index, ComponentsList>& GetComponents() { return _components; };

		const std::string tag;
		GameObject* parent;
		std::unique_ptr<GameObjectTransform> transform;

	private:
		//----- USINGS
		using GameObjectList = std::vector<std::unique_ptr<GameObject>>;

		//----- CHILD / PARENT
		bool _removeChild(GameObjectList::iterator child);

		//----- COMPONENTS
		template<typename T>
		inline void _componentValidityCheck() {
			//Assert that T inherits Component
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		}

		//Finds an iterator to the component with the templated tag and given tag
		//If the component was found, the given pointer will be set to it
		template<typename T>
		std::optional<ComponentsList::iterator> _findComponentByTag(const std::string& componentTag) {
			//Perform Validity Checks
			_componentValidityCheck<T>();

			//Find position of T and return nullptr if it wasn't found or the list was empty
			const auto typeIt = _components.find(std::type_index(typeid(T)));
			if (typeIt == _components.end() || typeIt->second.empty()) return std::nullopt;

			//If no tag was given: return first component cast to T*
			if (componentTag.empty()) {
				return std::optional{typeIt->second.begin()};
			}

			//Search for specific component by the given tag
			auto& typeList = typeIt->second;
			const auto componentIt = std::find_if(typeList.begin(), typeList.end(),
												  [&componentTag](const std::unique_ptr<Component>& comp) {
													  return comp->tag == componentTag;
												  });

			return (componentIt != typeList.end()) ? std::optional{componentIt} : std::nullopt;
		}

		std::unordered_map<std::type_index, ComponentsList> _components;
		std::vector<std::unique_ptr<GameObject>> _children;
};

#endif //BLOCKYENGINE_GAMEOBJECT_HPP