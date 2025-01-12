#include <Input/input_manager.h>
#include "SDL_events.h"

#include <string.h>
#include <iostream>
namespace magma_engine
{
	InputManager::InputManager()
	{
		exitRequest = false;
		cursorState = true;

		SDL_ShowCursor(cursorState);

		// TECLADO

		for (int i = 0; i < SIZE; i++)
			keysDown[i] = false;

		// RATON 

		mousePos.first = 0;
		mousePos.second = 0;

		isMouseButtonDown = false;
		isMouseButtonUp = false;

		for (int i = 0; i < MOUSE_MAX; i++)
			mouseButtonsDown[i] = false;
	}

	void InputManager::flush()
	{
		// TECLADO

		isKeyDownEvent = false;
		isKeyReleasedEvent = false;

		// RATON 

		isMouseButtonDown = false;
		isMouseButtonUp = false;

		for (int i = 0; i < MOUSE_MAX; i++)
			mouseButtonsDown[i] = false;

		windowChange = false;
	}

	bool InputManager::exitRequested()
	{
		return exitRequest;
	}

	void InputManager::exitPetition()
	{
		exitRequest = true; 
	}

	void InputManager::showOrHideMouse()
	{
		cursorState = !cursorState;
		SDL_ShowCursor(cursorState);
	}

	bool InputManager::hasWindowChange()
	{
		return windowChange;
	}

	void InputManager::inputEvent()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// CRUZ DE CIERRE
			case SDL_QUIT:

				exitRequest = true;
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					windowChange = true;
				}
				break;

				// TECLA 'ESCAPE'
			case SDL_KEYDOWN:

				if (event.key.keysym.scancode == SCANCODE_ESCAPE)
					exitRequest = true;

				else
				{
					isKeyDownEvent = true;
					keysDown[event.key.keysym.scancode] = true;
				}

				break;

			case SDL_KEYUP:

				isKeyReleasedEvent = true;
				keysDown[event.key.keysym.scancode] = false;

				break;

			case SDL_MOUSEMOTION:

				mouseMovement(event.motion.x, event.motion.y);

				break;

			case SDL_MOUSEBUTTONDOWN:

				isMouseButtonDown = true;
				isMouseButtonUp = false;

				if (event.button.button == SDL_BUTTON_LEFT)
					mouseButtonsDown[MOUSE_LEFT] = true;

				else
					mouseButtonsDown[MOUSE_RIGHT] = true;

				break;

			case SDL_MOUSEBUTTONUP:

				isMouseButtonDown = false;
				isMouseButtonUp = true;

				if (event.button.button == SDL_BUTTON_LEFT)
					mouseButtonsDown[MOUSE_LEFT] = false;

				else
					mouseButtonsDown[MOUSE_RIGHT] = false;

				break;

			default:
				break;
			}
		}
	}


	// CONTROLES TECLADO

	bool InputManager::isKeyDown(ScancodeKey key)
	{
		return isKeyDownEvent && keysDown[key];
	}

	bool InputManager::isKeyReleased(ScancodeKey key)
	{
		return isKeyReleasedEvent && !keysDown[key];
	}

	// CONTROLES RATON

	std::pair<int, int> InputManager::getMousePos()
	{
		return mousePos;
	}

	void InputManager::mouseMovement(const int& x, const int& y)
	{
		mousePos.first = x;
		mousePos.second = y;
	}

	bool InputManager::isMouseReleased()
	{
		return isMouseButtonUp;
	}

	bool InputManager::isMouseDown()
	{
		return isMouseButtonDown;
	}
}

