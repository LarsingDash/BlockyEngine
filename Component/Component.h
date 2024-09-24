//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_H
#define BLOCKYENGINE_COMPONENT_H

class Component {
	public:
		Component() = default;
		virtual void OnUpdate(float delta) = 0;
		virtual ~Component() = default;
};


#endif //BLOCKYENGINE_COMPONENT_H
