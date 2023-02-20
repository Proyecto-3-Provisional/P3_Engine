#pragma once

#include "AppContext.h"

class App : public AppContext
{
public:
  explicit App() : AppContext("MagmaTest") { };  // new -> setup()
  virtual ~App() { };    // delete -> shutdown()

  void rotate(float deltaTime);
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
      
  Ogre::SceneManager* mSM = nullptr;   
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mCubeNode = nullptr;
  Ogre::SceneNode* mPlaneNode = nullptr;

private:
    float rotationVelocity = 0.05;
};