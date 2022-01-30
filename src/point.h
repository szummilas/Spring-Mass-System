#pragma once
#include "ofMain.h"

class Point;

class Link {
public:
	Point* p1;
	Point* p2;

	float k;
};

class Point {
public:

	Point();

	void setup(ofColor _color, float _radius, float _mass, glm::vec2 _positionAtStart, bool _isLocked);
	void draw();

	void SpringForce(int& _lineSegmentLength);
	void Verlet(bool& _isLocked, float& _deltaTime);

	//bool isMouseOnIt(glm::vec2& mousePosition);
	bool isClicked;
	bool isLocked;

	unsigned int id;
	glm::vec2 grid;

	float radius;
	float mass;
	float displacement;
	
	glm::vec2 position;
	glm::vec2 positionOld;
	glm::vec2 force;
	glm::vec2 velocity;

	ofColor color;

	std::vector<Link> links;
};

