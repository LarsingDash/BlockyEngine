//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_HPP
#define BLOCKYENGINE_COMPONENT_HPP

#include <memory>
#include <string>

#include "ComponentTransform.hpp"

class GameObject;

/// Components are the driving force behind any game made with Blocky Engine. Behavior of gameObjects can be defined by the components it has.
/// Components can be added, removed and gotten using the templated methods from their owning gameObjects.
class Component {
	public:
		/// Do not use the constructor for a component manually, consider using AddComponent<>() from the gameObject that will own it.
		/// This is the constructor for the base Component that sets the variables all components have.
		/// Derived classes should use the constructor for only this component's data  
		/// \param gameObject Pointer to the gameObject owning this Component, must be set and shouldn't be changed
		/// \param tag Tag that will be given to this component, the default tag given by AddComponent is "Untagged"
		/// \param hasTransform Decides if this component should have a separate ComponentTransform. Is off by default to save memory
		Component(GameObject* gameObject, const char* tag, bool hasTransform = false);

		/// Required to override in derived components, though if it's default it will be done implicitly.
		/// Just like the constructor, derived classes should only use the destructor for this component's data
		virtual ~Component() = default;

		/// Internally used when AddChild() is called on a gameObject using a prefab or when scenes are being switched, should never be manually used.
		/// This copy-constructor will manage rebinding all the connections between GameObject, Transform and Components.
		/// \param other The component from the prefab that should be cloned
		Component(const Component& other);
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(Component&& other) noexcept = delete;

		/// Internally used when AddChild() is called on a gameObject using a prefab or when scenes are being switched, should never be manually used.
		/// CloneInternal() will call the implementation specific component's _clone() to reach the derived class.
		/// After cloning the derived class, the gameObject pointer and all references in the componentTransform (if present) will be rebound 
		/// \param parent The new gameObject that this component will be cloned to, used to rebind references
		/// \return Raw pointer to the newly cloned Component, will be wrapped in a unique_ptr in the calling gameObject's prefab instantiation
		Component* CloneInternal(GameObject& parent);
		
		/// Start() is called once on creation of this gameObject if said gameObject is active. It is called immediately after the constructor, do not call Start() manually.
		/// Where the constructor is only meant for constructing this component's data, Start() should only be used for interacting with other gameObjects, components, or modules, such as subscribing listeners.
		/// Start() is called again when the owning gameObject gets changed to Active
		virtual void Start() = 0;
		/// Update() is called once on each component during the owning gameObject's Update(), do not use manually.
		/// Components are stored by type in an unordered map in the owning gameObject, meaning the order of execution between components is not guaranteed to be consistent
		/// \param delta Difference in time since last Update call
		virtual void Update(float delta) = 0;
		/// End() is called during destruction of this gameObject if said gameObject is active. This component's destructor is called immediately this, do not call End() manually.
		/// Where the destructor is only meant for destructing this component's data, End() should only be used for interacting with other gameObjects, components, or modules, such as unsubscribing listeners.
		/// End() is called again when the owning gameObject gets changed to InActive
		virtual void End() = 0;

		std::string tag;
		GameObject* gameObject;
		std::unique_ptr<ComponentTransform> componentTransform;

	private:
		/// Implementation specific method for cloning a component for use in a newly instantiated prefab.
		/// This private _clone() method is called from the public CloneInternal() method and should also not be used manually.
		/// However, _clone() should always be explicitly overridden. See the template in the README on how this method should be implemented
		/// \param parent The new gameObject that this component will be cloned to, can be used to rebind references if needed
		/// \return Raw pointer to the newly cloned Component, will be wrapped in a unique_ptr in the calling gameObject's prefab instantiation
		virtual Component* _clone(const GameObject& parent) = 0;
		bool _hasTransform;
};

#endif //BLOCKYENGINE_COMPONENT_HPP
