//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_HPP
#define BLOCKYENGINE_GAMEOBJECT_HPP

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <optional>

#include "gameObject/GameObjectTransform.hpp"
#include "components/Component.hpp"

/// The central element of Blocky Engine. Everything in a game made with Blocky Engine is driven by gameObjects and the behaviors tied to it in Components
/// Only the root of a prefab (or scene) should ever be instantiated by directly using the constructor.
/// When building within a prefab (or scene), AddChild() should always be used for either a new gameObject, or one from instantiating a prefab.
/// View gameObject's Update() method for more detailed information regarding a gameObject's behavior in the game cycle
class GameObject {
	public:
		//----- RULE OF FIVE
		/// Creates an emtpy gameObject with a new transform under the (optionally) given parent.
		/// It is discouraged to use this constructor directly, consider wrapping it through a unique_ptr.
		/// Only use this constructor for the root of a prefab, where parent is nullptr.
		/// Always use a variant of AddChild for any other purpose
		/// \param tag The tag that will be given to the new gameObject
		/// \param parent The reference to the parent from this side, retain the default nullptr for the root of a prefab.
		/// This gameObject will not actually be registered as a child of this parent.
		/// For this reason, using AddChild() instead is strongly recommended
		explicit GameObject(std::string tag, GameObject* parent = nullptr);
		/// Never use the deconstructor manually removing gameObjects, always use Destroy() which will cleanly remove this gameObject.
		/// This gameObject will first be marked as being deleted, to prevent redundant destruction loops.
		/// Secondly, all components will receive their End() call, right before being deconstructed themselves.
		/// All this gameObject's children will get deconstructed at last, causing a recursive deconstruction chain that tears down the hierarchy from this point
		~GameObject();

		/// Internally used when AddChild() is called using a prefab or when scenes are being switched, should never be manually used.
		/// This copy-constructor will manage rebinding all the connections between GameObject, Transform, Components and Children
		/// \param other The prefab that will be cloned
		GameObject(const GameObject& other);
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

		//----- CYCLE
		/// Called internally from the BlockyEngine's cycle, never use manually.
		/// This method cascade the update cycle to all its components, then to its children. It is called every frame, before the ModuleManager is updated.
		/// When this gameObject's transform (or any of its component's transforms) are updated in this cycle, they will be placed in the recalculationList.
		/// A GameObjectTransform automatically recalculates this gameObject's components, therefor they are not also added if the GameObject has been transformed.
		/// The update cycle is skipped if an earlier gameObject marks this one for deletion. It is also broken off when a component or child does the same.
		/// After updating each child, their mark for deletion will be checked. They will be added to a temporary list if they were marked.
		/// Children are removed at the end of the cycle, meaning siblings will still get updated before this one is removed
		/// \param delta Difference in time since last Update call
		/// \param recalculationList Builds a list (GameObject/Component)Transforms to be recalculated at the end of this game cycle 
		void Update(float delta, std::vector<std::reference_wrapper<Transform>>& recalculationList);

		//----- CHILD / PARENT
		/// Will set this gameObject's _isActive check. When this value is changed, Start() and End() will be called on all components accordingly.
		/// When _isActive is changed to true, this gameObject's transform will be recalculated. A change in active state will also cascades to all children.
		/// \param active Active state to set this gameObject to 
		/// \param force Bypasses the need 
		void SetActive(bool active, bool force = false);

		/// Creates an empty child object by the given tag that is parented to this gameObject.
		/// The newly created child will forcefully inherit Active state from parent.
		/// This gameObject has ownership over this child, till it is reparented.
		/// This means that this child will be destructed when this gameObject is
		/// \param childTag The tag that should be given to the child
		/// \return Reference to the newly created child
		GameObject& AddChild(std::string_view childTag);
		/// Creates a child according to the given prefab parented to this gameObject.
		/// The newly created child will forcefully inherit Active state from parent.
		/// This gameObject has ownership over this child, till it is reparented.
		/// This means that this child will be destructed when this gameObject is 
		/// \param prefab The prefab that should be cloned for the creation of this child
		/// \return Reference to the newly created child
		GameObject& AddChild(GameObject& prefab);

		/// Searches a child by a given tag in this gameObject. Can look recursively in the hierarchy if enabled
		/// \param t The tag of the child that should be searched
		/// \param recursive Enables recursive searching in the hierarchy, false by default. Can be expensive when used frequently
		/// \return A pointer to the first child matching the given tag, or nullptr if none was found
		GameObject* GetChild(const std::string& t, bool recursive = false);

		/// Attempts to remove a child by the given reference
		/// \param child Child that should be removed from this gameObject
		/// \return False of the given given child was not found in this gameObject's children list
		bool RemoveChild(GameObject& child);
		/// Attempts to remove a child by the given tag
		/// \param t Tag of the child that should be removed from this gameObject 
		/// \return False of the given given child was not found in this gameObject's children list
		bool RemoveChild(const std::string& t);

		/// Small inline getter for the children list
		/// \return Reference to the list of this gameObject's children
		inline const std::vector<std::unique_ptr<GameObject>>& GetChildren() const { return _children; };

		/// Reparents this gameObject to the given gameObject by transferring ownership.
		/// References and parent relations in gameObject and Transform will be changed.
		/// Reparenting fails if this gameObject finds itself in the new parent's lineage.
		/// On successful reparenting, this gameObjects transform and component's transforms will be recalculated. 
		/// This method is cancelled from the start if the this gameObject has no parent or is marked for deletion
		/// \param target Reference to the gameObject that will be the new parent
		void Reparent(GameObject& target);
		/// Forcefully sets parent references in this gameObject and its transform.
		/// Only used for manually overriding these variables during prefab instantiation, consider using Reparent instead
		/// \param target Reference to the gameObject that will be the new parent
		void SetParent(GameObject& target);
		/// Marks this gameObject for deletion. This will interrupt its Update() cycle to prevent any other components or children from being updated
		/// This gameObject will only be actually destroyed at the end of its parent's Update() cycle
		void Destroy();

