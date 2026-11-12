#pragma once
#include "KeyObserver.hpp"
#include <map>

class InputSystem
{
public:
	InputSystem() { m_window = nullptr; }
	void setWindow(GLFWwindow* window) { m_window = window; }
	void ObserveKey(int key);
	void Update();

	bool IsDown(int key) { return m_keyMapper.at(key).IsDown(); }
	bool IsPressed(int key) { return m_keyMapper.at(key).IsPressed(); }
	bool IsReleased(int key) { return m_keyMapper.at(key).IsReleased(); }
	


private:
	GLFWwindow* m_window;
	std::map<int, KeyObserver> m_keyMapper;
};
