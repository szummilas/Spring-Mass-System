#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	POINTS_Y = 60;
	POINTS_X = 80;
	GRAVITY_X = 0;
	GRAVITY_Y = 9.81;
	length = 6;
	temp_mass = 10;
	stiffness = 500;

	startingPoint = { ofGetWidth() / 2 - (POINTS_X * length / 2), 20 };

	setupCloth(POINTS_X, POINTS_Y, length, temp_mass);

	// ------ GUI --------

	guiName = "settings";
	gui.setup(guiName);
	gui.add(guiLabel.setup("GUI", ""));
	gui.add(slider_restlength.setup("length", length, 6, 50));
	gui.add(slider_points_x.setup("x", POINTS_Y, 1, 60));
	gui.add(slider_points_y.setup("y", POINTS_X, 6, 80));
	gui.add(slider_gravity_x.setup("gravity x", GRAVITY_X, -6, 6));
	gui.add(slider_gravity_y.setup("gravity y", GRAVITY_Y, 1, 10));
	gui.add(slider_stiffness.setup("stiffness", stiffness, 10, 600));

	// ----- DEBUG -------

}

//--------------------------------------------------------------
void ofApp::update(){

	// dt
	deltaTime = 0.03;

	// reset force vector
	clearForce();

	// add calculated spring force to each point
	for (int i = 0; i < points.size(); i++) {
		points[i]->SpringForce(length, stiffness);
	}

	// add gravity force to simulation
	applyGravity();

	// add drag to simulation
	applyDrag();

	// update points position based on verlet
	for (int i = 0; i < points.size(); i++) {
		points[i]->Verlet(points[i]->isLocked, deltaTime);
	}

	// ------ GUI --------
	int temp_points_x = POINTS_X;
	int temp_points_y = POINTS_Y;
	float temp_gravity_x = GRAVITY_X;
	float temp_gravity_y = GRAVITY_Y;
	int temp_length = length;
	int temp_stiffness = stiffness;

	if (temp_points_x != slider_points_x || temp_points_y != slider_points_y ||
		temp_gravity_x != slider_gravity_x || temp_gravity_y != slider_gravity_y ||
		temp_length != slider_restlength || temp_stiffness != slider_stiffness) {
		
		// x
		temp_points_x = slider_points_x;
		POINTS_X = temp_points_x;

		// y
		temp_points_y = slider_points_y;
		POINTS_Y = temp_points_y;

		// gravity x
		temp_gravity_x = slider_gravity_x;
		GRAVITY_X = temp_gravity_x;

		// gravity y
		temp_gravity_y = slider_gravity_y;
		GRAVITY_Y = temp_gravity_y;

		// length
		temp_length = slider_restlength;
		length = slider_restlength;

		// stiffness
		temp_stiffness = slider_stiffness;
		stiffness = slider_stiffness;

		points.clear();
		setupCloth(POINTS_X, POINTS_Y, length, temp_mass);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// ------ BACKGROUND --------
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	// ------ GUI --------
	gui.draw();

	// ------ POINTS AND LINKS --------
	for (int i = 0; i < points.size(); i++) {

		for (int j = 0; j < points[i]->links.size(); j++) {
			ofSetColor(ofColor::lightBlue);
			ofDrawLine(points[i]->links[j].p1->position, points[i]->links[j].p2->position);
		}
		
		points[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::clearForce() {

	for (int i = 0; i < points.size(); i++) {

		points[i]->force = { 0, 0 };
	}
}

void ofApp::applyDrag() {

	for (int i = 0; i < points.size(); i++) {

		// stokes' law -> F = 6 * pi * dynamic_viscosity * radius * velocity
		points[i]->force += -6 * 3.14 * 17.8 * 10e-05 * points[i]->radius * points[i]->velocity;
	}
}

void ofApp::applyGravity() {

	for (int i = 0; i < points.size(); i++) {
	
		// gravity vector
		gravity = { GRAVITY_X , GRAVITY_Y };

		// m * g
		gravity *= points[i]->mass;

		// F = m * g
		points[i]->force += gravity;
	}
}

void ofApp::verlet() {

	for (int i = 0; i < points.size(); i++) {

		// calculate verlet besides top points
		if (!points[i]->isLocked) {

			glm::vec2 tempPositionOld = points[i]->position;

			points[i]->position = points[i]->position + (points[i]->position - points[i]->positionOld) + deltaTime * deltaTime * (points[i]->force / points[i]->mass);

			points[i]->positionOld = tempPositionOld;

			// velocity for drag
			points[i]->velocity += (points[i]->force / points[i]->mass) / deltaTime;
		}

		else { }
	}
}

void ofApp::setupCloth(int& _POINTS_X, int& _POINTS_Y, int& _lineSegmentLength, int& _lastMass) {

	size = { POINTS_X, POINTS_Y };

	// number of current point in iteration
	current = 0;

	// TOP 
	//  |
	//  v
	// DOWN
	for (int y = 0; y < size.y; y++) {
		
		// LEFT -> RIGHT
		for (int x = 0; x < size.x; x++) {

			Point* newPoint = new Point();

			newPoint->setup(ofColor::gray, 2, 1, { startingPoint.x + x * _lineSegmentLength, startingPoint.y + y * _lineSegmentLength }, false);
			newPoint->force = { 0, 0 };
			newPoint->grid = { x, y };

			// top points
			if (y == 0) {
				newPoint->color = ofColor::red;
				newPoint->radius = 2;
				newPoint->isLocked = true;
			}

			points.push_back(newPoint);
			current++;
		}
	}

	current = 0;
	
	// setup links between points
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {

			// each point has two links 
			// one above the point 
			// and one on the left side
			// besides:
			// first column and last row
			if (y != 0) {

				/*            
					 
				[y=0]		0   -> above	 4
				[y=1]		|				 |
				  .			1	-> current	 5
				  .			|				 |
				  .			2				 6
				  .			|				 |
				[y=6]	   (3)			    (7)

				*/

				int above = (y - 1) * size.x + x;

				Link l;
				l.p1 = points[current];
				l.p2 = points[above];

				points[current]->links.push_back(l);
			}

			if (x != 0) {

				/*
						   [x=0]     [x=1]     [x=2]

						   left		  current
				[y=0]		0   ---   4   ---	(8)
				[y=1]		|		  |			 |
				  .			1   ---	  5   ---	(9)
				  .			|		  |			 |
				  .			2	---	  6   ---	(10)
				  .			|		  |			 |
				[y=6]	   (3)	---  (7)  ---	(11)
				 
				*/

				int left = current - 1;

				Link l;
				l.p1 = points[current];
				l.p2 = points[left];

				points[current]->links.push_back(l);
			}

			current++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
