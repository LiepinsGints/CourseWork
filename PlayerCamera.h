#ifndef PlayerCamera_H
#define PlayerCamera_H
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
			position.z += 1;
			mCamera->setPosition(position);
			mCamera->lookAt(0, 0, 0);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_DOWN)) {
			position.z -= 1;
			mCamera->setPosition(position);
			mCamera->lookAt(0, 0, 0);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_LEFT)) {
			position.x -= 1;
			mCamera->setPosition(position);
			mCamera->lookAt(0, 0, 0);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
			position.x += 1;
			mCamera->setPosition(position);
			mCamera->lookAt(0, 0, 0);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD1)) {
			position.y -= 1;
			mCamera->setPosition(position);
			mCamera->lookAt(0, 0, 0);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD2)) {
			position.y += 1;
			mCamera->setPosition(position);
			mCamera->lookAt(0, 0, 0);
		}//rot
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
		}
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
};

#endif
