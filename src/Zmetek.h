//
// Created by pooka on 9/5/17.
//

#ifndef ZMETEKAPP_ZMETEKAPP_H
#define ZMETEKAPP_ZMETEKAPP_H

#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreTrays.h>

class ZmetekApp:
    public OgreBites::ApplicationContext,
    public OgreBites::InputListener,
    public OgreBites::TrayListener {

public:
    // Constructor
    ZmetekApp();

    // ApplicationContext
    void setup() override;

    // InputListener
    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;
    bool keyReleased(const OgreBites::KeyboardEvent &evt) override;
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt) override;
    void frameRendered(const Ogre::FrameEvent &evt) override;

private:

    void createWorld();
    void createZmetek();
    void createCamera();
    void updateCameraPosition();
    void moveZmetek(int direction);
    void turnZmetek(int direction);

    Ogre::Root* root = 0;
    Ogre::SceneManager* sceneManager = 0;
    Ogre::SceneNode* cameraNode = 0;
    Ogre::Entity* zmetek = 0;
    int cameraDistance = 10;
};

#endif //ZMETEKAPP_ZMETEKAPP_H
