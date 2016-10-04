#include <header.h>

namespace dig { namespace entity {
	Chunck::Chunck(dig::Core *core) {
		this->core = core;
		this->type = "ent_chunck";
		this->hitboxsize = 16;
		this->awake = 0;
		this->health = 60;
		this->hit = 0;
		this->beingHit = 0;
		this->app = core->app;
		this->shape = new sf::RectangleShape(sf::Vector2f(16, 16));
		this->velocity = new dig::Velocity(0, 0);
		this->velocity->rampX(0.5)->rampY(1);
	}
	
	void Chunck::pos(float x, float y) {
		this->shape->setPosition((this->x = x), (this->y = y));
	}
	
	int Chunck::colType() {
		return (1);
	}
	
	bool Chunck::dig(int i) {
		this->health = this->health - i;
		this->awake = 1;
		this->beingHit = 1;
		if (this->blockTypeValue != 1 && this->health < 0) {
			this->core->nodesMined += 1;
		}
		return (this->health < 0);
	}
	
	int Chunck::blockType() {
		return (this->blockTypeValue);
	}
	
	void Chunck::setBlockType(int n, float r) {
		this->blockTypeValue = n;
		if (n == 1) {
			int t = ((r != -1)? r * 55 : std::rand() % 55);
			this->shape->setFillColor(sf::Color(200 + t, 200 + t, 200 + t));
		}
		if (n == 2) {
			this->shape->setFillColor(sf::Color(180 + (75 * r), 0, 0));
		}
		if (n == 3) {
			this->shape->setFillColor(sf::Color(0, 180 + (75 * r), 0));
		}
		if (n == 4) {
			this->shape->setFillColor(sf::Color(0, 0, 180 + (75 * r)));
		}
	}
	
	void Chunck::draw() {
		this->app->draw(*this->shape);
	}
	
	void Chunck::update() {
		if (this->beingHit) {
			this->hit += 0.4;
			this->beingHit = 0;
		} else {
			this->hit = 0;
		}
		
		if (this->blockTypeValue != 1) {
			if (this->awake) {
				this->velocity->setY(5);
				this->physics();
			}
		}
		if (this->hit == 0) {
			this->shape->setPosition(this->x, this->y);
		} else {
			this->shape->setPosition(this->x + (cos(this->hit) * 1), this->y + (cos(this->hit) * 1));
		}
	}
}}