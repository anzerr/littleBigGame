#include <header.h>

namespace dig { namespace entity {
	Chunck::Chunck(sf::RenderWindow *app) {
		this->app = app;
		this->shape = new sf::CircleShape(100.f);
		this->shape->setFillColor(sf::Color::Green);
		//app->draw(this->shape);
	}
	
	void Chunck::draw() {
		//this->app->draw(this->shape);
	}
	
	void Chunck::update() {
		
	}
}}