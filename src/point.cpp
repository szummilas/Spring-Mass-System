#include "point.h"

Point::Point() {
}

void Point::setup(ofColor _color, float _radius, float _mass, glm::vec2 _positionAtStart, bool _isLocked) {
	color = _color;
	
	radius = _radius;
	mass = _mass;
	position = _positionAtStart;
	positionOld = _positionAtStart;
	isLocked = _isLocked;
	
	velocity = { 0, 0 };
	force = { 0, 0 };

	id = 0;
	grid = { 0, 0 };

	isClicked = false;
}

void Point::draw() {

	ofSetColor(color);
	ofDrawCircle(position, radius);

}

void Point::SpringForce(int& _lineSegmentLength) {

	for (int i = 0; i < links.size(); i++) {

		glm::vec2 directionalVector = links[i].p1->position - links[i].p2->position;

		links[i].p1->displacement = glm::distance(links[i].p1->position, links[i].p2->position) - _lineSegmentLength;

		directionalVector = glm::normalize(directionalVector);

		glm::vec2 springForce = 500 * links[i].p1->displacement * directionalVector;

		links[i].p1->force -= springForce;
		links[i].p2->force += springForce;
	}
}

void Point::Verlet(bool& _isLocked, float& _deltaTime) {

	if (!_isLocked) {

		glm::vec2 tempPositionOld = position;

		position = position + (position - positionOld) + _deltaTime * _deltaTime * (force / mass);

		positionOld = tempPositionOld;
	}
}

//bool Point::isMouseOnIt(glm::vec2& mousePosition) {
//
//	float distance = sqrt(pow((mousePosition.x - position.x), 2) + pow((mousePosition.y - position.y), 2));
//
//	if (distance <= radius) { return true; }
//
//	else { return false; }
//}