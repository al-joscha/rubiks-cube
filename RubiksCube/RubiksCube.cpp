// RubiksCube.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "GameInterface.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

#include "TestCubie.hpp"
#include "TestGlm.hpp"
#include "TestTriangle.hpp"


// Collection of test cases.
GameInterface gDummyInterface;
TestGlm gTestGlm;
TestTriangle gTestTriangle;
TestCubie gTestCubie;


GameInterface* gUsedInterface;

void APIENTRY openGLDebugCallback(
	GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userData)
{
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;

	std::cerr << "|''''''''''   OpenGL Debug Message   ''''''''''|\n";
	std::cerr << "| Message : " << message << "\n";
	std::cerr << "| Source  : " << source << "\n";
	std::cerr << "| Type    : " << type << "\n";
	std::cerr << "| ID      : " << id << "\n";
	std::cerr << "| Severity: " << severity << "\n";
	std::cerr << "|______________________________________________|\n";

	if (severity == GL_DEBUG_SEVERITY_HIGH) std::cerr << "Critical Bug Detected\n";
}


GLFWwindow* InitializeSystem()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Rubik's Cube", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openGLDebugCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	gUsedInterface->Initialize(window);

	return window;
}

void RunCoreLoop(GLFWwindow* window)
{
	double lastTime = glfwGetTime();
	double timeDifference = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		timeDifference = std::min(0.1, timeDifference);
		gUsedInterface->Update(timeDifference);

		int screenWidth, screenHeight;
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
		float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

		glViewport(0, 0, screenWidth, screenHeight);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		// glClearColor(.0f, .0f, .0f, .0f);
		glClearColor(.4f, .15f, .6f, .0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gUsedInterface->Render(aspectRatio);
		glfwSwapBuffers(window);

		double currentTime = glfwGetTime();
		timeDifference = currentTime - lastTime;
		lastTime = currentTime;
	}
}


void ShutdownSystem()
{
	gUsedInterface->ClearResources();
	glfwTerminate();
}


int main()
{
	// gUsedInterface = &gDummyInterface;
	// gUsedInterface = &gTestGlm;
	// gUsedInterface = &gTestTriangle;
	gUsedInterface = &gTestCubie;
	GLFWwindow* window = InitializeSystem();
	RunCoreLoop(window);
	ShutdownSystem();
}
