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
		
		// colors
		ofColor cRED = ofColor::paleVioletRed;
		ofColor cWHITE = ofColor::ghostWhite;

		Point staticPoint;
		Point activePoint;
		Point p3;
		Point p4;
		Point staticPoint2;
		Point p5;

		float deltaTime;

		std::vector<Point> points;
};
