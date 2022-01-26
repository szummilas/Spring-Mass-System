#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	staticPoint.setup(ofColor::paleVioletRed, 5, 1, { ofGetWidth() / 2, ofGetHeight() / 2 - 100}, true);
	activePoint.setup(ofColor::ghostWhite, 5, 1, { ofGetWidth() / 2, ofGetHeight() / 2 }, false);
	p3.setup(ofColor::aquamarine, 5, 1, { ofGetWidth() / 2, ofGetHeight() / 2 + 100 }, false);
	p4.setup(ofColor::lightBlue, 5, 1, { ofGetWidth() / 2, ofGetHeight() / 2 + 200 }, false);
	p5.setup(ofColor::lightCyan, 5, 1, { ofGetWidth() / 2 + 100, ofGetHeight() / 2 + 200 }, false);

	points.push_back(staticPoint);
	points.push_back(activePoint);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);

}

//--------------------------------------------------------------
void ofApp::update(){

	deltaTime = 0.03;

	for (int j = 0; j < points.size(); j++) {

		points[j].force = { 0, 0 };
	}

	for (int i = 0; i < points.size() - 1; i++) {

		//if (!points[i].isLocked) {

		// spring force

		glm::vec2 vecToNormalize = points[i].position - points[i + 1].position;

		float displacement = glm::distance(points[i].position, points[i + 1].position) - 100;

		vecToNormalize = glm::normalize(vecToNormalize);

		glm::vec2 springForce = 500 * displacement * vecToNormalize;

		points[i].force -= springForce;
		points[i + 1].force += springForce;

		//std::cout << "distance [" << i << "]: " << glm::distance(points[i].position, points[i + 1].position) << '\n';
		//std::cout << "displacement [" << i << "]: " << displacement << '\n';
	
		// drag
		//points[i].force += -6 * 3.14 * 17.8 * 10e-05 * points[i].radius * points[i].velocity;
				
		//points[i].velocity += (points[i].force / points[i].mass) * deltaTime;

		// ----------------

		/*if (points[i].isClicked) {

			points[i].position = glm::vec2(ofGetMouseX(), ofGetMouseY());

		}*/

	//}

		//std::cout << "[" << i << "]: " << points[i].force << '\n';

	}

	for (int i = 0; i < points.size(); i++) {
		// gravity force
		glm::vec2 gravity = { 9.8, 9.81 };

		gravity *= points[i].mass;

		points[i].force += gravity;
	}
	static int first = 0;


	/*if (first == 0)
	{
		for (int i = 1; i < points.size(); i++) {
			points[i].positionOld = points[i].position;

			points[i].velocity = points[i].velocity + points[i].force * deltaTime;
			points[i].position = points[i].position + points[i].velocity * deltaTime;
		}

		first++;
	}
	else {*/

	for (int i = 0; i < points.size(); i++) {

		if (!points[i].isLocked) {
			glm::vec2 tempPositionOld = points[i].position;

			points[i].position = points[i].position + (points[i].position - points[i].positionOld) + deltaTime * deltaTime * (points[i].force / points[i].mass);

			points[i].positionOld = tempPositionOld;
		}
		else {

		}
		// verlet
		
	}
	//}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	for (int i = 0; i < points.size(); i++) {
		points[i].draw();

		if (i != points.size() - 1) {
			ofDrawLine(points[i].position, points[i + 1].position);
		}
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

	if (activePoint.isMouseOnIt(glm::vec2(x, y)) && !activePoint.isClicked) {
		activePoint.isClicked = true;
	}

	else {
		activePoint.isClicked = false;
	}
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
