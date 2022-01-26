#include "point.h"

void Point::setup(ofColor _color, float _radius, float _mass, glm::vec2 _positionAtStart, bool _isLocked) {
	color = _color;
	
	radius = _radius;
	mass = _mass;
	position = _positionAtStart;
	positionOld = _positionAtStart;
	isLocked = _isLocked;
	
	velocity = { 0, 0 };
	force = { 0, 0 };

	isClicked = false;
}

void Point::draw() {
	ofSetColor(color);
	ofDrawCircle(position, radius);
}

bool Point::isMouseOnIt(glm::vec2& mousePosition) {

	float distance = sqrt(pow((mousePosition.x - position.x), 2) + pow((mousePosition.y - position.y), 2));

	if (distance <= radius) { return true; }

	else { return false; }
}