#include "App.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>

///#include <SDL_keycode.h>

void App::setup(void)
{
	AppContext::setup(); // NO OLVIDAR; LO PRIMERO
	mSM = mRoot->createSceneManager();
	mSM->addRenderQueueListener(mOverlaySystem);
	setupScene();
}

void App::shutdown()
{
  mSM->removeRenderQueueListener(mOverlaySystem);
  mRoot->destroySceneManager(mSM);
  AppContext::shutdown(); // NO OLVIDAR
}

void App::setupScene(void)
{
  // create the camera
  Ogre::Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Ogre::Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.90, 0.90, 0.90);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // CUBO
  Ogre::Entity* cube = mSM->createEntity("cube.mesh"); // crear entidad
  cube->setMaterialName("logo"); // definir material de la entidad

  mCubeNode = mSM->getRootSceneNode()->createChildSceneNode("CubeNode"); // crear nodo, hijo del 'ra�z'
  mCubeNode->attachObject(cube); // anclar entidad a nodo

  // configurar nodo
  mCubeNode->setPosition(0, 0, 350); // me lo acerco a la cara 350 ud.
  mCubeNode->setScale(2, 2, 2);
  mCubeNode->yaw(Ogre::Degree(-45));
  mCubeNode->showBoundingBox(false);
  mCubeNode->setVisible(true);

  // PLANO
  // definir malla mPlane1080x800
  Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), // vector normal, vector up
	  1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Y);
  // crear entidad
  Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
  plane->setMaterialName("default");
  // crear nodo
  mPlaneNode = mSM->getRootSceneNode()->createChildSceneNode("PlaneNode");
  mPlaneNode->attachObject(plane);
  mPlaneNode->setPosition(0, 0, -400);


																// Pruebas de Overlay Ogre (Falta pasar y adaptar todo para un UI Manager)
  // Creamos un overlay manager y un panel
  Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
  Ogre::Overlay* overlay = overlayManager.create("OverlayName");
  Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelName"));

  panel->setMetricsMode(Ogre::GMM_PIXELS);
  panel->setPosition(10, 10);
  panel->setDimensions(200, 100);
  panel->setMaterialName("BaseWhite");

  // Creamos un area de texto sobre la que trabajar
  Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "TextAreaUI"));

  // Preparar dimensiones y contenido texto
  textArea->setMetricsMode(Ogre::GMM_PIXELS);
  textArea->setPosition(0, 0);
  textArea->setDimensions(100, 100);
  textArea->setCaption("Creo que Eva es sospechosa");
  
  // Tama�o letra, fuente y color
  textArea->setCharHeight(16);
  
  textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
  textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

  //textArea->setFontName("BlueHighway"); // Falla al no haber carga de recursos, especificamente con ttf

  panel->addChild(textArea);

  // Show the overlay
  overlay->add2D(panel);
  overlay->show();
}

void App::rotate(float deltaTime)
{
	mCubeNode->yaw(Ogre::Degree(rotationVelocity * deltaTime));
}
