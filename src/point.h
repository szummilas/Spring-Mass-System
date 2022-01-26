#pragma once
#include "ofMain.h"

class Point {
public:
	void setup(ofColor _color, float _radius, float _mass, glm::vec2 _positionAtStart, bool _isLocked);
	void draw();

	bool isMouseOnIt(glm::vec2& mousePosition);
	bool isClicked;
	bool isLocked;

	float radius;
	float mass;
	
	glm::vec2 position;
	glm::vec2 positionOld;
	glm::vec2 force;
	glm::vec2 velocity;

	ofColor color;
};

