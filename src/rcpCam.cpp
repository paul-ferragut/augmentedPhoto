

#include "rcpCam.h"

#include "ofxGlm.h"

rcpCam::rcpCam() :imgPath("NONE"), R(1.0), t(0., 0., 0.), lat(0.0), lon(0.0), alt(0.0), f(0.0), k1(0.0), k2(0.0) {

}

rcpCam::~rcpCam() {

}

void rcpCam::setup(float w, float h, ofVec3f translation, ofVec3f rotation, ofVec2f principalPoint, double focalLenght, double radDistort1, double radDistort2,string imageS)
{
	width=w/2;
	height=h/2;

	t.x = translation.x;
	t.y = translation.y;
	t.z = translation.z;
	
	r.x = ofDegToRad(rotation.x);
	r.y = ofDegToRad(rotation.y);
	r.z = ofDegToRad(rotation.z);

	pp = principalPoint;
	f = focalLenght;
	//f = focalLenght;//*100;
	//fov = 2 * atan((0.5*width) / focalLenght);
	//f = 5334.57470703;
	//f = (width * 0.5) / tan(f * 0.5 * PI / 180);
	cout << "f" << f << endl;
	k1 = radDistort1;
	k2 = radDistort2;
	imgPath = imageS;
	cout << imgPath << endl;
	//cout << rotation << endl;
	glm::vec3 r2;
	r2.x = r.x; 
	r2.y = r.y;
	r2.z = r.z;

	

	//r = glm::normalize(r);
	//R = glm::eulerAngleYXZ(r2.y, r2.x, r2.z);
	//glm::quat q = glm::quat_cast(R);
	
	glm::quat q = glm::quat(glm::vec3(r.x, r.y, r.z));//glm::toQuat(glm::eulerAngleYXZ(r2.y, r2.x, r2.z));
	R = glm::mat3_cast(q);
	//glm::quat q = glm::quat_cast(R);
	setOrientation(ofQuaternion(q[0], q[1], q[2], q[3]));
	//cout << ofQuaternion(q[0], q[1], q[2], q[3]).getEuler() << endl;
	//glm::vec3 p = -R * t;
	glm::vec3 p =  t;
	setPosition(p[0], p[1], p[2]);

}

/*
void rcpCam::setIntrinsics() {
	


	vector<string> intrinsics = ofSplitString(_buffer.getNextLine(), " ");
	f = ofToDouble(intrinsics[0]);
	k1 = ofToDouble(intrinsics[1]);
	k2 = ofToDouble(intrinsics[2]);

	for (int i = 0; i < 3; i++) {
		vector<string> row = ofSplitString(_buffer.getNextLine(), " ");
		R[i][0] = ofToFloat(row[0]);
		R[i][1] = ofToFloat(row[1]);
		R[i][2] = ofToFloat(row[2]);
	}

	vector<string> transfor = ofSplitString(_buffer.getNextLine(), " ");
	t.x = ofToFloat(transfor[0]);
	t.y = ofToFloat(transfor[1]);
	t.z = ofToFloat(transfor[2]);

	//  Convert values to OF
	//
	glm::quat q = glm::quat_cast(R);
	setOrientation(ofQuaternion(q[0], q[1], q[2], q[3]));

	glm::vec3 p = -R * t;
	setPosition(p[0], p[1], p[2]);
	

}

void rcpCam::setExtrinsics(ofBuffer &_buffer) {


	//  Space
	//  vis image
	for (int i = 0; i < 2; i++) {
		string tmp = _buffer.getNextLine();
	}

	string imgFile = _buffer.getNextLine();
	double focalLength = ofToDouble(_buffer.getNextLine());
	if (focalLength == f) {
		//        cout << "Focal lenght match on " << imgFile << endl;
	}
	else {
		cout << "ERROR: Focal lenght DON'T match on " << imgFile << endl;
	}

	if (ofFile(ofToDataPath(imgFile)).exists()) {
		imgPath = imgFile;
	}

	vector<string> sizeValues = ofSplitString(_buffer.getNextLine(), " ");
	width = ofToFloat(sizeValues[0]);
	height = ofToFloat(sizeValues[1]);

	for (int i = 0; i < 8; i++) {
		string tmp = _buffer.getNextLine();
	}

	string geoString = _buffer.getNextLine();
	if (geoString != "0 0 0") {
		vector<string> geoValues = ofSplitString(geoString, " ");
		lat = ofToDouble(geoValues[0]);
		lon = ofToDouble(geoValues[1]);
		alt = ofToDouble(geoValues[2]);
	}

}
*/

