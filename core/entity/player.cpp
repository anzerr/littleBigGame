#include <header.h>

namespace dig { namespace entity {
	Player::Player(dig::Core *core) {
		this->core = core;
		this->type = "ent_player";
		this->hitboxsize = 6;
		this->app = core->app;
		this->shape = new sf::RectangleShape(sf::Vector2f(6, 6));
		this->shape->setFillColor(sf::Color(255, 255, 0));
		//this->particles = new ParticleSystem(1000);
		
		this->tool = new sf::RectangleShape(sf::Vector2f(3, 6));
		this->tool->setFillColor(sf::Color(255, 0, 255));
		
		this->velocity = new dig::Velocity(0, 0);
		this->velocity->rampX(0.5)->rampY(1);
		this->isJump = -1;
		this->jumpStamina = 128;
		this->mouseX = 0;
		this->mouseY = 0;
		this->mining = 0;
	}
	
	
	void Player::setMouse(int x, int y) {
		this->mouseX = x;
		this->mouseY = y;
	}
	
	void Player::pos(float x, float y) {
		this->shape->setPosition((this->x = x), (this->y = y));
		
		float deltaX = this->x - this->mouseX;
		float deltaY = this->y - this->mouseY;
		float rad = std::atan2(deltaY, deltaX) + 1.5708; // In radians
		this->tool->setRotation(rad * (180 / 3.1415926535897));
		this->tool->setPosition(this->x + 3, this->y + 3);
	}
	
	void Player::vecX(float x) {
		this->velocity->setX(x);
	}
	
	void Player::vecY(float y) {
		this->velocity->setY(y);
	}
	
	void Player::jump() {
		if (this->isJump == -1 || this->jumpStamina > 0) {
			this->isJump = std::max(1, this->isJump + 1);
			this->jumpStamina += -1;
		}
	}
	
	void Player::draw() {
		this->app->draw(*this->shape);
		this->app->draw(*this->tool);
        //this->app->draw(this->particles);
	}
	
	bool Player::isCollide(float ax, float ay, float aw, float bx, float by, float bw) {
		return !(
			((ay + aw) < (by)) ||
			(ay > (by + bw)) ||
			((ax + aw) < bx) ||
			(ax > (bx + bw))
		);
	}
	
	void Player::update() {
		this->velocity->setY((this->isJump > 0)? -1 : 5);
		float x = this->x + this->velocity->getX();
		float gravity = this->velocity->getY();
		float y = this->y + gravity;
		
		bool allowX = true;
		bool allowY = true;
		std::vector<Entity*>::iterator it;
				
		// disable if falling
		/*if (gravity >= 0) {
			this->jumpStamina = 0;
		}*/
		
		float blockSize = 16;
		float endBlock = blockSize + this->hitboxsize;
		
		for (it = this->core->entityList.begin(); it != this->core->entityList.end(); ++it) {
			std::string type = (*it)->type;
			if (type != "ent_player") {
				if (this->mining) {
					float deltaX = this->x - this->mouseX;
					float deltaY = this->y - this->mouseY;
					float rad = std::atan2(deltaY, deltaX) + 3.14159;
					if (this->isCollide(this->x + (cos(rad) * 8), this->y + (sin(rad) * 8), 4, (*it)->x, (*it)->y, (*it)->hitboxsize)) {
						entity::Chunck *tmp = (entity::Chunck *)(*it);
						if (tmp->dig(1)) {
							this->core->removeList.push_back((*it));
						}
					}
				}
				
				if (this->isCollide(x, this->y, this->hitboxsize, (*it)->x, (*it)->y, (*it)->hitboxsize)) {
					allowX = false;
					this->velocity->resetX();
				}
				if (this->isCollide(this->x, y, this->hitboxsize, (*it)->x, (*it)->y, (*it)->hitboxsize) || y == (600.0f - endBlock)) {
					allowY = false;
					if (gravity >= 0) {
						this->isJump = -1;
						this->jumpStamina = 128;
					}
					this->velocity->resetY();
				}
			}
		}
		this->mining = 0;
		
		/*sf::Time elapsed = clock.restart();
        this->particles->update(elapsed);*/
		
		this->pos(std::min(800.0f - endBlock, std::max(0.0f + blockSize, (allowX)? x : this->x)), std::min(600.0f - endBlock, std::max(0.0f + blockSize, (allowY)? y : this->y)));
		if (this->isJump != -1) {
			this->isJump = std::max(0, this->isJump - 1);
		}
	}
}}