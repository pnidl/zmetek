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

private:

    void createWorld();
    void createCamera();
    void createZmetek();

    Ogre::Root* root = 0;
    Ogre::SceneManager* sceneManager = 0;
    Ogre::SceneNode* cameraNode = 0;
};

#endif //ZMETEKAPP_ZMETEKAPP_H
