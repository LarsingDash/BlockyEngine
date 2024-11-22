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
		~Transform() = default;

		Transform(const Transform& other) = delete;
		Transform& operator=(const Transform& other) = delete;

		Transform(Transform&& other) noexcept = delete;
		Transform& operator=(Transform&& other) noexcept = delete;

		//GETTER
		const glm::vec2& GetLocalPosition();
		[[nodiscard]] const float& GetLocalRotation() const;
		const glm::vec2& GetLocalScale();

		glm::vec2 GetWorldPosition();
		[[nodiscard]] float GetWorldRotation() const;
		glm::vec2 GetWorldScale();

		//SETTER
		void Translate(float x, float y);
		void Translate(const glm::vec2&& position);
		void Rotate(const float&& rotation);
		void Scale(float x, float y);
		void Scale(const glm::vec2&& scale);

		GameObject& gameObject;

		//WORLD
		void RecalculateWorldMatrix();
		bool isMarkedForRecalculation;

	private:
		glm::vec2 _position;
		float _rotation;
		glm::vec2 _scale;

		glm::mat3 _worldMatrix;
		void _recalculateWorldMatrix(const glm::mat3& parent);
};

#endif //BLOCKYENGINE_TRANSFORM_HPP
