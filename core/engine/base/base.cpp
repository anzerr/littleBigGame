#include <header.h>

namespace dig {
	std::string Base::getGridCord(int x, int y) {
		std::string key;
		char num[21];
		int i;
		sprintf(num, "%d", x);
		i = 0;
		while (num[i]) {
			key += num[i];
			i++;
		}
		key += ",";
		sprintf(num, "%d", y);
		i = 0;
		while (num[i]) {
			key += num[i];
			i++;
		}
		return (key);
	}
}