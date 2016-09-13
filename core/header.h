
#ifndef __X_H_INCLUDED__
#define __X_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include <vector>

namespace dig {
	class Base {};
	
	class Entity: public Base {
		public:
			sf::RenderWindow *app;
			int x;
			int y;
			void update();
			void draw();
	};
	
	class Core: public Base {
		sf::RenderWindow* app;
		public:
			Core(void);
			std::vector<Entity*> entityList;
			void createWindow();
			void createGame();
			void render();
			void run();
	};
	
	namespace entity {
		class Chunck: public Entity {
			public:
				sf::CircleShape *shape;
				sf::RenderWindow *app;
				Chunck(sf::RenderWindow *app);
				void update();
				void draw();
		};
	}
}

#endif 