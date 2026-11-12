#include "InputSystem.hpp"

void InputSystem::ObserveKey(int key)
{
	m_keyMapper[key] = KeyObserver(m_window, key);
	
}

void InputSystem::Update()
{
	for (auto& pair : m_keyMapper)
	{
		pair.second.Update();
	}
}
