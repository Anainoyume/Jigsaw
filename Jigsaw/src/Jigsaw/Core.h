#pragma once

#ifdef JS_PLATFORM_WINDOWS
	#ifdef JS_BUILD_DLL
		#define JIGSAW_API __declspec(dllexport)
	#else	
		#define JIGSAW_API __declspec(dllimport)
	#endif 
#else
	#error Jigsaw only support windows!
#endif 

