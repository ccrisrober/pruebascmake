#pragma once

#if defined(_MSC_VER) || defined(__declspec)
#  define LAVAUTILS_DLLEXPORT __declspec(dllexport)
#  define LAVAUTILS_DLLIMPORT __declspec(dllimport)
#else // _MSC_VER
#  define LAVAUTILS_DLLEXPORT
#  define LAVAUTILS_DLLIMPORT
#endif // _MSC_VER

#if defined(LAVAUTILS_STATIC)
#  define LAVAUTILS_API
#elif defined(LAVA_SHARED)
#  define LAVAUTILS_API LAVAUTILS_DLLEXPORT
#else
#  define LAVAUTILS_API LAVAUTILS_DLLIMPORT
#endif

#if defined(LAVAUTILS_SHARED_INL)
#  define LAVAUTILS_INL LAVAUTILS_DLLEXPORT
#else
#  define LAVAUTILS_INL LAVAUTILS_DLLIMPORT
#endif