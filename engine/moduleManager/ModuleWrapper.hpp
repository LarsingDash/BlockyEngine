//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_MODULEWRAPPER_HPP
#define BLOCKYENGINE_MODULEWRAPPER_HPP

class ModuleWrapper {
	public:
		ModuleWrapper() = default;
		virtual ~ModuleWrapper() = default;

		virtual void Update(float delta) = 0;
};

#endif //BLOCKYENGINE_MODULEWRAPPER_HPP
