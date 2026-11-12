#pragma once
struct GLFWwindow;

class KeyObserver
{
public:
	KeyObserver();
	KeyObserver(GLFWwindow* window, int key);
	void Update();
	bool IsDown() const { return m_isDown; }
	bool IsPressed() const { return m_isDown && !m_wasDown; }
	bool IsReleased() const { return !m_isDown && m_wasDown; }

private:
	GLFWwindow* m_window;
	int m_key;

	bool m_wasDown;
	bool m_isDown;
};
