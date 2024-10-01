//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_TRANSFORM_HPP
#define BLOCKYENGINE_TRANSFORM_HPP

class GameObject;

#include <vector>
#include <algorithm>
#include <memory>
#include "vec2.hpp"
#include "mat3x3.hpp"

class Transform {
	public:
		GameObject& gameObject;

		explicit Transform(GameObject& gameObject);
		~Transform() = default;

		Transform(const Transform& other) = delete;
		Transform& operator=(const Transform& other) = delete;

		Transform(Transform&& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		//GETTER
		const glm::vec2& GetLocalPosition();
		[[nodiscard]] const float& GetLocalRotation() const;
		const glm::vec2& GetLocalScale();

		//SETTER
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2&& position);
		void SetLocalRotation(const float&& rotation);
		void SetLocalScale(float x, float y);
		void SetLocalScale(const glm::vec2&& scale);

		//WORLD
		const glm::vec2 GetWorldPosition();
		const float GetWorldRotation();
		const glm::vec2 GetWorldScale();

	private:
		//TODO this position and scale is dependent on the resolution of the window, convert to consistent units
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;

		glm::mat3 worldMatrix;

		void RefreshWorldMatrix();
		glm::mat3 RecalculateWoldMatrix();
};

#endif //BLOCKYENGINE_TRANSFORM_HPP
