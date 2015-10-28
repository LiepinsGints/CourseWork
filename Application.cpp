#include "Application.h"
#include <OgreException.h>
#include <OgreConfigFile.h>
#include "OgreRenderWindow.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreCamera.h>
#include "OgreViewport.h"
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>


Application::Application()
	: mRoot(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	mWindow(0),
	mSceneMgr(0),
	mCamera(0),
	mInputMgr(0),
	mMouse(0),
	mKeyboard(0)
{
}

Application::~Application()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

	windowClosed(mWindow);

	delete mRoot;
}

Ogre::SceneNode* origin;;
Ogre::SceneNode* ogreNode;
bool Application::go()
{
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	mRoot = new Ogre::Root(mPluginsCfg);

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}

	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;
	
	//mWindow = mRoot->initialise(true, "Avalon");
	mRoot->initialise(false);
	HWND hWnd = 0;
	Ogre::NameValuePairList misc;
	misc["externalWindowHandle"] = Ogre::StringConverter::toString((int)hWnd);
	mWindow = mRoot->createRenderWindow("Avalon",1024, 768, false, &misc);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setPosition(0, 0, 160);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	// Create Scene
	Ogre::Vector3 movement(20,20, 0);
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
	origin = mSceneMgr->getRootSceneNode()->createChildSceneNode();;
	ogreNode = origin->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	ogreNode->translate(40, 30, 0);

	//ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ogreNode->attachObject(ogreEntity);
	//ogreNode->setPosition(0, 30, 0);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	// Create ground
	
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 10000, 10000, 200, 200, true, 1, 100, 100, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

	groundEntity->setMaterialName("Examples/Rockwall");
	groundEntity->setCastShadows(false);
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
	//-->Keyboard inputs
	/*mKeyboard->capture();
	if (mKeyboard->isKeyDown(OIS::KC_UP)) {
		mCamera->setPosition(0, 0, 320);
	}*/
		
	//<-- Keyboard inputs ends
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	mRoot->startRendering();

	return true;
}
Ogre::Vector3 movement(0, 0, 160);
bool Application::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	//Ogre::Vector3 movement(0, 0, 0);
	if (mWindow->isClosed()) return false;
	mKeyboard->capture();
	mMouse->capture();

	

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
	else if (mKeyboard->isKeyDown(OIS::KC_UP)) {
		movement.z += 1;
		mCamera->setPosition(movement);
		mCamera->lookAt(0, 0, 0);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_DOWN)) {
		movement.z -= 1;
		mCamera->setPosition(movement);
		mCamera->lookAt(0, 0, 0);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_LEFT)) {
		movement.x -= 1;
		mCamera->setPosition(movement);
		mCamera->lookAt(0, 0, 0);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_RIGHT)) {
		movement.x += 1;
		mCamera->setPosition(movement);
		mCamera->lookAt(0, 0, 0);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD1)) {
		movement.y -= 1;
		mCamera->setPosition(movement);
		mCamera->lookAt(0, 0, 0);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD2)) {
		movement.y += 1;
		mCamera->setPosition(movement);
		mCamera->lookAt(0, 0, 0);
	}//rot
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD4)) {
		origin->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_WORLD);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD5)) {
		origin->rotate(Ogre::Quaternion(Ogre::Degree(-1), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_WORLD);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD6)) {
		origin->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(0, 1, 0)), Ogre::Node::TransformSpace::TS_WORLD);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD7)) {
		origin->rotate(Ogre::Quaternion(Ogre::Degree(-1), Ogre::Vector3(0, 1, 0)), Ogre::Node::TransformSpace::TS_WORLD);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD8)) {
		origin->rotate(Ogre::Quaternion(Ogre::Degree(1), Ogre::Vector3(0, 0 ,1)), Ogre::Node::TransformSpace::TS_WORLD);
	}
	else if (mKeyboard->isKeyDown(OIS::KC_NUMPAD9)) {
		origin->rotate(Ogre::Quaternion(Ogre::Degree(-1), Ogre::Vector3(0, 0, 1)), Ogre::Node::TransformSpace::TS_WORLD);
	}
	return true;
}

void Application::windowResized(Ogre::RenderWindow* rw)
{
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void Application::windowClosed(Ogre::RenderWindow* rw)
{
	if (rw == mWindow)
	{
		if (mInputMgr)
		{
			mInputMgr->destroyInputObject(mMouse);
			mInputMgr->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputMgr);
			mInputMgr = 0;
		}
	}
}


/**********************************
*********platform handler**********
***********************************/
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
		Application app;

		try
		{
			app.go();
		}
		catch (Ogre::Exception& e)
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(
				NULL,
				e.getFullDescription().c_str(),
				"An exception has occured!",
				MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}
#ifdef __cplusplus
}
#endif