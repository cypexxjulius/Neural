#pragma once

#include "memory"

#ifdef NL_PLATFORM_WINDOWS
	#ifdef NL_NEURAL_LINK
		#ifdef NL_BUILD_DLL
			#define NEURAL_API __declspec(dllexport)
		#else 
			#define NEURAL_API __declspec(dllimport)
		#endif //NL_BUILD_DLL
	#else
		#define NEURAL_API 
	#endif
#else 
	#error Neural only supports Windows
#endif //NL_PLATFORM_WINDOWS

#ifdef NL_ENABLE_ASSERTS
	#define	NL_ASSERT(x, ...)		{ if(!(x)) { NL_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define	NL_CORE_ASSERT(x, ...)	{ if(!(x)) { NL_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define NL_ASSERT(x, ...)
	#define	NL_CORE_ASSERT(x, ...)
#endif 




#define BIT(x) (1 << x)

#define NL_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)


namespace Neural
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}