#pragma once

#include "UI_Element.h"

namespace Ogre
{
	class TextAreaOverlayElement;
}

class UI_Text : public UI_Element
{
public:

	UI_Text(Ogre::Overlay* overReference, std::string title, int posX, int posY,
		int sizeX, int sizeY, std::string fontTitle, std::string textContent,
		Ogre::ColourValue textColor);
	~UI_Text();

	void setTextPosition(float x, float y);
	void setTextSize(float x, float y);
	void changeFontSize(int fontSize);
	void changeTextColor(Ogre::ColourValue textColor);

private:
	Ogre::TextAreaOverlayElement* textArea;
};
