#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	setupLine(HOW_MANY_POINTS, lineSegmentLength, temp_mass);

	guiName = "settings";
	gui.setup(guiName);
	gui.add(guiLabel.setup("  SETTINGS  ", ""));
	gui.add(lineSegmentLengthSlider.setup("Segment length", lineSegmentLength, 6, 50));
	gui.add(numOfPointsSlider.setup("Number of the segments", HOW_MANY_POINTS, 3, 50));
	gui.add(massSlider.setup("Mass of the last point", temp_mass, 3, 50));
}

//--------------------------------------------------------------
void ofApp::update(){

	deltaTime = 0.03;

	clearForce();
	springForce(lineSegmentLength);
	gravity();
	verlet();

	if (lineSegmentLengthSlider != lineSegmentLength
		|| numOfPointsSlider != HOW_MANY_POINTS
		|| massSlider != points[HOW_MANY_POINTS].mass) {

		lineSegmentLength = lineSegmentLengthSlider;
		HOW_MANY_POINTS = numOfPointsSlider; 
		temp_mass = massSlider;

		points.clear();
		setupLine(HOW_MANY_POINTS, lineSegmentLength, temp_mass);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	gui.draw();

	for (int i = 0; i < points.size(); i++) {

		if (i != points.size() - 1) {
			ofSetColor(ofColor(202, 188, 165));
			ofDrawLine(points[i].position, points[i + 1].position);
		}

		points[i].draw();
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

		points[i].force = { 0, 0 };

	}
}

void ofApp::springForce(int& _lineSegmentLength) {

	for (int i = 0; i < points.size() - 1; i++) {

		glm::vec2 directionalVector = points[i].position - points[i + 1].position;

		points[i].displacement = glm::distance(points[i].position, points[i + 1].position) - _lineSegmentLength;

		directionalVector = glm::normalize(directionalVector);

		glm::vec2 springForce = 1000 * points[i].displacement * directionalVector;

		points[i].force -= springForce;
		points[i + 1].force += springForce;

	}
}

void ofApp::gravity() {

	for (int i = 0; i < points.size(); i++) {
		
		// gravity vector
		glm::vec2 gravity = { 0.5, 9.81 };

		gravity *= points[i].mass;

		points[i].force += gravity;
	}
}

void ofApp::verlet() {

	for (int i = 0; i < points.size(); i++) {

		if (!points[i].isLocked) {

			glm::vec2 tempPositionOld = points[i].position;

			points[i].position = points[i].position + (points[i].position - points[i].positionOld) + deltaTime * deltaTime * (points[i].force / points[i].mass);

			points[i].positionOld = tempPositionOld;
		}

		else { }

	}
}

void ofApp::setupLine(int& _HOW_MANY_POINTS, int& _lineSegmentLength, int& _lastMass) {

	for (int i = 0; i <= _HOW_MANY_POINTS; i++) {

		Point newPoint;

		newPoint.setup(ofColor::gray, 2, 1, { startingPoint.x, startingPoint.y + i * _lineSegmentLength }, false);
		newPoint.force = { 0, 0 };

		if (i == 0) {
			newPoint.color = ofColor::white;
			newPoint.radius = 6;
			newPoint.isLocked = true;
		}

		if (i == _HOW_MANY_POINTS) {
			newPoint.color = ofColor::lightGoldenRodYellow;
			newPoint.radius = 10;
			newPoint.mass = _lastMass;
		}

		points.push_back(newPoint);
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
