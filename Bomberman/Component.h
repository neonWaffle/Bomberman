#pragma once
#include "Converter.h"
#include "glm/gtx/string_cast.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <iostream>

class Component
{
public:
	Component();
	virtual ~Component() = 0;
};

