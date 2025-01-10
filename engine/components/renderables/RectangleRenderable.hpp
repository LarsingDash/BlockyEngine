//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RECTANGLERENDERABLE_HPP
#define BLOCKYENGINE_RECTANGLERENDERABLE_HPP

#include <glm/vec4.hpp>

#include "Renderable.hpp"
#include "utilities/JsonUtil.hpp"

class RectangleRenderable : public Renderable {
	public:
		RectangleRenderable(GameObject* gameObject, const char* tag,
							const glm::ivec4& color, int layer = 0, bool isFilled = false);
		~RectangleRenderable() override = default;

		[[nodiscard]] glm::ivec4 GetColor() const;
		[[nodiscard]] bool IsFilled() const;
		void SetColor(const glm::vec4& color);

		JSON_REGISTER_HEADER(RectangleRenderable);

	private:
		Component* _clone(const GameObject& parent) override;

		glm::ivec4 _color;
		bool _isFilled;
};

JSON_REGISTER_COMPONENT(RectangleRenderable);

#endif //BLOCKYENGINE_RECTANGLERENDERABLE_HPP
