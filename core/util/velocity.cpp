#include <header.h>

namespace dig {
	Velocity::Velocity(float x, float y) {
		this->_wordX = x;
		this->_wordY = y;
		this->_rampX = 0;
		this->_rampY = 0;
		this->x = 0;
		this->y = 0;
		this->_curX = 0;
		this->_curY = 0;
	}
	
	Velocity *Velocity::rampX(float x) {
		this->_rampX = x;
		return (this);
	}
	
	Velocity *Velocity::rampY(float y) {
		this->_rampY = y;
		return (this);
	}
	
	Velocity *Velocity::setX(float x) {
		this->_curX = x;
		return (this);
		
	}
	
	Velocity *Velocity::setY(float y) {
		this->_curY = y;
		return (this);
	}
	
	Velocity *Velocity::resetX() {
		this->x = 0;
		return (this);
	}
	
	Velocity *Velocity::resetY() {
		this->y = 0;
		return (this);
	}
	
	float Velocity::getX() {
		if (this->_curX > this->x) {
			this->x = std::min((1 * this->_rampX) + this->x, this->_curX) + this->_wordX;
		} else {
			this->x = std::max((-1 * this->_rampX) + this->x, this->_curX) + this->_wordX;
		}
		return (this->x);
	}
	
	float Velocity::getY() {
		if (this->_curY > this->y) {
			this->y = std::min((1 * this->_rampY) + this->y, this->_curY) + this->_wordY;
		} else {
			this->y = std::max((-1 * this->_rampY) + this->y, this->_curY) + this->_wordY;
		}
		return (this->y);
	}
}