#include <header.h>

namespace dig {
	void Entity::draw() {
		dig::Logger::get()->log("render base");
	}
	
	void Entity::update() {
		dig::Logger::get()->log("update base");
	}
	
	void Entity::setCore(dig::Core *core) {
		this->core = core;
	}
}