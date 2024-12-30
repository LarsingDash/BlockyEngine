//
// Created by larsv on 30/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_

#include <string>

class GameObject;

namespace JsonUtil {
	void LoadFromString(GameObject& recipient, const std::string& text);
	void LoadFromFile(GameObject& recipient, const std::string& filePath);
	void SaveToFile(GameObject& gameObject, const std::string& filePath);
}

#endif //BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
