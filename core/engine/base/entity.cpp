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
	
	void Entity::onCollide() {
		// placeholder
	}
	
	void Entity::pos(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
		
	bool Entity::isCollide(float ax, float ay, float aw, float bx, float by, float bw) {
		return !(
			((ay + aw) <= (by)) ||
			(ay >= (by + bw)) ||
			((ax + aw) <= bx) ||
			(ax >= (bx + bw))
		);
	}
	
	void Entity::physics() {
		float x = this->x + this->velocity->getX();
		float gravity = this->velocity->getY();
		float y = this->y + gravity;
		
		std::vector<Entity*>::iterator it;
		bool allowX = true;
		bool allowY = true;
		
		for (it = this->core->entityList.begin(); it != this->core->entityList.end(); ++it) {
			if ((*it) != this) {
				if (this->isCollide(x, this->y, this->hitboxsize, (*it)->x, (*it)->y, (*it)->hitboxsize)) {
					allowX = false;
					this->velocity->resetX();
				}
				if (this->isCollide(this->x, y, this->hitboxsize, (*it)->x, (*it)->y, (*it)->hitboxsize)) {
					allowY = false;
					this->velocity->resetY();
				}
			}
		}
		
		this->pos((allowX)? x : this->x, (allowY)? y : this->y);
	}
}