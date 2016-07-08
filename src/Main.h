#pragma once

#include <ppl.h>
#include <concurrent_queue.h>
#include "UniverseChunk.h"
#include "SDL.h"

extern concurrency::concurrent_queue<string> cmdQueue;