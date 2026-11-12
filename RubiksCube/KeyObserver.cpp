#include "KeyObserver.hpp"
#include <GLFW/glfw3.h>

KeyObserver::KeyObserver()
{
	m_window = nullptr;
	m_key = 0;
	m_wasDown = false;
	m_isDown = false;
}

KeyObserver::KeyObserver(GLFWwindow* window, int key)
{
	m_window = window;
	m_key = key;
	m_wasDown = false;
	m_isDown = false;
}

void KeyObserver::Update()
{
	m_wasDown = m_isDown;
	m_isDown = glfwGetKey(m_window, m_key) == GLFW_PRESS;
}
