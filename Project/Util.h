#ifndef UTIL_H
#define UTIL_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class Util {
	public:
		static void USleep(int);

};
#endif
