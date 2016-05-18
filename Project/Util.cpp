#include "Util.h"

/*
	Simple cross platform sleep method.
*/
	void Util::USleep(int time) //Sleep time in milliseconds
	{
	#ifdef _WIN32
		Sleep(time);
	#else
		usleep(time * 1000);
	#endif
}
