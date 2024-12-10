//
// Created by larsv on 13/11/2024.
//

#ifndef BLOCKYENGINE_RENDERABLE_HPP
#define BLOCKYENGINE_RENDERABLE_HPP

#include "components/Component.hpp"
#include "glm/vec4.hpp"

enum RenderableType {
	RECTANGLE,
	ELLIPSE,
	SPRITE,
	ANIMATED,
	TEXT
};

class Renderable : public Component {
	public:
		Renderable(GameObject* gameObject, const char* tag, RenderableType renderableType, int layer = 0);
		~Renderable() override;

		Renderable(const Renderable& other) = default;
		
		void Start() override;
		void Update(float delta) override;
		void End() override;

		[[nodiscard]] inline RenderableType GetRenderableType() const { return _renderableType; };
		[[nodiscard]] inline int GetLayer() const { return _layer; }
		inline void SetLayer(int layer) { _layer = layer; }
		
	private:
		RenderableType _renderableType;
		int _layer;
};

#endif //BLOCKYENGINE_RENDERABLE_HPP