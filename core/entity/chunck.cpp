#include <header.h>

namespace dig { namespace entity {
	Chunck::Chunck(sf::RenderWindow *app) {
		this->type = "ent_chunck";
		this->app = app;
		this->shape = new sf::RectangleShape(sf::Vector2f(16, 16));
	}
	
	void Chunck::pos(float x, float y) {
		this->shape->setPosition((this->x = x), (this->y = y));
	}
	
	void Chunck::blockType(int n, float r) {
		if (n == 1) {
			int t = ((r != -1)? r * 55 : std::rand() % 55);
			this->shape->setFillColor(sf::Color(200 + t, 200 + t, 200 + t));
		} else {
			this->shape->setFillColor(sf::Color(125 + (25 * n), 0, 0));
		}
		
	}
	
	void Chunck::draw() {
		this->app->draw(*this->shape);
	}
	
	void Chunck::update() {
		
	}
}}