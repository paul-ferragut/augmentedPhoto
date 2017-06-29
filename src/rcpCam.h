
#pragma once

#include "ofMain.h"

#include <glm.hpp>

//  Using he reference from: https://github.com/snavely/bundler_sfm
//
class rcpCam : public ofNode {
public:

	rcpCam();
	virtual ~rcpCam();
	
	void setup(float w, float h, ofVec3f translation, ofVec3f rotation, ofVec2f principalPoint, double focalLenght, double radDistort1, double radDistort2, string imageS);  //  [the focal length, followed by two radial distortion coeffs]

	


	//void    setIntrinsics(ofBuffer &_buffer);
	//void    setExtrinsics(ofBuffer &_buffer);

	void    draw();
	void    drawPhotoBillboard(float zImage);

	//  From cameras_v2.txt
	//

	float           width, height;
	double          lon, lat, alt;    // GeoLocation

									  //  From boundle.rd.out
	//glm::mat3   R;          //  [a 3x3 matrix representing the camera rotation]
	//glm::vec3   t;          //  [a 3-vector describing the camera translation]				  //
	glm::mat3    R;          //  [a 3x3 matrix representing the camera rotation]
	glm::vec3   t;          //  [a 3-vector describing the camera translation]
	//glm::quat q;
	double      f, k1, k2;  //  [the focal length, followed by two radial distortion coeffs]
	string     imgPath;        // Image
	glm::vec3   r;
	ofVec2f pp;

};