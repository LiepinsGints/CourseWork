#ifndef MATH3D_H
#define MATH3D_H
#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreWindowEventUtilities.h>
#include <math.h> 
#include <OgreException.h>
#include <OgreConfigFile.h>
#include "OgreRenderWindow.h"
/*#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreCamera.h>
#include "OgreViewport.h"
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>*/
class Math3D
{
public:
	void init() {
		
	}
	float pythagor(float a, float b, float c) {
		return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
	}
	Ogre::Vector3 directionVector(float CamX, float CamY, float CamZ, float x, float y, float z) {
		Ogre::Vector3 vector;
		vector.x = CamX - x;
		vector.y = CamY - y;
		vector.z = CamZ - z;
		float divider = pythagor(vector.x, vector.y, vector.z);
		vector.x /= divider;
		vector.y /= divider;
		vector.z /= divider;


		return vector;
	}
private:


};

#endif
