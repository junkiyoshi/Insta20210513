#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	ofSetColor(39);
	ofDrawBox(218);

	ofSetColor(239);

	int span = 20;
	for (int i = 0; i < 6; i++) {

		for (auto x = -100; x <= 100; x += span) {

			for (int y = -100; y <= 100; y += span) {

				ofPushMatrix();

				if (i <= 3) {

					ofRotateX(i * 90);
				}
				else {

					i == 5 ? ofRotateY(90) : ofRotateY(270);
				}
				ofTranslate(x, y, 110);

				auto noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003);
				auto start_param = noise_value < 0.5 ? (noise_value < 0.45 ? 0 : ofMap(noise_value, 0.45, 0.5, 0, 25)) : 25;

				auto start = this->make_point(span, start_param);
				auto end = this->make_point(span, start_param + 50);

				ofDrawLine(start, end);
				ofDrawSphere(glm::vec3(start, 0), 4);
				ofDrawSphere(glm::vec3(end, 0), 4);

				ofPopMatrix();
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}