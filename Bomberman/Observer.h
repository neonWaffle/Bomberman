#pragma once

#include "Event.h"

#include <TGUI/TGUI.hpp>

class GameObject;

class Observer
{
public:
	virtual void OnNotify(Event event);
	virtual void OnNotify(Event event, GameObject& object);
	virtual void OnNotify(Event event, tgui::Widget::Ptr guiElement);
};

