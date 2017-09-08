//
// Created by pooka on 9/5/17.
//

#include "Zmetek.h"
#include <iostream>
#include <OgreMath.h>

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
    createZmetek();
    createCamera();
    updateCameraPosition();
}

// InputListener
bool wPressed = false;
bool sPressed = false;
bool aPressed = false;
bool dPressed = false;

bool ZmetekApp::keyPressed(const OgreBites::KeyboardEvent &evt) {
    switch (evt.keysym.sym) {
        case SDLK_w:
            wPressed = true;
            break;
        case SDLK_s:
            sPressed = true;
            break;
        case SDLK_a:
            aPressed = true;
            break;
        case SDLK_d:
            dPressed = true;
            break;
        default:
            break;
    }
    return true;
}

bool ZmetekApp::keyReleased(const KeyboardEvent &evt) {
    switch (evt.keysym.sym) {
        case SDLK_ESCAPE:
            getRoot()->queueEndRendering();
            break;
        case SDLK_w:
            wPressed = false;
            break;
        case SDLK_s:
            sPressed = false;
            break;
        case SDLK_a:
            aPressed = false;
            break;
        case SDLK_d:
            dPressed = false;
            break;
        default:
            break;
    }
    return true;
}

void ZmetekApp::frameRendered(const Ogre::FrameEvent &evt) {
    if (wPressed) {
        moveZmetek(1);
    } else if (sPressed) {
        moveZmetek(-1);
    } else if (aPressed) {
        turnZmetek(1);
    } else if (dPressed) {
        turnZmetek(-1);
    }
}

bool ZmetekApp::mouseWheelRolled(const MouseWheelEvent &evt) {
    cameraDistance = cameraDistance - evt.y;
    updateCameraPosition();
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
    light->setPosition(-300, 300, -300);
}

void ZmetekApp::createZmetek() {
    zmetek = sceneManager->createEntity("zmetek", "Zmetek.mesh", "Zmetek");
    zmetek->setMaterialName("Examples/EnvMappedRustySteel");
    //zmetek->setMaterialName("Zmetek", "Zmetek");

    Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode(Vector3(5,5,5));
    node->attachObject(zmetek);

    // Blender exports are Z-up oriented
    /*node->pitch(Degree(-90));
    node->setFixedYawAxis(true, Vector3::UNIT_Z);*/
}

void ZmetekApp::createCamera() {
    cameraNode = sceneManager->getRootSceneNode()->createChildSceneNode();

    Camera* camera = sceneManager->createCamera("MainCamera");
    camera->setNearClipDistance(1);
    camera->setAutoAspectRatio(true);

    getRenderWindow()->addViewport(camera);
    cameraNode->attachObject(camera);
}

void ZmetekApp::updateCameraPosition() {
    const Vector3 &zmetekPosition = zmetek->getParentSceneNode()->getPosition();
    cameraNode->setPosition(zmetekPosition.x, zmetekPosition.y + cameraDistance, zmetekPosition.z + cameraDistance);
    cameraNode->lookAt(zmetekPosition, Node::TS_WORLD);
}

void ZmetekApp::moveZmetek(int direction) {
    SceneNode *zmetekNode = zmetek->getParentSceneNode();
    Matrix3 matrix;
    zmetekNode->getOrientation().ToRotationMatrix(matrix);
    zmetekNode->translate(matrix, Vector3(direction,0,0));
    updateCameraPosition();
}

void ZmetekApp::turnZmetek(int direction) {
    SceneNode *zmetekNode = zmetek->getParentSceneNode();
    zmetekNode->yaw(Degree(direction));
    const Quaternion &orientation = zmetekNode->getOrientation();
    std::cout << "Orientation: " << orientation << std::endl;
}

