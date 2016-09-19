
#ifndef __X_H_INCLUDED__
#define __X_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdarg>
#include <string>
#include <cstdlib>
#include <ctime>

namespace dig {
	class Base {};
	
	class Entity: public Base {
		public:
			std::string type;
			sf::RenderWindow *app;
			float x;
			float y;
			void update();
			void draw();
	};
	
	class Seed: public Base {
		public:
			Seed(int s);
			int s;
			float next();
	};
	
	class Core;
	
	class Map: public Base {
		public:
			Map(int level);
			int level;
			int size;
			void clear(Core *core);
			void generate(Core *core);
	};
	
	class Core: public Base {
		Map *map;
		public:
			Core(void);
			sf::RenderWindow *app;
			std::vector<Entity*> entityList;
			void createWindow();
			void createGame();
			void render();
			void run();
	};
	
	class Logger: public Base {
		public:
			Logger();
			void log(std::string msg);
			static Logger* get();
		private:
			static Logger* m_pThis;
			static std::ofstream m_Logfile;
	};
	
	namespace entity {
		class Chunck: public Entity {
			public:
				sf::RectangleShape *shape;
				sf::RenderWindow *app;
				Chunck(sf::RenderWindow *app);
				void pos(float x, float y);
				void blockType(int n, float r);
				void update();
				void draw();
		};
	}
}

#endif 