#pragma once

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef GENERATINGRANDOMNUMBERS_EXPORTS
#define RNDGEN_API DLL_EXPORT
#else
#define RNDGEN_API DLL_IMPORT
#endif // GENERATINGRANDOMNUMBERS_EXPORTS
