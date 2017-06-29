#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	/*

	ofGLWindowSettings settings;
	//settings.setGLVersion(3, 2);
	settings.setGLVersion(4, 5);
	settings.width = 1280;
	settings.height = 720;
	ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	*/
	///*

	//ofAppGlutWindow window;
	ofAppGLFWWindow  window;


	ofGLWindowSettings settings;
	//settings.setGLVersion(3, 2);
	//settings.setGLVersion(2, 1);
	settings.setGLVersion(4, 1);
	settings.width = 1920;// 2480;
	settings.height = 1080;//3508;


	ofCreateWindow(settings);
	//window.setup(settings);
	//ofApp

	//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context


	//ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
