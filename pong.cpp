#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <BBOP/Graphics.h>
#include <vector>
using namespace std;

int main() {
  //Initialisation Début ############################################################################
  // Initialisation de GLFW
  GLFWwindow * window;
    //initialisation de la lib
  bbopInit(1920,1080,"window name",window);
  // Désactiver la synchronisation verticale (V-Sync)
  //glfwSwapInterval(0);
  //General info
  cout << "Bibibop Engine Version 0.0.1" << endl << "Author: Alexander74" << endl << "Contact: alexandre.lanternier@outlook.fr" << endl << "License: GPL-3.0" << endl; 
  //GPU info
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  cout << "OpenGL Vendor: " << vendor << endl;
  cout << "OpenGL Renderer: " << renderer << endl;
  cout << "Window size: " << 1000 << "x" << 500 << endl;
  // Initialisation Fin ##############################################################################
  //creation du sprite

  
  RectangleShape paddle1;
  
  paddle1.setPosition(Vector2f(100.0f,150.0f));
  paddle1.setSize(Vector2f(25.0f,150.0f));
  paddle1.setColor(Vector3i(128,0,128));
  RectangleShape paddle2;
  
  paddle2.setPosition(Vector2f(1800.0f,150.0f));
  paddle2.setSize(Vector2f(25.0f,150.0f));
  paddle2.setColor(Vector3i(128,0,128));
  RectangleShape ball;
  
  ball.setPosition(Vector2f(500.0f,250.0f));
  ball.setSize(Vector2f(25.0f,25.0f));
  ball.setColor(Vector3i(128,0,128));
  int direction=1;
  int sens=1;
  int cpt=5;
  //creation de la sceneClass
  
  Scene defaultScene;
  
  int TARGET_FPS = 10;
  double lastFrameTime = glfwGetTime();
  //FPS counter
  int nbFrames = 0;
  //double frameTarget = 1.0/60.0;
  double lastTime = glfwGetTime();
  double fps;
  double currentTime;
  double delta;
  double totalFps = 0.0;
  //FPS end init #######
  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    // FPS calc ################################################
    currentTime = glfwGetTime();
    delta = currentTime - lastTime;
    nbFrames++;
    totalFps++;
    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
      fps = double(nbFrames) / delta;
      stringstream ss;
      ss << "BibibopEngine" << " [" << fps << " FPS]";

      glfwSetWindowTitle(window, ss.str().c_str());
      nbFrames = 0;
      lastTime = currentTime;

    }
    //FPS calc end #############################################
	  // Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
    //testspr.setPosition(testspr.getPositionX()+0.5f, testspr.getPositionY()+0.5f);
    if (glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS  && paddle1.getPosition().y<1000.0f-10.0f)
    {
        paddle1.setPosition(Vector2f(paddle1.getPosition().x,paddle1.getPosition().y+25));
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS && paddle1.getPosition().y>10.0f)
    {
      paddle1.setPosition(Vector2f(paddle1.getPosition().x,paddle1.getPosition().y-25));
    }
    if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS  && paddle2.getPosition().y<1000.0f-10.0f)
    {
      paddle2.setPosition(Vector2f(paddle2.getPosition().x,paddle2.getPosition().y+25));
    }
    if (glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS && paddle2.getPosition().y>10.0f)
    {
      paddle2.setPosition(Vector2f(paddle2.getPosition().x,paddle2.getPosition().y-25));
    }
    switch (sens)
    {
    case 1:
      ball.setPosition(Vector2f(ball.getPosition().x,ball.getPosition().y+15));
      break;
    case 2:
      ball.setPosition(Vector2f(ball.getPosition().x,ball.getPosition().y-15));
      break;
    }
    switch (direction)
    {
    case 1:
      ball.setPosition(Vector2f(ball.getPosition().x+25,ball.getPosition().y));
      break;
    case 2:
      ball.setPosition(Vector2f(ball.getPosition().x-25,ball.getPosition().y));
      break;
    }
    if (ball.getCollisionBox()->check(paddle1.getCollisionBox()))
    {
      direction=1;
      
    }
    if (ball.getCollisionBox()->check(paddle2.getCollisionBox()))
    {
      direction=2;
      
    }
    if (ball.getPosition().x<10.0f && cpt>0)
    {
      ball.setPosition(Vector2f(500.0f,500.0f));
      cpt++;
    }
    if (ball.getPosition().x>1900.0f)
    {
      ball.setPosition(Vector2f(1500.0f,500.0f));
      cpt++;
    }
    if (ball.getPosition().y<10.0f)
    {
      sens=1;
    }
    if (ball.getPosition().y>1000.0f)
    {
      sens=2;
    }
    
    
    
    
    
  
    
    defaultScene.Use();
    defaultScene.Draw(paddle1);
    defaultScene.Draw(paddle2);
    defaultScene.Draw(ball);
    
    //Check d'erreur
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << error << std::endl;
    }
    // Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTime;

    // Attendre si nécessaire pour atteindre le taux de rafraîchissement cible
    while (deltaTime < 1.0 / TARGET_FPS) {
      glfwWaitEventsTimeout((1.0 / TARGET_FPS - deltaTime) * 0.9); // Attente avec un petit marge
      currentFrameTime = glfwGetTime();
      deltaTime = currentFrameTime - lastFrameTime;
    }
    lastFrameTime = currentFrameTime;


    
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  
  cout << "Session terminated, avg fps: " << totalFps/glfwGetTime() << endl;
	glfwTerminate();
	return 0;
}
