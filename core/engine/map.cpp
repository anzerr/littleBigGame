#include <header.h>

namespace dig {
	Map::Map(int level) {
		this->level = level || 0;
		this->size = 16;
	}
	
	void Map::clear(Core *core) {
		core->entityList.erase(core->entityList.begin(), core->entityList.end());
	}
	
	void Map::generate(Core *core) {
		Seed *s = new Seed(this->level);
		
		for (int y = 1; y < ((600 / this->size) - 1); y++) {			
			for (int x = 1; x < ((800 / this->size) - 1); x++) {
				entity::Chunck *tmp = new entity::Chunck(core->app);
				float n = s->next() * 10;
				tmp->blockType((n < 6)? 1 : (n - 5), s->next());
				tmp->pos(16 * x, 16 * y);
				core->entityList.push_back(tmp);
			}
		}
	}
}