#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	setupLine(HOW_MANY_POINTS, lineSegmentLength, temp_mass);


	// ------ GUI --------

	guiName = "settings";
	gui.setup(guiName);
	gui.add(guiLabel.setup("  SETTINGS  ", ""));
	gui.add(lineSegmentLengthSlider.setup("Segment length", lineSegmentLength, 6, 50));
	gui.add(numOfPointsSlider.setup("Number of the segments", HOW_MANY_POINTS, 3, 50));
	gui.add(massSlider.setup("Mass of the last point", temp_mass, 3, 50));

	// ----- DEBUG -------

	std::cout << points.size() << '\n';
}

//--------------------------------------------------------------
void ofApp::update(){

	deltaTime = 0.03;

	clearForce();

	for (int i = 0; i < points.size(); i++) {

		points[i]->SpringForce(lineSegmentLength);
	
	}

	

	gravity();

	for (int i = 0; i < points.size(); i++) {

		points[i]->Verlet(points[i]->isLocked, deltaTime);

	}

	//verlet();

	// ------ GUI --------

	/*if (lineSegmentLengthSlider != lineSegmentLength
		|| numOfPointsSlider != HOW_MANY_POINTS
		|| massSlider != points[HOW_MANY_POINTS]->mass) {

		lineSegmentLength = lineSegmentLengthSlider;
		HOW_MANY_POINTS = numOfPointsSlider; 
		temp_mass = massSlider;

		points.clear();
		setupLine(HOW_MANY_POINTS, lineSegmentLength, temp_mass);
	}*/

}

//--------------------------------------------------------------
void ofApp::draw(){
	// ------ GUI --------

	gui.draw();


	// ------ OTHER --------

	for (int i = 0; i < points.size(); i++) {

		for (int j = 0; j < points[i]->links.size(); j++) {

			ofSetColor(ofColor(202, 188, 165));
			ofDrawLine(points[i]->links[j].p1->position, points[i]->links[j].p2->position);

		}
		
		points[i]->draw();

		//ofDrawBitmapString(points[i]->grid, points[i]->position);
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

void ofApp::springForce(int& _lineSegmentLength) {

	for (int i = 0; i < points.size() - 1; i++) {

		glm::vec2 directionalVector = points[i]->position - points[i + 1]->position;

		points[i]->displacement = glm::distance(points[i]->position, points[i + 1]->position) - _lineSegmentLength;

		directionalVector = glm::normalize(directionalVector);

		glm::vec2 springForce = 1000 * points[i]->displacement * directionalVector;

		points[i]->force -= springForce;
		points[i + 1]->force += springForce;

	}
}

void ofApp::gravity() {

	for (int i = 0; i < points.size(); i++) {
		
		// gravity vector
		glm::vec2 gravity = { -2.5, 9.81 };

		gravity *= points[i]->mass;

		points[i]->force += gravity;
	}
}

void ofApp::verlet() {

	for (int i = 0; i < points.size(); i++) {

		if (!points[i]->isLocked) {

			glm::vec2 tempPositionOld = points[i]->position;

			points[i]->position = points[i]->position + (points[i]->position - points[i]->positionOld) + deltaTime * deltaTime * (points[i]->force / points[i]->mass);

			points[i]->positionOld = tempPositionOld;
		}

		else { }

	}
}

void ofApp::setupLine(int& _HOW_MANY_POINTS, int& _lineSegmentLength, int& _lastMass) {

	size = { 81, HOW_MANY_POINTS };
	current = 0;

	for (int y = 0; y < size.y; y++) {
		
		for (int x = 0; x < size.x; x++) {

			Point* newPoint = new Point();

			newPoint->setup(ofColor::gray, 2, 1, { startingPoint.x + x * _lineSegmentLength, startingPoint.y + y * _lineSegmentLength }, false);
			newPoint->force = { 0, 0 };
			newPoint->id = current;
			newPoint->grid = { x, y };

			if (y == 0) {
				newPoint->color = ofColor::white;
				newPoint->radius = 2;
				newPoint->isLocked = true;
			}

			points.push_back(newPoint);
			current++;
		}
	}

	current = 0;

	for (int y = 0; y < size.y; y++) {

		for (int x = 0; x < size.x; x++) {

			if (y != 0) {

				int above = (y - 1) * size.x + x;

				Link l;
				l.p1 = points[current];
				l.p2 = points[above];

				points[current]->links.push_back(l);
			}

			if (x != 0) {
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
