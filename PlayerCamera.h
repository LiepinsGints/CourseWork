#ifndef PlayerCamera_H
#define PlayerCamera_H
#include "Math3D.h"
#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreWindowEventUtilities.h>

#include <OgreException.h>
#include <OgreConfigFile.h>
#include "OgreRenderWindow.h"
/*#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreCamera.h>
#include "OgreViewport.h"
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>*/
class PlayerCamera 
{
public:
	void init(Ogre::Root* _mRoot, Ogre::RenderWindow* _mWindow, Ogre::Camera* _mCamera,
		Ogre::SceneNode* _origin,Ogre::SceneNode* _cameraNode) {
		mRoot = _mRoot;
		mWindow = _mWindow;
		mCamera = _mCamera;
		origin = _origin;
		cameraNode = _cameraNode;
		up = false;
		back = false;
		left = false;
		right = false;
	}
	void setPosition(float x, float y, float z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}
	bool keyListener() {
		// OIS
		Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
		OIS::ParamList pl;
		size_t windowHandle = 0;
		std::ostringstream windowHandleStr;
		mWindow->getCustomAttribute("WINDOW", &windowHandle);
		windowHandleStr << windowHandle;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
		mInputMgr = OIS::InputManager::createInputSystem(pl);
		mKeyboard = static_cast<OIS::Keyboard*>(
			mInputMgr->createInputObject(OIS::OISKeyboard, false));
		mMouse = static_cast<OIS::Mouse*>(
			mInputMgr->createInputObject(OIS::OISMouse, false));
		mKeyboard->capture();
		mMouse->capture();
		if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
		else if (mKeyboard->isKeyDown(OIS::KC_UP)) {
			up = true;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_DOWN)) {
			back = true;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_LEFT)) {
			left = true;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
			right = true;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD1)) {
			
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD2)) {
			
		}//rot
		/*
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD4)) {
			cameraNode->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_WORLD);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD5)) {
			cameraNode->rotate(Ogre::Quaternion(Ogre::Degree(-1), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_WORLD);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD6)) {
			cameraNode->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(0, 1, 0)), Ogre::Node::TransformSpace::TS_WORLD);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD7)) {
			cameraNode->rotate(Ogre::Quaternion(Ogre::Degree(-1), Ogre::Vector3(0, 1, 0)), Ogre::Node::TransformSpace::TS_WORLD);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD8)) {
			cameraNode->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(0, 0, 1)), Ogre::Node::TransformSpace::TS_WORLD);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD9)) {
			cameraNode->rotate(Ogre::Quaternion(Ogre::Degree(-1), Ogre::Vector3(0, 0, 1)), Ogre::Node::TransformSpace::TS_WORLD);
		}*/

		//Key released event
		
		if (!mKeyboard->isKeyDown(OIS::KC_UP)) {
			up = false;
		}
		else if (!mKeyboard->isKeyDown(OIS::KC_DOWN)) {
			back = false;
		}
		else if (!mKeyboard->isKeyDown(OIS::KC_LEFT)) {
			left = false;
		}
		else if (!mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
			right = false;
		}
		/*
		//Check event 
		if (up) {
			Ogre::Vector3 direction = math3D.directionVector(
				cameraNode->getPosition().x, cameraNode->getPosition().y, cameraNode->getPosition().z,
				origin->getPosition().x, origin->getPosition().y, origin->getPosition().z);
			position.x += direction.x * 1;
			position.y += direction.y * 1;
			position.z += direction.z * 1;

			origin->setPosition(position);
			mCamera->lookAt(origin->getPosition().x, origin->getPosition().y, origin->getPosition().z);
		}
		*/
		return true;
	};
private:
	Ogre::Vector3 position;
	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
	Ogre::Root* mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneNode* objectNode;
	Ogre::SceneNode* origin;
	Ogre::SceneNode* cameraNode;
	bool up;
	bool back;
	bool left;
	bool right;
	Math3D math3D;
};

#endif
