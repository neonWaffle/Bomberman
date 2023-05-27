#pragma once

#include "Event.h"

#include <vector>

#include <TGUI/TGUI.hpp>

class GameObject;
class Observer;

class Subject
{
private:
	std::vector<Observer*> observers;
public:
	Subject();
	virtual ~Subject();

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

	void Notify(Event event);
	void Notify(Event event, GameObject& object);
	void Notify(Event event, tgui::Widget::Ptr guiElement);
};

