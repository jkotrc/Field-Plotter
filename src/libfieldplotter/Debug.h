#pragma once

#define FIELDPLOTTER_DEBUG


#include <stdio.h>
#include <string>
#include <glm/glm.hpp>

#include "fieldplotter.h"

#define TAG(t) "["+t+"] "


using namespace std;
using namespace glm;

#ifdef FIELDPLOTTER_DEBUG
#define DEBUGSTRING(a,b) Debug::debugString(a,b)
#else
#define DEBUGSTRING(a,b)
#endif

namespace Debug {
	inline void debugString(const char* tag, const char* message) {
		printf("[%s] %s\n", tag, message);
	}
}

