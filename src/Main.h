#pragma once

#include <ppl.h>
#include <concurrent_queue.h>
#include "SDL.h"

extern concurrency::concurrent_queue<std::string> cmdQueue;