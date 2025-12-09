/** 
 * File:   Engine.cpp
 * Author: hector
 */

#include "Engine.h"
#include "objects/Model.h"
#include <iostream>

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

Engine* Engine::ACTIVE = NULL;

Engine* Engine::getActive()
{
    return ACTIVE;
}

Engine::Engine()
{
    activeCamera = NULL;
    defaultCamera = NULL;
    states = new StateMachine();
    lightingEnabled = true;
    resetFunction = NULL;
    
    ACTIVE = this;
}

Engine::~Engine()
{
    delete states;
    
    if(ACTIVE == this)
        ACTIVE = NULL;
}

void Engine::initGlut(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
}

void Engine::init(Viewport* viewport)
{
    // Initialize viewport
    viewport->init();
    
    // Configure callbacks
    configureCallbacks(viewport);
    
    // Default clear color
    glClearColor(0, 0, 0, 1);
    
    // Set identity in top modelview
    glLoadIdentity();
    
    // Enable depth
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    
    // Enable lights
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    // Focus camera
    activeCamera->refocus();
}

StateMachine* Engine::getStates()
{
    return states;
}

void Engine::configureCallbacks(Viewport* viewport)
{
    glutSetWindow(viewport->getId());
    
    glutDisplayFunc(refresh_callback);
    glutReshapeFunc(reshape_callback);
    glutMouseFunc(mousePressed_callback);
    glutMotionFunc(mouseMotion_callback);
    glutKeyboardFunc(keyDown_callback);
    glutKeyboardUpFunc(keyUp_callback);
    glutIdleFunc(idle_callback);
}

void Engine::printHelp()
{
    cout << "Help:" << endl;
    cout << "Use the keys and the mouse to perform actions and change between tools and cameras.";
    cout << endl;
    cout << endl;
    
    cameraHelp();
    actionHelp();
    states->printHelp();
}

void Engine::cameraHelp()
{
    cout << "Cameras:" << endl;
    cout << "    " << "Key " << "    " << "Name" << endl;
    
    map<unsigned char, pair<Camera*, string>* >::const_iterator it = cameras.begin();
    while(it != cameras.end())
    {
        cout << "    ";
        cout << it->first << "   " << "    ";
        cout << it->second->second << endl;
        
        ++it;
    }
    
    cout << endl;
}

void Engine::actionHelp()
{
    cout << "Actions:" << endl;
    cout << "    " << "Key " << "    " << "Description" << endl;
    
    printLine('i', "Enable/Disable lighting");
    printLine('n', "Enable/Disable normal per vertex");
    printLine('p', "Change between the available lens of the active camera");
    
    map<unsigned char, pair<Toggler*, string>* >::const_iterator it = actions.begin();
    while(it != actions.end())
    {
        printLine(it->first, it->second->second);
        
        ++it;
    }

    cout << endl;
}

void Engine::printLine(unsigned char key, string s)
{
    cout << "    ";
    cout << key << "   " << "    ";
    cout << s << endl;
}

void Engine::addCamera(unsigned char key, Camera* camera, string name)
{
    if(activeCamera == NULL)
    {
        activeCamera = camera;
        defaultCamera = camera;
    }
    
    cameras[key] = new pair<Camera*, string>(camera, name);
}

Camera* Engine::getActiveCamera()
{
    return activeCamera;
}

void Engine::loop()
{   
    glutMainLoop();
}

void Engine::addAction(unsigned char key, Toggler* toggler, string description)
{
    actions[key] = new pair<Toggler*, string>(toggler, description);
}

void Engine::render()
{
    activeCamera->render();
}

void Engine::reshape(int width, int height)
{
    activeCamera->reshape(width, height);
}

void Engine::keyUp(unsigned char key, int x, int y)
{
    if(key == 'h')
        printHelp();
    
    else if(key == 'n')
        Model::toggleNormalPerVertex();
    
    else if(key == 'i')
        toggleLighting();
    
    else if(key == 'r')
        reset();
    
    triggerCamera(key);
    triggerAction(key);
    
    states->keyUp(key, x, y);
}

void Engine::toggleLighting()
{
    lightingEnabled = !lightingEnabled;
    
    if(lightingEnabled)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
}

void Engine::triggerCamera(unsigned char key)
{
    map<unsigned char, pair<Camera*, string>* >::const_iterator it = cameras.find(key);
    
    if(it != cameras.end())
    {
        activeCamera = it->second->first;
        activeCamera->refocus();
        activeCamera->relocate();
        activeCamera->redisplay();
    }
    
    if(key == 'p')
        activeCamera->toggle();
}

void Engine::triggerAction(unsigned char key)
{
    map<unsigned char, pair<Toggler*, string>* >::const_iterator it = actions.find(key);
    
    if(it != actions.end())
        it->second->first->toggle();
}

void Engine::keyDown(unsigned char key, int x, int y)
{
    states->keyDown(key, x, y);
}

void Engine::mouseMotion(int x, int y)
{
    states->mouseMotion(x, y);
}

void Engine::mousePressed(int buttonId, int state, int x, int y)
{
    states->mousePressed(buttonId, state, x, y);
}

void Engine::idle()
{
    states->idle();
}

void Engine::reset()
{
    activeCamera = defaultCamera;
    activeCamera->moveTo(0, 0, 0);
    activeCamera->rotateTo(0, 0, 0);
    
    activeCamera->refocus();
    activeCamera->relocate();
    activeCamera->redisplay();
    
    if(resetFunction != NULL)
        (*resetFunction)();
}

void Engine::setResetCallback(void (*resetFunction)())
{
    this->resetFunction = resetFunction;
}

/** FUNCTIONAL CALLBACKS */
void refresh_callback()
{
    Engine::getActive()->render();
}

void reshape_callback(int width, int height)
{
    Engine::getActive()->reshape(width, height);
}

void mousePressed_callback(int buttonId, int state, int x, int y)
{
    Engine::getActive()->mousePressed(buttonId, state, x, y);
}

void mouseMotion_callback(int x, int y)
{
    Engine::getActive()->mouseMotion(x, y);
}

void keyUp_callback(unsigned char key, int x, int y)
{
    Engine::getActive()->keyUp(key, x, y);
}

void keyDown_callback(unsigned char key, int x, int y)
{
    Engine::getActive()->keyDown(key, x, y);
}

void idle_callback()
{
    Engine::getActive()->idle();
}
