#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class CamControl {
public:

	static void MouseDown(MouseEvent event) 
	{
		if (event.isRight() && event.isRightDown())
		{
			lastMousePos = event.getPos();
		}
	};
	
	static void MouseDrag(MouseEvent event) {
		if (event.isRight() || event.isRightDown())
		{
			vec3 right = cross(cam->getViewDirection(), cam->getWorldUp());
			vec3 up = cross(cam->getViewDirection(), right);
			float r = (event.getPos().x - lastMousePos.x) / 180.0f;
			vec3 newCamPos = rotate(camLookAtPos - cam->getEyePoint(), r, up);
			r = (event.getPos().y - lastMousePos.y) / 180.0f;
			float t = acosf(dot(vec3(0, -1, 0), cam->getViewDirection()));
			if (acosf(dot(vec3(0, -1, 0), cam->getViewDirection())) > M_PI*0.9)
				if (r > 0)
					r = 0;
			if (acosf(dot(vec3(0, -1, 0), cam->getViewDirection())) < M_PI*0.1)
				if (r < 0)
					r = 0;
			newCamPos = rotate(newCamPos, r, right);
			cam->setEyePoint(camLookAtPos - newCamPos);
			cam->lookAt(camLookAtPos);

			lastMousePos = event.getPos();
		}
	};

	static void SetCam(CameraPersp* camp) 
	{
		CamControl::cam = camp;
		getWindow()->getSignalMouseDown().connect(std::bind(&CamControl::MouseDown, std::placeholders::_1));
		getWindow()->getSignalMouseDrag().connect(std::bind(&CamControl::MouseDrag, std::placeholders::_1));
	};


	static CameraPersp* cam;
	static vec2 lastMousePos;
	static vec3 camLookAtPos;
};

