#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <singleton.h>

namespace Ogre
{
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

namespace magma_engine
{
	class UI_Element;

	class MAGMAENGINE_API UI_Manager : public Singleton<UI_Manager>
	{
	public:
		// Crea un overlay y lo muestra en pantalla
		UI_Manager(); 
		~UI_Manager();

		void init();
		void update();
		// Borra todos los elementos del overlay
		void cleanPanel(); 

		void flush(); 

		/*
		Crea un UI_Element de X tipo(Texto, Image, etc.) con su nombre de panel,
		una referencia al overlay y los argumentos que necesite su tipo
		*/
		template<typename T, typename ...Ts>
		T* createElement(std::string over, std::string panelName, Ts&&... args)
		{
			T* elem = new T(over, panelName, args...);
			elements.push_back(elem);
			return elem;
		}

		void deleteElement(UI_Element* f); 

	private:
		Ogre::OverlayManager* overlayMngr_;
		Ogre::Overlay* overlay;
		std::vector<UI_Element*> elements;
	};
}

