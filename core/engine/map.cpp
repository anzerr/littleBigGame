#include <header.h>

namespace dig {
	Map::Map(int level) {
		this->level = level || 0;
		this->size = 16;
		this->startPosX = 0;
		this->startPosY = 0;
	}
	
	void Map::clear(Core *core) {
		core->colGrid.clear();
		std::vector<Entity*>::iterator it = core->entityList.begin();
		while (it != core->entityList.end()) {
			delete *it;
			++it;
		}
		core->entityList.erase(core->entityList.begin(), core->entityList.end());
	}
	
	void Map::setGrid(Core *core, int x, int y, entity::Chunck *chunck) {
		core->colGrid[getGridCord(x, y)] = chunck;
	}
	
	void Map::clearGrid(Core *core, int x, int y) {
		this->clearGrid(core, getGridCord(x, y));
	}
	
	void Map::clearGrid(Core *core, std::string key) {
		dig::Logger::get()->log(key);
		std::map<std::string, Entity*>::iterator chunck = core->colGrid.find(key);
		if (chunck == core->colGrid.end()) {
			return;
		}
		
		std::vector<Entity*>::iterator it = core->entityList.begin();
		while (it != core->entityList.end()) {
			if ((*it) == (*chunck).second) {
				delete *it;
				core->entityList.erase(it);
				core->colGrid.erase(key);
				return;
			} else {
				++it;
			}
		}
	}
	
	void Map::branch(Core *core, Seed *s, int skip, int length, int startX, int startY) {
		int last = -1;
		int i = 0;
		int split = 0;
		if (length <= 1) {
			return;
		}
		while (i < length) {
			int side = ((length > 5 && split < 4) ? 4 : 3) * s->next();
			while (side == last && side == skip) {
				side = ((length > 5 && split < 4) ? 4 : 3) * s->next();
			}
			
			if (side == 4) {
				split += 1;
				this->branch(core, s, last, (length / 1.5) + 3, startX, startY);
			}
			last = side;
			
			
			if (side == 3) {
				this->clearGrid(core, (startX += -1), (startY += 0));
			}
			if (side == 2) {
				this->clearGrid(core, (startX += 1), (startY += 0));
			}
			if (side == 1) {
				this->clearGrid(core, (startX += 0), (startY += 1));
			}
			if (side == 0) {
				this->clearGrid(core, (startX += 0), (startY += -1));
			}
			i += 1;
		}
	}
	
	void Map::createVain(Core *core, Seed *s, int nodes, int type, float size, int maxSize, int startX, int startY) {
		int failedNode = 0;
		while (nodes > 0) {
			int zoneX = (size * s->next()) - (size / 2);
			int zoneY = (size * s->next()) - (size / 2);
			std::string pos = getGridCord(startX + zoneX, startY + zoneY);
			std::map<std::string, Entity*>::iterator it = core->colGrid.find(pos);
			dig::Logger::get()->log(pos);
			if (it != core->colGrid.end() && (*it).second->type == "ent_chunck") {
				entity::Chunck *tmp = (entity::Chunck *)(*it).second;
				if (tmp->blockType() == 1) {
					tmp->setBlockType(type, s->next());
					nodes += -1;
					failedNode = 0;
					size = size * 1.05;
					size = (size > maxSize) ? maxSize : size;
					this->nodeCount += 1;
					dig::Logger::get()->log("found space added");
					continue;
				}
			}
			
			if (failedNode > 10) {
				size = size * 1.1;
				size = (size > maxSize) ? maxSize : size;
				dig::Logger::get()->log("failed cap going up size");
				failedNode = 0;
			} else {
				dig::Logger::get()->log("failed trying again");
				failedNode += 1;
			}
			dig::Logger::get()->log(getGridCord(failedNode, 10));
			dig::Logger::get()->log(getGridCord(size, maxSize));
		}
		
	}
	
	void Map::generate(Core *core) {
		Seed *s = new Seed(this->level);
		int maxY = ((600 / this->size) - 1);
		int maxX = ((800 / this->size) - 1);
		
		for (int y = 1; y < maxY; y++) {			
			for (int x = 1; x < maxX; x++) {
				entity::Chunck *tmp = new entity::Chunck(core);
				tmp->setBlockType(1, s->next());
				this->setGrid(core, x, y, tmp);
				tmp->pos(this->size * x, this->size * y);
				core->entityList.push_back(tmp);
			}
		}
		
		bool start = false;
		int i = 10 + (2 * s->next());
		float size = (maxY / 16);
		while (i > 0) {
			int zoneX = (size * s->next()) - (size / 2);
			int zoneY = (size * s->next()) - (size / 2);
			if (!start) {
				this->startPosX = this->size * ((maxX / 2) + zoneX);
				this->startPosY = this->size * ((maxY / 2) + zoneY);
				start = true;
			}
			this->branch(core, s, 3 * s->next(), 126, (maxX / 2) + zoneX, (maxY / 2) + zoneY);
			size = size * 1.4;
			i += -1;
		}
		
		i = 3;
		size = (maxY / 12);
		this->nodeCount = 0;
		while (i > 0) {
			int zoneX = (size * s->next()) - (size / 2);
			int zoneY = (size * s->next()) - (size / 2);
			this->createVain(core, s, 32, 1 + i, (maxY / 12), maxY, (maxX / 2) + zoneX, (maxY / 2) + zoneY);
			size = size * 1.1;
			i += -1;
		}
		
	}
}