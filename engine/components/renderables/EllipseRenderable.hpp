//
// Created by 11896 on 15/11/2024.
//

#ifndef BLOCKYENGINE_ELLIPSERENDERABLE_HPP
#define BLOCKYENGINE_ELLIPSERENDERABLE_HPP

#include <glm/vec4.hpp>
#include "Renderable.hpp"

class EllipseRenderable : public Renderable {
	public:
		EllipseRenderable(GameObject* gameObject, const char* tag,
						  const glm::ivec4& color, int layer = 0, bool isFilled = false);
		~EllipseRenderable() override = default;

		[[nodiscard]] glm::ivec4 GetColor() const;
		[[nodiscard]] bool IsFilled() const;

	private:
		Component* _clone(const GameObject& parent) override;

		glm::ivec4 _color;
		bool _isFilled;
};

#endif //BLOCKYENGINE_ELLIPSERENDERABLE_HPP