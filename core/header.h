
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
#include <cmath>

namespace dig {
	class Base {
		public:
			std::string intToString(int x) ;
			std::string getGridCord(int x, int y);
	};
	
	class Velocity {
		public:
			Velocity(float x, float y);
			float x;
			float y;
			float _wordX;
			float _wordY;
			float _rampX;
			float _rampY;
			float _curX;
			float _curY;
			Velocity *resetX();
			Velocity *resetY();
			Velocity *rampX(float x);
			Velocity *rampY(float y);
			Velocity *setX(float x);
			Velocity *setY(float y);
			float getX();
			float getY();
	};
	
	class Core;
	
	class Entity: public Base {
		public:
			std::string type;
			sf::RenderWindow *app;
			Velocity *velocity;
			dig::Core *core;
			float x;
			float y;
			float hitboxsize;
			void setCore(dig::Core *core);
			void pos(float x, float y);
			bool isCollide(float ax, float ay, float aw, float bx, float by, float bw);
			void onCollide();
			void physics();
			void update();
			void draw();
	};
	
	class Seed: public Base {
		public:
			Seed(int s);
			int s;
			float next();
	};
	
	namespace entity {
		class Chunck;
		class Player;
	}
	
	class Map: public Base {
		public:
			Map(int level);
			int level;
			int size;
			int nodeCount;
			int startPosX;
			int startPosY;
			void branch(Core *core, Seed *s, int skip, int length, int startX, int startY);
			void createVain(Core *core, Seed *s, int nodes, int type, float size, int maxSize, int startX, int startY);
			void clearGrid(Core *core, std::string);
			void clearGrid(Core *core, int x, int y);
			void setGrid(Core *core, int x, int y, entity::Chunck *chunck);
			void clear(Core *core);
			void generate(Core *core);
	};
	
	class Core: public Base {
		public:
			Core(void);
			Map *map;
			sf::Text *text;
			sf::RenderWindow *app;
			entity::Player *player;
			std::map<std::string, Entity*> colGrid;
			std::vector<Entity*> entityList;
			std::vector<Entity*> removeList;
			int nodesMined;
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
				Chunck(dig::Core *core);
				int awake;
				int health;
				int beingHit;
				float hit;
				bool dig(int i);
				int colType();
				int blockType();
				void pos(float x, float y);
				void setBlockType(int n, float r);
				void update();
				void draw();
		};
		
		class Player: public Entity {
			public:
				sf::RectangleShape *shape;
				sf::RectangleShape *tool;
				sf::RenderWindow *app;
				Player(dig::Core *core);
				int isJump;
				int jumpStamina;
				int mouseX;
				int mouseY;
				int mining;
				void setMouse(int x, int y);
				bool isCollide(float ax, float ay, float aw, float bx, float by, float bw);
				void pos(float x, float y);
				void vecX(float x);
				void vecY(float y);
				void jump();
				void update();
				void draw();
		};
	}
}

#endif 