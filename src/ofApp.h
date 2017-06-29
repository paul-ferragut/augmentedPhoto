#pragma once

#include "ofMain.h"
//#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "rcpCam.h"
#include "customLight.h"

#define MAX_LIGHTS 8

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

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


		ofxIntSlider cameraSelection;

		//vector<ofImage>images;
		vector<rcpCam>camPhotos;
		ofEasyCam cam;
		//vector<>;
		ofVboMesh mesh; 

		string folderName;

		ofTexture   img;
		int         nCamera;
		float       fCameraPct;


		void renderScene();
		void resizeShadowMap(int & numLights);
		void setShadowMap(int numLights);

		//ofVec3f modelScale;
		customLight pbrLight[MAX_LIGHTS];

		ofShader renderingShader, blurShader;
		ofMatrix4x4 inverseCameraMatrix;
		int depthMapRes;
		int depthMapAtrasWidth, depthMapAtrasHeight;
		ofVec2f depthTexMag;
		ofFbo depthMap;
		ofFbo depthSumFbo, blurVFbo, blurHFbo;
		ofFbo::Settings settings;
		ofMatrix4x4 shadowMatrix[MAX_LIGHTS];
		const ofMatrix4x4 biasMatrix = ofMatrix4x4(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);


		ofxPanel gui;
		ofxToggle saveImage;
		ofxToggle debugView;
		ofxFloatSlider zImagePos;

		ofxFloatSlider fovManual;
		ofxFloatSlider roughness;
		ofxColorSlider baseColor;
		ofxIntSlider numLights;
		ofxFloatColorSlider shadowOffset;
		ofxVec3Slider modelScale;
		ofxFloatSlider opacityBlack;
		ofxFloatSlider opacityWhite;

		ofxFloatSlider nearClipCamera;
		ofxFloatSlider  farClipCamera;

		ofxFloatSlider  lightMoveScale;

		ofParameter<bool> isEnabled[MAX_LIGHTS];
		ofParameter<int> lightType[MAX_LIGHTS], shadowType[MAX_LIGHTS];
		ofParameter<ofFloatColor> color[MAX_LIGHTS];
		ofParameter<float> cutoff[MAX_LIGHTS];
		ofParameter<float> exponent[MAX_LIGHTS];
		ofParameter<float> intensity[MAX_LIGHTS];
		ofParameter<float> radius[MAX_LIGHTS];
		ofParameter<float> nearClip[MAX_LIGHTS];
		ofParameter<float> farClip[MAX_LIGHTS];

		ofParameter<ofVec3f>  lightPosOffset[MAX_LIGHTS];
		ofParameter<ofVec3f>  lightLookAt[MAX_LIGHTS];
		ofParameter<bool>  moveLight[MAX_LIGHTS];


		ofxPanel lightGui[MAX_LIGHTS];
		ofParameter<string> lightTypeName[MAX_LIGHTS], shadowTypeName[MAX_LIGHTS];

		int guiWidth;
		bool isGuiShown;

		const string lightTypeNames[3] = { "Directional Light", "Spot Light", "Point Light" };
		const string shadowTypeNames[3] = { "No Shadow", "hard Shadow", "Soft Shadow" };

		ofFbo fbo;
		ofFbo saveImageFbo;

};
