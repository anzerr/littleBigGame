#include <header.h>

namespace dig {
	Seed::Seed(int s) {
		this->s = s;
	}
	
	float Seed::next() {
		this->s = (this->s * 9301 + 49297) % 233280;
		return (this->s / (233280.0));
	}
}