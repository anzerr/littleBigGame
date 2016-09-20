
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
#include <map>
#include <algorithm>

namespace dig {
	class Base {
		public:
			std::string getGridCord(int x, int y);
	};
	
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
	
	namespace entity {
		class Chunck;
	}
	
	class Map: public Base {
		public:
			Map(int level);
			int level;
			int size;
			void branch(Core *core, Seed *s, int skip, int length, int startX, int startY);
			void createVain(Core *core, Seed *s, int nodes, int type, float size, int maxSize, int startX, int startY);
			void clearGrid(Core *core, int x, int y);
			void setGrid(Core *core, int x, int y, entity::Chunck *chunck);
			void clear(Core *core);
			void generate(Core *core);
	};
	
	class Core: public Base {
		Map *map;
		public:
			Core(void);
			sf::RenderWindow *app;
			std::map<std::string, Entity*> colGrid;
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
			private:
				int blockTypeValue;
			public:
				sf::RectangleShape *shape;
				sf::RenderWindow *app;
				Chunck(sf::RenderWindow *app);
				int colType();
				int blockType();
				void pos(float x, float y);
				void setBlockType(int n, float r);
				void update();
				void draw();
		};
	}
}

#endif 