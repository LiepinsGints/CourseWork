#ifndef APPLICATION_H
#define APPLICATION_H
#include "PlayerCamera.h"
#include <OgreRoot.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreWindowEventUtilities.h>
//Terrain
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

class Application
	: public Ogre::WindowEventListener,
	public Ogre::FrameListener
{
public:
	Application();
	virtual ~Application();

	bool go();

private:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;

	PlayerCamera playerCamera;
	Ogre::SceneNode* origin;
	Ogre::SceneNode* ogreNode;
};

#endif