#include "Observer.h"

#include <vector>

void Observer::OnNotify(Event event)
{
}

void Observer::OnNotify(Event event, GameObject& object)
{
}

void Observer::OnNotify(Event event, tgui::Widget::Ptr guiElement)
{
}
