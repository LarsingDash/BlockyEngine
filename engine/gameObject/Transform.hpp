//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_TRANSFORM_HPP
#define BLOCKYENGINE_TRANSFORM_HPP

class GameObject;

#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"

/// Transform is amongst the most essential classes of Blocky Engine as it facilitates one of the most important aspects of a game: transformations
/// The Transform class is the base that contains nearly all logic regarding transformations.
/// It is only derived to GameObject- and ComponentTransform for specific recalculation behavior
class Transform {
	public:
		/// Transforms should only be created by gameObjects or components, do not use manually
		/// \param gameObject Reference to the owning gameObject
		explicit Transform(GameObject& gameObject);
		/// Deconstructor for deleting all data, since all GLM structs are trivially deletable, this can be default.
		/// Deconstruction is also handled by the owning gameObject or component, do not use manually
		virtual ~Transform() = default;

		// Trivial copy-constructor used in prefab instantiation, do not use manually
		Transform(const Transform& other) = default;
		Transform& operator=(const Transform& other) = delete;

		Transform(Transform&& other) noexcept = delete;
		Transform& operator=(Transform&& other) noexcept = delete;

		//GETTER
		[[maybe_unused]] [[nodiscard]] const glm::vec2& GetLocalPosition() const;
		[[maybe_unused]] [[nodiscard]] float GetLocalRotation() const;
		[[maybe_unused]] [[nodiscard]] const glm::vec2& GetLocalScale() const;

		[[maybe_unused]] [[nodiscard]] const glm::vec2& GetWorldPosition() const;
		[[maybe_unused]] [[nodiscard]] float GetWorldRotation() const;
		[[maybe_unused]] [[nodiscard]] const glm::vec2& GetWorldScale() const;

		//SETTER
		/// Increments this transform's position in local-space. This marks this transform for recalculation, which will be done at the end of the frame
		[[maybe_unused]] void Translate(float x, float y);
		/// Increments this transform's rotation in local-space. This marks this transform for recalculation, which will be done at the end of the frame
		[[maybe_unused]] void Rotate(float rotation);
		/// Increments this transform's scale in local-space. This marks this transform for recalculation, which will be done at the end of the frame
		[[maybe_unused]] void Scale(float x, float y);

		/// Sets this transform's position in local-space. This marks this transform for recalculation, which will be done at the end of the frame
		[[maybe_unused]] void SetPosition(float x, float y);
		/// Sets this transform's rotation in local-space. This marks this transform for recalculation, which will be done at the end of the frame
		[[maybe_unused]] void SetRotation(float rotation);
		/// Sets this transform's scale in local-space. This marks this transform for recalculation, which will be done at the end of the frame
		[[maybe_unused]] void SetScale(float x, float y);

		GameObject* gameObject;

		//WORLD
		/// Internal method for overriding the parenting transform, used in prefab instantiation and reparenting. Do not use manually
		void SetParent(Transform& target);
		/// Internal method for overriding the owning gameObject, used in prefab instantiation and reparenting. Do not use manually
		void SetGameObject(GameObject& target);
		
		/// This method recalculates this transform's world matrix according to its local transformations, relative to its parenting transform (unless its the root).
		/// Recalculation should be automatically called when it is needed, it's generally not recommended to do this manually.
		/// At the end of the recalculations, world transformations are extracted and cached for more efficient access, at the cost of a slight memory increase.
		/// GameObjectTransform recalculates itself, then its owning gameObject's components and then its owning gameObject's children. ComponentTransform only recalculates itself.
		/// RecalculateWorldMatrix() is only for the behavior defining what gets recalculated, the actual task gets performed in _recalculateWorldMatrix() 
		virtual void RecalculateWorldMatrix() = 0;
		bool isMarkedForRecalculation;

	protected:
		Transform* _parent;
		glm::mat3 _worldMatrix;
		
		/// Internal method for performing the actual task of recalculating this transform's world matrix according to its local transformations,
		/// relative to its parenting transform (unless it's the root). This method also unmarks this transform for recalculation.
		/// First, a local-space transformation matrix (3x3) is build in the order of translation, rotation and scale.
		/// Secondly, this transform's world matrix, world rotation and world scale are set by multiplying the parent's variants (if present) with the local variants.
		/// Lastly, the world location is extracted from the newly updated world matrix
		void _recalculateWorldMatrix();

	private:
		glm::vec2 _position;
		float _rotation;
		glm::vec2 _scale;

		glm::vec2 _worldPosition;
		float _worldRotation;
		glm::vec2 _worldScale;
};

#endif //BLOCKYENGINE_TRANSFORM_HPP
