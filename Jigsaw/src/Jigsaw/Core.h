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

#ifdef JS_ENABLE_ASSERTS
	#define JS_ASSERT(x, ...) { if (!(x)) { JS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JS_CORE_ASSERT(x, ...) { if (!(x)) { JS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JS_ASSERT(x, ...)
	#define JS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)