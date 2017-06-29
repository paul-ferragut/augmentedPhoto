#include "ofApp.h"

#include "ofxGlm.h"
//--------------------------------------------------------------
void ofApp::setup(){



	ofBackground(0, 0, 0);

	//ofSetWindowShape(2480,3508);

	nCamera = -1;
	folderName = "bigger tree";
	//folderName = "4 trees";
	ofXml rcp;
	rcp.load(folderName + "/" + folderName + ".rcp");
	
	if (rcp.exists("SHOT"))
	{
		int increment = 0;
		while (rcp.exists("SHOT[" + ofToString(increment) + "]")) {

			int w, h;
			ofVec3f   t;          //  [a 3-vector describing the camera translation]
			double      f, k1, k2;  //  [the focal length, followed by two radial distortion coeffs]
			string     imgPath;        // Image
			ofVec3f   r;
			ofVec2f pp;

			rcp.setTo("SHOT[" + ofToString(increment) + "]");
			imgPath = folderName + "/images/" + rcp.getAttribute("n");
			w = ofToInt(rcp.getAttribute("w"));
			h= ofToInt(rcp.getAttribute("h"));
			rcp.setTo("CFRM");
			f = ofToDouble(rcp.getAttribute("fovx"));
			k1 = ofToDouble(rcp.getAttribute("rd"));
			k2 = ofToDouble(rcp.getAttribute("rd2"));
			pp.x= ofToFloat(rcp.getAttribute("ppx"));
			pp.y= ofToFloat(rcp.getAttribute("ppy"));
			rcp.setTo("T");
			t.set(ofToFloat(rcp.getAttribute("x")), ofToFloat(rcp.getAttribute("y")), ofToFloat(rcp.getAttribute("z")));
			rcp.setToParent();
			rcp.setTo("R");
			r.set(ofToFloat(rcp.getAttribute("x")), ofToFloat(rcp.getAttribute("y")), ofToFloat(rcp.getAttribute("z")));
			rcp.setToParent();
			rcp.setToParent();
			rcp.setToParent();
			increment++;

			rcpCam tCam;
			tCam.setup(w, h, t, r, pp, f, k1, k1, imgPath);
			ofCamera tCam2;


			//glm::orientate3
			
			//glm::mat3    R;          //  [a 3x3 matrix representing the camera rotation]
			//glm::vec3   r2;
			//r2.x = r.x; 
			//r2.y = r.y; 
			//r2.z = r.z;

			//R = glm::orientate3(r2);
			//glm::quat q = glm::quat_cast(R);
			//cout <<"before: "<< r << endl;
			//glm::quat q = glm::toQuat(glm::orientate3(r2));
			//glm::quat q = glm::quat(glm::vec3(r2.y, r2.z, r2.x));
			//tCam2.setGlobalPosition(t);
			//cout << " after: " << ofQuaternion(q[0], q[1], q[2], q[3]).getEuler() << endl;
			//ofQuaternion qOF;
			//qOF.makeRotate(r.x, ofVec3f(1, 0, 0), r.y, ofVec3f(0,1, 0), r.z, ofVec3f(0, 0, 1));
			//cout << "2after: " << qOF.getEuler() << endl;

			//glm::vec3 r2;
			//r2.x = r.x;
			//r2.y = r.y;
			//r2.z = r.z;

			//r = glm::normalize(r);
			//R = glm::eulerAngleYXZ(r2.y, r2.x, r2.z);
			//glm::quat q = glm::quat_cast(R);

			//glm::quat q = glm::toQuat(glm::eulerAngleYXZ(r2.y, r2.x, r2.z));
			//R = glm::mat3_cast(q);
			//glm::quat q = glm::quat_cast(R);
			//setOrientation(ofQuaternion(q[0], q[1], q[2], q[3]));

			//tCam2.setGlobalOrientation(ofQuaternion(q[0], q[1], q[2], q[3]));
			//cout  << endl;
			//tCam2.setFov(f);
			//camPhotos2.push_back(tCam2);
			//tCam2.set

			camPhotos.push_back(tCam);

		}

	}




	mesh.load(folderName + "/"+"mesh.ply");

	/*
	
	R is the rotation (Euler angle), T the translation, fovx for focal length, ppx ppy for principal point, rd and  rd2 for the two radial distortion parameters
	You should be able to compute all the other parameters you need using those values and some math
	

	</SHOT>
	<SHOT i="2" n="00000001.jpg" ci="1" w="3744" h="5616">
	<IPLN img="00000001.jpg" url="n2://67ee7a0296df4432963f57d774055332"/>
	<TPLN img="00000001.jpg" url="n2://67ee7a0296df4432963f57d774055332"/>
	<CFRM cf="1" fovx="52.296507" rd="-0.020833578" rd2="0.037688727" ppx="0.4957143" ppy="0.50096099">
	<T x="13.331099" y="-16.59665" z="12.510555"/>
	<R x="80.932477" y="-1.555219" z="36.071933"/>



	# The format of each camera is as follows:
	# Filename (of the undistorted image in visualize folder)
	# Original filename
	# Focal Length (of the undistorted image)
	# 2-vec Principal Point (image center)
	# 3-vec Translation T (as in P = K[R T])
	# 3-vec Camera Position C (as in P = K[R -RC])
	# 3-vec Axis Angle format of R
	# 4-vec Quaternion format of R
	# 3x3 Matrix format of R
	# [Normalized radial distortion] = [radial distortion] * [focal length]^2
	# 3-vec Lat/Lng/Alt from EXIF

	# The nubmer of cameras in this reconstruction
	48

	00000000.jpg
	E:\convivial\berlin photoshoot\3D Scans Raw Phillip\standing4\JPEG\_MG_0428.jpg
	3995.57226563
	1872 2808
	0.0813115239143 0.052978888154 -0.552383720875
	-0.476520985365 -0.0627471655607 0.289027124643
	-0.0406570913691 0.874609075255 0.0285722528527
	0.905597715105 -0.0196847395728 0.423455079906 0.0138336840506
	0.640989124775 -0.0417266301811 0.766415297985
	0.00838438048959 0.998843252659 0.0473688095808
	-0.767504513264 -0.0239370111376 0.64059650898
	0.068816206054
	0 0 0
	*/
	//cam.setFov(52.296507);

	renderingShader.load("shaders/render");
	blurShader.load("shaders/blur");

	isGuiShown = true;
	guiWidth = int(ofGetWidth() / 9);
	gui.setDefaultWidth(guiWidth);
	gui.setup("gui", folderName + "/" + folderName + ".xml");
	gui.setPosition(0, 0);
	gui.add(zImagePos.setup("zImagePos", 3880, 2000, 6000));
	gui.add(fovManual.setup("fovManual", 53.0, 0, 120));
	gui.add(modelScale.setup("modelScale", ofVec3f(1.0,1.0,1.0), ofVec3f(0.9, 0.9, 0.9), ofVec3f(1.1, 1.1, 1.1)));

		gui.add(debugView.setup("debug View", false));
	gui.add(roughness.setup("roughness", 0.05, 0.0, 1.0));
	gui.add(saveImage.setup("save image", false));
	gui.add(baseColor.setup("baseColor", ofColor(255, 255, 255, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255)));
	gui.add(numLights.setup("numLights", 3, 0, MAX_LIGHTS));
	numLights.addListener(this, &ofApp::resizeShadowMap);
	gui.add(shadowOffset.setup("shadowOffset", ofFloatColor(0.05, 0.05, 0.05, 1.0), ofFloatColor(0.0, 0.0, 0.0, 1.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
	gui.add(opacityBlack.setup("opacityBlack", 55, 0.0, 255));
	gui.add(opacityWhite.setup("opacityWhite", 55, 0.0, 255));

	gui.add(nearClipCamera.setup("nearClipCamera", 0.01, 0.0, 10));
	gui.add(farClipCamera.setup("farClipCamera", 50., 0.0, 1000));
	gui.add(lightMoveScale.setup("lightMoveScale", 1, 0.01, 4));
	gui.loadFromFile(folderName + "/" + folderName + ".xml");


	depthMapRes = 1024;
	setShadowMap(numLights);

	for (int i = 0; i<MAX_LIGHTS; i++) {
		pbrLight[i].setDepthMapRes(depthMapRes);
		pbrLight[i].setSoftShadowExponent(75.0);
		pbrLight[i].setShadowBias(0.001);
		pbrLight[i].setScale(2.0);

		ofFloatColor c = ofFloatColor(ofRandom(0.0, 1.0), ofRandom(0.0, 1.0), ofRandom(0.0, 1.0), 1.0);
		lightGui[i].setup("light " + ofToString(i), folderName + "/" + folderName +"Light"+ofToString(i)+".xml");
		lightGui[i].setPosition(guiWidth + i * guiWidth, 0);
		lightGui[i].add(isEnabled[i].set("enable", true));
		lightGui[i].add(lightType[i].set("lightType", LightType_Spot, LightType_Directional, LightType_Point));
		lightGui[i].add(lightTypeName[i].set(lightTypeNames[1]));
		lightGui[i].add(shadowType[i].set("shadowType", ShadowType_Soft, ShadowType_None, ShadowType_Soft));
		lightGui[i].add(shadowTypeName[i].set(shadowTypeNames[2]));
		lightGui[i].add(color[i].set("color", c, ofFloatColor(0.0, 0.0, 0.0, 1.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
		lightGui[i].add(cutoff[i].set("cutoff", 60, 10, 90));
		lightGui[i].add(exponent[i].set("exponent", 32, 0, 128));
		lightGui[i].add(intensity[i].set("intensity", 1.0, 0.0, 5.0));
		lightGui[i].add(radius[i].set("radius", 3000.0, 100.0, 6000.0));
		lightGui[i].add(nearClip[i].set("nearClip", 500.0, 10.0, 6000.0));
		lightGui[i].add(farClip[i].set("farClip", 4000, 10.0, 6000.0));

		lightGui[i].add(lightPosOffset[i].set("lightPosOffset", ofVec3f(0, 0, 0), ofVec3f(-1500, -1500, -1500), ofVec3f(1500, 1500, 1500)));
		lightGui[i].add(lightLookAt[i].set("lightLookAt", ofVec3f(0, 0, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
		lightGui[i].add(moveLight[i].set("moveLight", true));

		lightGui[i].loadFromFile( folderName + "/" + folderName + "Light" + ofToString(i) + ".xml");
	}



	ofFbo::Settings settingsFbo;
	settingsFbo.width = ofGetWidth();
	settingsFbo.height = ofGetHeight();
	//settingsFbo.useStencil = true;
	settingsFbo.useDepth = true;
	settingsFbo.internalformat = GL_RGBA;
	settingsFbo.numSamples = 8;
	fbo.allocate(settingsFbo);

	fbo.getTextureReference().getTextureData().bFlipTexture = true;

	ofFbo::Settings settingsFbo2;
	settingsFbo2.width = ofGetWidth();
	settingsFbo2.height = ofGetHeight();
	//settingsFbo.useStencil = true;
	//settingsFbo.useDepth = true;
	settingsFbo2.internalformat = GL_RGB;
	settingsFbo2.numSamples = 8;
	saveImageFbo.allocate(settingsFbo2);
}

//--------------------------------------------------------------
void ofApp::update(){

	//cam.setNearClip(0.1);	
	//cam.setFarClip(0);
	//cam.setFov(fovManual);//camPhotos[nCamera].f
	cam.setNearClip(nearClipCamera);
	cam.setFarClip(farClipCamera);
	/*TO DO REPLACE*/
	//nCamera = -1;

	for (int i = 0; i<numLights; i++) {
		pbrLight[i].enable(isEnabled[i]);
		pbrLight[i].setLightType(static_cast<LightType>(lightType[i].get()));
		pbrLight[i].setShadowType(static_cast<ShadowType>(shadowType[i].get()));
		pbrLight[i].setColor(color[i]);
		pbrLight[i].setCutoff(cutoff[i]);
		pbrLight[i].setExponent(exponent[i]);
		pbrLight[i].setIntensity(intensity[i]);
		pbrLight[i].setRadius(radius[i]);
		pbrLight[i].setNearClip(nearClip[i]);
		pbrLight[i].setFarClip(farClip[i]);

		if (moveLight[i]) {
		float rad = ofGetElapsedTimef() + TWO_PI * i / fmaxf(numLights, 1);
			pbrLight[i].setPosition(ofVec3f(lightPosOffset[i]) + (ofVec3f(1500.0 * cos(rad), 1500.0, 1500.0 * sin(rad))*lightMoveScale));
			pbrLight[i].lookAt(ofVec3f(lightLookAt[i]) + ofVec3f(0, 0, 0));
		}
		else {
			float rad = 0;// ofGetElapsedTimef() + TWO_PI * i / fmaxf(numLights, 1);
			pbrLight[i].setPosition(ofVec3f(lightPosOffset[i]) + (ofVec3f(1500.0 * cos(rad), 1500.0, 1500.0 * sin(rad))*lightMoveScale));
			pbrLight[i].lookAt(ofVec3f(lightLookAt[i]) + ofVec3f(0, 0, 0));
		
		}
		lightTypeName[i].set(lightTypeNames[lightType[i].get()]);
		shadowTypeName[i].set(shadowTypeNames[shadowType[i].get()]);
	}
	//

	float lerpPct = 0.5;
	if (nCamera >= 0) {
		if (fCameraPct>0.01) {
			cam.setPosition(cam.getPosition().getInterpolated(camPhotos[nCamera].getPosition(), 1.0 - fCameraPct));
			ofQuaternion q;
			q.slerp(1.0 - fCameraPct, cam.getOrientationQuat(), camPhotos[nCamera].getOrientationQuat());
			cam.setGlobalOrientation(q);
			//cam.setFov(fovManual);//camPhotos[nCamera].f
			fCameraPct *= (1.0 - powf(10.0, (1.0 - lerpPct)*-3.0));
		}
	}
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(0, 0, 0);
	/*
	ofEnableAlphaBlending();

	cam.begin();ofNoFill();
	for (int i = 0;i < camPhotos.size();i++) {
		camPhotos[i].draw();
		
		
		//camPhotos2[i].draw();
	}
	ofDrawAxis(2.5);


	if (nCamera != -1 && camPhotos[nCamera].imgPath != "NONE") {
		ofSetColor(255, 255.*(1. - fCameraPct));
		ofSetColor(255, 255);
		img.bind();

		camPhotos[nCamera].drawPhotoBillboard(mouseX * 10);cout << mouseX * 10 << endl;
		img.unbind();
	}
	ofSetColor(255, 255, 255, 100);
	mesh.drawWireframe();
	cam.end();

	//

	*/

	ofEnableAlphaBlending();

	fbo.begin();
	ofClear(0, 0, 0, 255);
	cam.setFov(fovManual);
	for (int i = 0; i<numLights; i++) {
		shadowMatrix[i] = pbrLight[i].getShadowMatrix(cam.getModelViewMatrix());

		if (pbrLight[i].getShadowType() != ShadowType_None && pbrLight[i].getIsEnabled()) {
			depthMap.begin();
			ofClear(255, 0, 0, 255);
			pbrLight[i].beginDepthCamera();
			renderScene();
			pbrLight[i].endDepthCamera();
			depthMap.end();

			if (pbrLight[i].getShadowType() == ShadowType_Soft) {
				blurVFbo.begin();
				ofClear(255, 0, 0, 255);
				blurShader.begin();
				blurShader.setUniform2f("resolution", blurHFbo.getWidth(), blurHFbo.getHeight());
				blurShader.setUniform1f("sigma", 2.0);
				blurShader.setUniformTexture("blurSampler", depthMap.getDepthTexture(), 1);
				blurShader.setUniform1i("horizontal", 0);
				depthMap.getDepthTexture().draw(0, 0);
				blurShader.end();
				blurVFbo.end();

				blurHFbo.begin();
				ofClear(255, 0, 0, 255);
				blurShader.begin();
				blurShader.setUniform2f("resolution", blurHFbo.getWidth(), blurHFbo.getHeight());
				blurShader.setUniform1f("sigma", 2.0);
				blurShader.setUniformTexture("blurSampler", blurVFbo.getTexture(), 1);
				blurShader.setUniform1i("horizontal", 1);
				blurVFbo.draw(0, 0);
				blurShader.end();
				blurHFbo.end();
			}

			depthSumFbo.begin();
			if (pbrLight[i].getShadowType() == ShadowType_Hard) {
				depthMap.getDepthTexture().draw((i % 4) * depthMapRes, floor(i / 4) * depthMapRes);
			}
			else if (pbrLight[i].getShadowType() == ShadowType_Soft) {
				blurHFbo.draw((i % 4) * depthMapRes, floor(i / 4) * depthMapRes);
			}
			depthSumFbo.end();
		}
	}



	ofEnableAlphaBlending();



	cam.begin();
	renderingShader.begin();
	renderingShader.setUniform1i("numLights", numLights);
	renderingShader.setUniformMatrix4f("viewMatrix", ofGetCurrentViewMatrix());
	renderingShader.setUniformTexture("shadowMap", depthSumFbo.getTexture(), 1);
	renderingShader.setUniform2f("depthMapAtrasRes", depthMapAtrasWidth, depthMapAtrasHeight);
	renderingShader.setUniform2f("depthTexMag", depthTexMag);
	renderingShader.setUniform1f("roughness", roughness);
	renderingShader.setUniform4f("shadowOffset", shadowOffset);
	for (int i = 0; i<numLights; i++) {
		string index = ofToString(i);
		renderingShader.setUniform1i("lights[" + index + "].isEnabled", pbrLight[i].getIsEnabled());
		renderingShader.setUniform3f("lights[" + index + "].position", pbrLight[i].getViewSpacePosition(ofGetCurrentViewMatrix()));
		renderingShader.setUniform4f("lights[" + index + "].color", pbrLight[i].getColor());
		renderingShader.setUniform3f("lights[" + index + "].direction", pbrLight[i].getViewSpaceDirection(ofGetCurrentViewMatrix()));
		renderingShader.setUniform1i("lights[" + index + "].type", pbrLight[i].getLightType());
		renderingShader.setUniform1i("lights[" + index + "].shadowType", pbrLight[i].getShadowType());
		renderingShader.setUniform1f("lights[" + index + "].intensity", pbrLight[i].getIntensity());
		renderingShader.setUniform1f("lights[" + index + "].exponent", pbrLight[i].getExponent());
		renderingShader.setUniform1f("lights[" + index + "].cutoff", pbrLight[i].getCutoff());
		renderingShader.setUniform1f("lights[" + index + "].radius", pbrLight[i].getRadius());
		renderingShader.setUniform1f("lights[" + index + "].softShadowExponent", pbrLight[i].getSoftShadowExponent());
		renderingShader.setUniform1f("lights[" + index + "].bias", pbrLight[i].getShadowBias());
	}
	glUniformMatrix4fv(renderingShader.getUniformLocation("shadowMatrix"), numLights, false, shadowMatrix[0].getPtr());
	renderScene();
	renderingShader.end();

	for (int i = 0; i < numLights; i++) {
		ofSetColor(pbrLight[i].getColor());
		ofDrawSphere(pbrLight[i].getPosition(), 50);
	}

	ofSetColor(255, 255, 255, 255);

	if(debugView){
	ofSetColor(255, 255, 255, 20);
	mesh.drawWireframe();}


	cam.end();



	fbo.end();


	if (saveImage) {
		saveImageFbo.begin();
	}
	
	ofSetColor(255, 255, 255, 255);
	ofEnableDepthTest();
	ofEnableAlphaBlending();

	cam.begin();
	ofPushMatrix();


	for (int i = 0;i < camPhotos.size();i++) {
	//	camPhotos[i].draw();
	}

	//meshFaces.draw();

	if (nCamera != -1 && camPhotos[nCamera].imgPath != "NONE") {
		ofSetColor(255, 255.*(1. - fCameraPct));
		ofSetColor(255, 255);
		img.bind();
		//bundler.cameras[nCamera].drawPhotoBillboard();
		camPhotos[nCamera].drawPhotoBillboard(zImagePos);
		img.unbind();

	}



	ofPopMatrix();
	cam.end();
	ofDisableDepthTest();

	ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
	ofSetColor(255, 255, 255, opacityBlack);
	fbo.draw(0, 0);
	//ofDisableBlendMode();



	ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	ofSetColor(opacityWhite, opacityWhite, opacityWhite, opacityWhite);
	fbo.draw(0, 0);
	ofDisableBlendMode();

	if (saveImage) {
		saveImageFbo.end();
	}

	if (saveImage) {
		//ofSaveScreen(ofGetTimestampString()+".png");
		ofPixels pix;
		saveImageFbo.readToPixels(pix);
		ofImage saveImageT;
		saveImageT.setFromPixels(pix);
		saveImageT.saveImage(ofGetTimestampString() + ".png",OF_IMAGE_QUALITY_HIGH);
		saveImage = false;
	}

	ofSetColor(255, 255, 255, 255);
	if (isGuiShown) {
		gui.draw();
		for (int i = 0;i<numLights;i++) {
			lightGui[i].draw();
		}
	}



}
//--------------------------------------------------------------
void ofApp::exit() {
	cout << "EXIT" << endl;
	gui.saveToFile(folderName + "/" + folderName + ".xml");
	for (int i = 0; i<MAX_LIGHTS; i++) {
		lightGui[i].saveToFile(folderName + "/" + folderName + "Light" + ofToString(i) + ".xml");
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'q') {
		nCamera--;
		if (nCamera == -1) {
			nCamera = camPhotos.size() - 1;
		}

		if (nCamera != -1 && camPhotos[nCamera].imgPath != "NONE") {
			ofLoadImage(img, camPhotos[nCamera].imgPath);
		}

		fCameraPct = 1.0;

	}
	else if (key == 'w') {
		nCamera++;
		//nCamera = 147;
		if (nCamera >= camPhotos.size()) {
			nCamera = -1;
		}
	


		if (nCamera != -1 && camPhotos[nCamera].imgPath != "NONE") {
			ofLoadImage(img, camPhotos[nCamera].imgPath);
		}
		fCameraPct = 1.0;
	}
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::resizeShadowMap(int & numLights) {
	setShadowMap(numLights);
}

//--------------------------------------------------------------
void ofApp::setShadowMap(int numLights) {
	depthMapAtrasWidth = depthMapRes * min(numLights, 4);
	depthMapAtrasHeight = depthMapRes * (floor(numLights / 5) + 1);

	depthTexMag.x = float(depthMapRes) / float(depthMapAtrasWidth);
	depthTexMag.y = float(depthMapRes) / float(depthMapAtrasHeight);

	settings.width = depthMapRes;
	settings.height = depthMapRes;
	settings.textureTarget = GL_TEXTURE_2D;
	settings.internalformat = GL_R8;
	settings.useDepth = true;
	settings.depthStencilAsTexture = true;
	settings.useStencil = true;
	settings.minFilter = GL_LINEAR;
	settings.maxFilter = GL_LINEAR;
	settings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
	settings.wrapModeVertical = GL_CLAMP_TO_EDGE;

	depthMap.allocate(settings);

	settings.internalformat = GL_R32F;
	blurHFbo.allocate(settings);
	blurVFbo.allocate(settings);

	settings.width = depthMapAtrasWidth;
	settings.height = depthMapAtrasHeight;

	depthSumFbo.allocate(settings);
	depthSumFbo.begin();
	ofClear(255, 0, 0);
	depthSumFbo.end();
}

//--------------------------------------------------------------
void ofApp::renderScene() {
	ofEnableDepthTest();
	ofPushStyle();
	ofSetColor(baseColor);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	/*
	for (int i = 0; i<model.getNumMeshes(); i++) {
		ofPushMatrix();
		ofMultMatrix(mesh.getMeshHelper(i).matrix);
		
		//ofScale(modelScale.x, modelScale.y, modelScale.z);
		model.getCurrentAnimatedMesh(i).draw();
		ofPopMatrix();
	}*/

	
	//ofVec3f v(modelScale.x, modelScale.y, modelScale.z);
	ofPushMatrix();ofScale(modelScale);
	mesh.drawFaces();
	//ofMultMatrix(model.getMeshHelper(i).matrix);
	//
	//mesh.drawFaces();



	ofPopMatrix();

	//  ofDrawBox(0, -5, 0, 10000, 10, 10000);
	glDisable(GL_CULL_FACE);
	ofPopStyle();
	ofDisableDepthTest();
}
