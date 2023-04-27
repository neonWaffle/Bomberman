#include "Subject.h"

Subject::~Subject()
{
}

void Subject::AddObserver(Observer* observer)
{
	observers.emplace_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::Notify(Event event)
{
	for (int i = observers.size() - 1; i >= 0; i--)
	{
		observers[i]->OnNotify(event);
	}
}

void Subject::Notify(Event event, GameObject& object)
{
	for (int i = observers.size() - 1; i >= 0; i--)
	{
		observers[i]->OnNotify(event, object);
	}
}

void Subject::Notify(Event event, tgui::Widget::Ptr guiElement)
{
	for (int i = observers.size() - 1; i >= 0; i--)
	{
		observers[i]->OnNotify(event, guiElement);
	}
}