void rcpCam::draw() {

	float w = width / (f);
	float h = height / (f);
	float d = 0.5;


	glm::vec3 p;


	glm::vec3 points[4] = { R * glm::vec3(-w,h,-d),
		R * glm::vec3(w,h,-d),
		R * glm::vec3(w,-h,-d),
		R * glm::vec3(-w,-h,-d) };


	ofPoint center = getPosition();
	ofPoint topLeft = center + ofPoint(points[0].x, points[0].y, points[0].z);
	ofPoint topRight = center + ofPoint(points[1].x, points[1].y, points[1].z);
	ofPoint bottomRight = center + ofPoint(points[2].x, points[2].y, points[2].z);
	ofPoint bottomLeft = center + ofPoint(points[3].x, points[3].y, points[3].z);

	ofSetColor(0, 255, 255);

	//ofDrawSphere(center, 0.2);
	ofLine(center, topLeft);
	ofLine(topLeft, topRight);
	ofLine(center, topRight);
	ofLine(topRight, bottomRight);
	ofLine(center, bottomRight);
	ofLine(bottomRight, bottomLeft);
	ofLine(center, bottomLeft);
	ofLine(bottomLeft, topLeft);

	//draw();
	
}

void rcpCam::drawPhotoBillboard(float zImage) {

	

	glm::vec3 points[4] = { R * glm::vec3(-width,height,-zImage),
		R * glm::vec3(width,height,-zImage),
		R * glm::vec3(width,-height,-zImage),
		R * glm::vec3(-width,-height,-zImage) };

	ofPoint center = getPosition();
	ofPoint topLeft = center + ofPoint(points[0].x, points[0].y, points[0].z);
	ofPoint topRight = center + ofPoint(points[1].x, points[1].y, points[1].z);
	ofPoint bottomRight = center + ofPoint(points[2].x, points[2].y, points[2].z);
	ofPoint bottomLeft = center + ofPoint(points[3].x, points[3].y, points[3].z);


	ofVboMesh mesh;

	mesh.addVertex(topLeft); // make a new vertex
	mesh.addColor(ofFloatColor(1, 1, 1));  // add a color at that vertex
	mesh.addNormal(ofPoint(0, 0, 10));  // add a color at that vertex
	mesh.addTexCoord(ofPoint(0, 0));

	mesh.addVertex(topRight); // make a new vertex
	mesh.addColor(ofFloatColor(1, 1, 1));  // add a color at that vertex
	mesh.addNormal(ofPoint(500, 0, 10));
	mesh.addTexCoord(ofPoint(width*2.0, 0));

	mesh.addVertex(bottomRight); // make a new vertex
	mesh.addColor(ofFloatColor(1, 1, 1));  // add a color at that vertex
	mesh.addNormal(ofPoint(500, 500, 10));
	mesh.addTexCoord(ofPoint(width*2.0, height*2.0));

	mesh.addVertex(bottomLeft); // make a new vertex
	mesh.addColor(ofFloatColor(1, 1, 1));  // add a color at that vertex
	mesh.addNormal(ofPoint(0, 500, 10));
	mesh.addTexCoord(ofPoint(0, height*2.0));

	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(2);
	mesh.addIndex(2);
	mesh.addIndex(3);
	mesh.addIndex(0);

	//mesh.drawWireframe();
	mesh.draw();

}

