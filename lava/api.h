#pragma once

#if defined(_MSC_VER) || defined(__declspec)
#  define LAVA_DLLEXPORT __declspec(dllexport)
#  define LAVA_DLLIMPORT __declspec(dllimport)
#else // _MSC_VER
#  define LAVA_DLLEXPORT
#  define LAVA_DLLIMPORT
#endif // _MSC_VER

#if defined(LAVA_STATIC)
#  define LAVA_API
#elif defined(LAVA_SHARED)
#  define LAVA_API LAVA_DLLEXPORT
#else
#  define LAVA_API LAVA_DLLIMPORT
#endif

#if defined(LAVA_SHARED_INL)
#  define LAVA_INL LAVA_DLLEXPORT
#else
#  define LAVA_INL LAVA_DLLIMPORT
#endif