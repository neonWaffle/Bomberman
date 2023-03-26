#include <iostream>
#include "GameEngine.h"
#include "MainMenu.h"

int main()
{
    GameEngine engine;
    engine.Init();
	engine.Run();
    engine.Close();
}
