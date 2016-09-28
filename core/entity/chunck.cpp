#include <header.h>

namespace dig { namespace entity {
	Chunck::Chunck(sf::RenderWindow *app) {
		this->type = "ent_chunck";
		this->hitboxsize = 16;
		this->app = app;
		this->shape = new sf::RectangleShape(sf::Vector2f(16, 16));
	}
	
	void Chunck::pos(float x, float y) {
		this->shape->setPosition((this->x = x), (this->y = y));
	}
	
	int Chunck::colType() {
		return (1);
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
			this->shape->setFillColor(sf::Color(125 + (125 * r), 0, 0));
		}
		if (n == 3) {
			this->shape->setFillColor(sf::Color(0, 125 + (125 * r), 0));
		}
		if (n == 4) {
			this->shape->setFillColor(sf::Color(0, 0, 125 + (125 * r)));
		}
	}
	
	void Chunck::draw() {
		this->app->draw(*this->shape);
	}
	
	void Chunck::update() {
		
	}
}}