#include <header.h>

namespace dig {
	Core::Core() {
		this->app = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Graphics");
		this->app->setFramerateLimit(60);
		
		entityList.push_back(new entity::Chunck(this->app));
		
		this->createGame();
		this->run();
	}
	
	void Core::createGame() {
		// create game object
	}
	
	void Core::render() {
		
	}

	void Core::run() {
		while (this->app->isOpen()) {
			sf::Event event;
			while (this->app->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					this->app->close();
				}
			}

			this->app->clear();
			this->render();
			this->app->display();
		}
	}
}