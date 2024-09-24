//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_H
#define BLOCKYENGINE_COMPONENT_H


class Component {
	public:
		Component() = delete;
		virtual void OnUpdate() = 0;
		virtual ~Component();
};


#endif //BLOCKYENGINE_COMPONENT_H
