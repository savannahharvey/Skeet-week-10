#pragma once
#include "order.h"

static class Executor
{
public:
	static void execute(Order* order) { order->execute(); }
};