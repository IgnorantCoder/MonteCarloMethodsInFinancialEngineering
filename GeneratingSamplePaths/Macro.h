#pragma once

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef SAMPLEPATHS_EXPORTS
#define SAMPLEPATHS_API DLL_EXPORT
#else
#define SAMPLEPATHS_API DLL_IMPORT
#endif // SAMPLEPATHS_EXPORTS
