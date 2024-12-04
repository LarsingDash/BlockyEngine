//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_RECTANGLERENDERABLE_HPP
#define BLOCKYENGINE_RECTANGLERENDERABLE_HPP

#include <glm/vec4.hpp>
#include "Renderable.hpp"

class RectangleRenderable : public Renderable {
	public:
		RectangleRenderable(GameObject* gameObject, const char* tag,
							const glm::ivec4& color, bool isFilled = false);
		~RectangleRenderable() override = default;

		Component* _cloneImpl(GameObject& parent) override;
		
		[[nodiscard]] glm::ivec4 GetColor() const;
		[[nodiscard]] bool IsFilled() const;
		void SetColor(const glm::vec4& color);

	private:
		glm::ivec4 _color;
		bool _isFilled;
};

#endif //BLOCKYENGINE_RECTANGLERENDERABLE_HPP
