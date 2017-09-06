//
// Created by pooka on 9/5/17.
//

#include "Zmetek.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

// Constructor

ZmetekApp::ZmetekApp() {
    addInputListener(this);
}

// ApplicationContext

void ZmetekApp::setup() {
    ApplicationContext::setup();
    root = getRoot();
    sceneManager = root->createSceneManager(ST_GENERIC);

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    createWorld();
    createCamera();
}

// InputListener

bool ZmetekApp::keyPressed(const OgreBites::KeyboardEvent &evt) {
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }
    return true;
}

// Collaborators

void ZmetekApp::createWorld() {
    // Materials
    const MaterialPtr &x_material = MaterialManager::getSingleton().create("x_axis_material", "General");
    x_material->setReceiveShadows(false);
    x_material->getTechnique(0)->setLightingEnabled(true);
    x_material->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0);
    x_material->getTechnique(0)->getPass(0)->setAmbient(1,0,0);
    x_material->getTechnique(0)->getPass(0)->setSelfIllumination(1,0,0);
    const MaterialPtr &y_material = MaterialManager::getSingleton().create("y_axis_material", "General");
    y_material->setReceiveShadows(false);
    y_material->getTechnique(0)->setLightingEnabled(true);
    y_material->getTechnique(0)->getPass(0)->setDiffuse(0,1,0,0);
    y_material->getTechnique(0)->getPass(0)->setAmbient(0,1,0);
    y_material->getTechnique(0)->getPass(0)->setSelfIllumination(0,1,0);
    const MaterialPtr &z_material = MaterialManager::getSingleton().create("z_axis_material", "General");
    z_material->setReceiveShadows(false);
    z_material->getTechnique(0)->setLightingEnabled(true);
    z_material->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0);
    z_material->getTechnique(0)->getPass(0)->setAmbient(0,0,1);
    z_material->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1);

    // Axis system
    ManualObject *axisSystem = sceneManager->createManualObject("axisSystem");
    int max=300;
    for (int i = 0; i < max; ++i) {
        axisSystem->begin("x_axis_material", RenderOperation::OT_LINE_LIST);
        axisSystem->position(0,0,i);
        axisSystem->position(max,0,i);
        axisSystem->end();
    }
    for (int j = 0; j < max; ++j) {
        axisSystem->begin("z_axis_material", RenderOperation::OT_LINE_LIST);
        axisSystem->position(j, 0, 0);
        axisSystem->position(j, 0, max);
        axisSystem->end();
    }
    for (int k = 0; k < max; ++k) {
        axisSystem->begin("y_axis_material", RenderOperation::OT_LINE_LIST);
        axisSystem->position(k, 0, 0);
        axisSystem->position(k, max, 0);
        axisSystem->end();
        axisSystem->begin("y_axis_material", RenderOperation::OT_LINE_LIST);
        axisSystem->position(0, 0, k);
        axisSystem->position(0, max, k);
        axisSystem->end();
    }
    SceneNode *axisSystemNode = sceneManager->getRootSceneNode()->createChildSceneNode("axis_node");
    axisSystemNode->attachObject(axisSystem);

    // Light
    Ogre::Light* light = sceneManager->createLight("MainLight");
    light->setPosition(300, 300, 300);
}

void ZmetekApp::createCamera() {
    cameraNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    cameraNode->setPosition(10, 20, 50);
    cameraNode->lookAt(Vector3(10,0,0), Node::TS_WORLD);

    Camera* camera = sceneManager->createCamera("MainCamera");
    camera->setNearClipDistance(1);
    camera->setAutoAspectRatio(true);

    getRenderWindow()->addViewport(camera);
    cameraNode->attachObject(camera);
}

