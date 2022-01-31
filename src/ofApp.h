#pragma once

#include "ofMain.h"
#include "ofxGui.h"
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

		int POINTS_Y;
		int POINTS_X;
		float GRAVITY_X;
		float GRAVITY_Y;
		int length;
		int temp_mass;
		int stiffness;

		glm::vec2 startingPoint;

		float deltaTime;

		int current;

		glm::vec2 gravity;

		std::vector<Point*> points;

		// clear force vector
		void clearForce();

		// calculate spring force and add it to force vect.
		void springForce(int& _lineSegmentLength);

		// calculate gravity force and add it to force vect.
		void applyGravity();

		// motion equation, verlet integration
		void verlet();

		// setup points vector
		void setupCloth(int& _POINTS_X, int& _POINTS_Y, int& _lineSegmentLength, int& _lastMass);

		// ------ CLOTH --------

		glm::vec2 size;

		// ------ GUI --------

		ofxPanel gui;
		ofxLabel guiLabel;
		ofxIntSlider slider_restlength;
		ofxIntSlider slider_points_x;
		ofxIntSlider slider_points_y;
		ofxFloatSlider slider_gravity_x;
		ofxFloatSlider slider_gravity_y;
		ofxIntSlider slider_mass;
		ofxIntSlider slider_stiffness;

		std::string guiName;
};
