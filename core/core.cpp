#include <header.h>

namespace dig {
	Core::Core() {
		this->app = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Graphics");
		this->app->setFramerateLimit(60);
		this->map = new Map(0);
		this->map->generate(this);
		
		this->createGame();
		this->run();
	}
	
	void Core::createGame() {
		// create game object
	}
	
	void Core::render() {
		std::vector<Entity*>::iterator it;
		
		for (it = entityList.begin(); it != entityList.end(); ++it) {
			std::string type = (*it)->type; 
			if (type == "ent_chunck") {
				entity::Chunck *tmp = (entity::Chunck *)(*it);
				tmp->update();
				continue;
			}
		}
		
		for (it = entityList.begin(); it != entityList.end(); ++it) {
			std::string type = (*it)->type; 
			if (type == "ent_chunck") {
				entity::Chunck *tmp = (entity::Chunck *)(*it);
				tmp->draw();
				continue;
			}
		}
	}

	void Core::run() {
		while (this->app->isOpen()) {
			sf::Event event;
			while (this->app->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					this->app->close();
				}
				
				if (event.type == sf::Event::KeyPressed){
					if (event.key.code == sf::Keyboard::Space) {
						this->map->level += 1;
						this->map->clear(this);
						this->map->generate(this);
					}
				}
			}

			this->app->clear();
			this->render();
			this->app->display();
		}
	}
}