//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_TRANSFORM_HPP
#define BLOCKYENGINE_TRANSFORM_HPP

class GameObject;

#include "glm/vec2.hpp"
#include "glm/mat3x3.hpp"

class Transform {
	public:
		explicit Transform(GameObject& gameObject);
		virtual ~Transform() = default;

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
		[[maybe_unused]] void Translate(float x, float y);
		[[maybe_unused]] void Rotate(float rotation);
		[[maybe_unused]] void Scale(float x, float y);

		[[maybe_unused]] void SetPosition(float x, float y);
		[[maybe_unused]] void SetRotation(float rotation);
		[[maybe_unused]] void SetScale(float x, float y);

		GameObject* gameObject;

		//WORLD
		void SetParent(Transform& target);
		void SetGameObject(GameObject& target);
		virtual void RecalculateWorldMatrix() = 0;
		bool isMarkedForRecalculation;

	protected:
		Transform* _parent;
		glm::mat3 _worldMatrix;
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
