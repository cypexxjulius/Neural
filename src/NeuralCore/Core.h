#pragma once


#ifdef NL_PLATFORM_WINDOWS

	#ifdef NL_BUILD_DLL
		#define NEURAL_API __declspec(dllexport)
	#else 
		#define NEURAL_API __declspec(dllimport)
	#endif //NL_BUILD_DLL
#else 
	#error Neural only supports Windows
#endif //NL_PLATFORM_WINDOWS