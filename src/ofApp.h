#pragma once

#include "ofMain.h"
#include "point.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		Point staticPoint;
		Point activePoint;
		Point p3;
		Point p4;
		Point staticPoint2;
		Point p5;

		int HOW_MANY_POINTS = 50;

		float lineSegmentLength = 10;

		glm::vec2 startingPoint = { ofGetWidth() / 2, 10 };

		float deltaTime;

		std::vector<Point> points;

		// clear force vector
		void clearForce();

		// calculate spring force and add it to force vect.
		void springForce();

		// calculate gravity force and add it to force vect.
		void gravity();

		// motion equation, verlet integration
		void verlet();

};
