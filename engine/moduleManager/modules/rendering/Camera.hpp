//
// Created by larsv on 10/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_CAMERA_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_CAMERA_HPP_

#include <glm/vec2.hpp>

class Camera {
	public:
		Camera() : _position(0.f), _horizontalBoundary(0.f), _verticalBoundary(0.f) {}
		Camera(glm::vec2 position, glm::vec2 horBoundary, glm::vec2 verBoundary) :
				_position(position), _horizontalBoundary(horBoundary), _verticalBoundary(verBoundary) {}
		~Camera() = default;

		//Increments
		inline void Translate(float x, float y) {
			_position.x += x;
			_position.y += y;

			_clamp();
		}

		//Sets
		inline void SetPosition(float x, float y) {
			_position.x = x;
			_position.y = y;

			_clamp();
		}

		inline void SetBoundary(float xMin, float xMax, float yMin, float yMax) {
			_horizontalBoundary.x = xMin;
			_horizontalBoundary.y = xMax;
			_verticalBoundary.x = yMin;
			_verticalBoundary.y = yMax;
		}

		//Gets
		[[nodiscard]] inline const glm::vec2& GetPosition() const { return _position; }

	private:
		inline void _clamp() {
			_position.x = std::max(_horizontalBoundary.x, std::min(_position.x, _horizontalBoundary.y));
			_position.y = std::max(_verticalBoundary.x, std::min(_position.y, _verticalBoundary.y));
		}

		glm::vec2 _position;
		glm::vec2 _horizontalBoundary;
		glm::vec2 _verticalBoundary;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_CAMERA_HPP_
