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
		glm::vec2 GetWorldPosition();
		float GetWorldRotation();
		glm::vec2 GetWorldScale();

	private:
		//TODO position and scale is dependent on the resolution of the window, convert to consistent units
		//TODO position is from topLeft to bottomRight, this isn't intuitive for scripting. (0, 0) should be the center
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;

		glm::mat3 worldMatrix;

		//TODO use flagging to refresh WorldMatrix once per frame (at the end), instead of after every Setter
		//	> Go from root downwards to find first transform that has this flag, then cascade downwards
		//		> Don't refresh parents, use their matrix. Since it's going downwards it's ensured that this parent is up-to-date
		void RefreshWorldMatrix();
		glm::mat3 RecalculateWoldMatrix();
};

#endif //BLOCKYENGINE_TRANSFORM_HPP
