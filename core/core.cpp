#include <header.h>

namespace dig {
	Core::Core() {
		this->app = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Graphics");
		this->app->setFramerateLimit(60);
		this->map = new Map(0);

		this->createGame();
		this->run();
	}
	
	void Core::createGame() {
		this->map->level += 1;
		this->map->clear(this);
		this->map->generate(this);
	
		entity::Player *tmp = new entity::Player(this->app);
		tmp->pos(this->map->startPosX, this->map->startPosY);
		tmp->setCore(this);
		this->entityList.push_back(tmp);
		this->player = tmp;
	}
	
	void Core::render() {
		std::vector<std::string>::iterator rit;
		for (rit = this->removeList.begin(); rit != this->removeList.end(); ++rit) {
			this->map->clearGrid(this, (*rit));
		}
		this->removeList.erase(this->removeList.begin(), this->removeList.end());	
		
		std::vector<Entity*>::iterator it;
		for (it = entityList.begin(); it != entityList.end(); ++it) {
			std::string type = (*it)->type;
			//dig::Logger::get()->log(type);
			if (type == "ent_chunck") {
				entity::Chunck *tmp = (entity::Chunck *)(*it);
				tmp->update();
				continue;
			}
			if (type == "ent_player") {
				entity::Player *tmp = (entity::Player *)(*it);
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
			if (type == "ent_player") {
				entity::Player *tmp = (entity::Player *)(*it);
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
			}
			
			sf::Vector2i position = sf::Mouse::getPosition(*this->app);
			this->player->setMouse(position.x, position.y);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				this->createGame();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				this->player->mining = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				this->player->jump();
			}
			this->player->vecX(
				((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ? 1 : 0) + ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) ? -1 : 0)
			);

			this->app->clear();
			this->render();
			this->app->display();
		}
	}
}