		//----- COMPONENTS
		using ComponentsList = std::vector<std::unique_ptr<Component>>;

		/// Adds a new component of the given type to this gameObject by forwarding the given arguments.
		/// The owning gameObject reference will be set by this method and does not need to be passed as an argument to AddComponent<>().
		/// This gameObject has indefinite ownership over this component. This means that this component will be destructed when this gameObject is.
		/// These components are stored in an unordered map by type_index, each entry here is a vector of components in unique_ptr's
		/// If this gameObject is Active, Start() will immediately be called on the newly created component. 
		/// \tparam T The type of component to create, it must derive from Component
		/// \tparam Args Variadic argument pack that will be forwarded to T's constructor
		/// \param componentTag Tag that will be given to the component that will be created
		/// \param args Variadic argument pack that will be forwarded to T's constructor, this excludes the owning gameObject reference and tag
		/// \return Reference to the newly created component, already casted to T 
		template<typename T, typename... Args>
		T& AddComponent(const char* componentTag = "Untagged", Args&& ... args) {
			//Perform validity checks
			_componentValidityCheck<T>();
			const auto type = std::type_index(typeid(T));

			//Create component and call Start() on it
			auto typeIt = _components.find(type);
			std::unique_ptr<T> component = std::make_unique<T>(this, componentTag, std::forward<Args>(args)...);
			if (_isActive) {
				component->Start();
			}

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

		/// Will remove a component by the given type and tag.
		/// Completely removes the _components entry if it was the last of its type.
		/// If no component of the given type exists, nothing will happen
		/// \tparam T Type of the component that should be removed, must derive from Component
		/// \param componentTag Optional tag of the component that should be removed.
		/// Removes the first component that matches the given type if no tag was given
		template<typename T>
		void RemoveComponent(const std::string& componentTag = "") {
			std::optional<ComponentsList::iterator> componentIt = _findComponentByTag<T>(componentTag);

			if (componentIt) {
				//Call End()
				if (!_isActive) {
					(*componentIt.value())->End();
				}

				//Erase
				auto& typeList = _components[typeid(T)];
				typeList.erase(*componentIt);

				//Remove list if it's empty
				if (typeList.empty()) {
					_components.erase(typeid(T));
				}
			}
		}

		/// Gets the first component of the given type that matches the (optionally) given tag.
		/// If no tag is supplied, any component that matches the templated type will be returned 
		/// \tparam T Type of the component to get, must derive from Component
		/// \param componentTag Optional tag that needs to be matched, the first match will be returned.
		/// If no tag was given, the first component matching the given type will be returned
		/// \return Raw pointer to the first Component that matched the type and (optional) tag.
		/// Returns nullptr if no component was found matching the given type or tag
		template<typename T>
		T* GetComponent(const std::string& componentTag = "") {
			auto componentIt = _findComponentByTag<T>(componentTag);

			//Return tagged component cast to T* if found
			return componentIt ? static_cast<T*>((**componentIt).get()) : nullptr;
		}

		/// Small inline getter for the component list
		/// \return Reference to the list of this gameObject's components
		inline const std::unordered_map<std::type_index, ComponentsList>& GetComponents() const { return _components; };

		const std::string tag;
		GameObject* parent;
		std::unique_ptr<GameObjectTransform> transform;

		//----- USINGS
		using GameObjectList = std::vector<std::unique_ptr<GameObject>>;

		//----- CHILD / PARENT
		/// Internal method for actually performing the removeChild task, simply used to extract duplicate logic from the actual RemoveChild methods.
		/// Do not use this method manually (shouldn't even be possible), consider using one of the public alternatives
		/// \param child Iteration that points to the child that should be removed
		/// \return False of the given given child was not found in this gameObject's children list
		bool _removeChild(GameObjectList::iterator child);
		
		/// Internal method for actually performing the reparenting task.
		/// As preparation, this gameObject will try locating itself in its parent's children list. An error message will be logged when this is unsuccessful.
		/// When itself has been found, and a target is specified, the gameObject will first be moved from its current parent to the new parent.
		/// After that, the place in the old parent's children list when this gameObject used to be will be freed.
		/// If no target was given, this gameObject wasn't moved out of this list, meaning that calling this method with nullptr can and should be used as a clean self-destruct method.
		/// Lastly, the parent references in this gameObject and its transform will be reassigned to the target.
		/// This method is cancelled from the start if the this gameObject has no parent or is marked for deletion 
		/// \param target The GameObject to reparent to. This target should not be a descendant of this gameObject, or be nullptr to trigger a clean self-destruction
		void _reparent(GameObject* target);

		//----- COMPONENTS
		/// Simple inline static_assertion validity check for if the given component type derives from Component
		/// \tparam T Type of component to check the validity of
		template<typename T>
		inline void _componentValidityCheck() {
			//Assert that T derives Component
			static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		}

		/// Internally used for component lookups, don't use manually, consider using GetComponent<>().
		/// Finds an iterator to the component with the templated type and given tag
		/// \tparam T Type of component to find in this GameObject. Must derive from Component 
		/// \param componentTag Tag of the component to find. If left empty, the first match will be chosen
		/// \return Optionally returns an iterator pointing to the found component.
		/// Returns std::nullopt when no component of the given type existed or when the (non-empty) tag didn't match any component
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
		std::vector<GameObject*> _deletionList;

		bool _isActive;
		bool _isMarkedForDeletion;
};

#endif //BLOCKYENGINE_GAMEOBJECT_HPP