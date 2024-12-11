//
// Created by larsv on 10/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_CAMERA_HPP_
#define BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_CAMERA_HPP_

#include <glm/vec2.hpp>

class Camera {
	public:
		Camera() : _position(0.f), _boundary(100.f) {}
		Camera(glm::vec2 position, glm::vec2 boundary) :
		_position(position), _boundary(boundary) {}
		~Camera() = default;

		//Increments
		inline void Translate(float x, float y) {
			_position.x += x;
			_position.y += y;

			if (_position.x < 0) _position.x = std::max(-_boundary.x, _position.x);
			else _position.x = std::min(_boundary.x, _position.x);
			if (_position.y < 0) _position.y = std::max(-_boundary.y, _position.y);
			else _position.y = std::min(_boundary.y, _position.y);
		}

		//Sets
		inline void SetPosition(float x, float y) {
			_position.x = x;
			_position.y = y;

			if (_position.x < 0) _position.x = std::max(-_boundary.x, _position.x);
			else _position.x = std::min(_boundary.x, _position.x);
			if (_position.y < 0) _position.y = std::max(-_boundary.y, _position.y);
			else _position.y = std::min(_boundary.y, _position.y);
		}
		inline void SetBoundary(float x, float y) {
			_boundary.x = x;
			_boundary.y = y;
		}

		//Gets
		[[nodiscard]] inline const glm::vec2& GetPosition() const { return _position; }

	private:
		glm::vec2 _position;
		glm::vec2 _boundary;
};

#endif //BLOCKYENGINE_ENGINE_MODULEMANAGER_MODULES_RENDERING_CAMERA_HPP_
