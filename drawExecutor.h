#pragma once
#include "drawOrder.h"

static class DrawExecutor
{
public:
	static void execute(DrawOrder* drawOrder) { drawOrder->execute(); }
};