#pragma once

#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#ifdef EXTERNAL_WRAPPER_EXPORTS
#define EXTERNAL_API DLL_EXPORT
#else
#define EXTERNAL_API DLL_IMPORT
#endif // EXTERNAL_WRAPPER_EXPORTS
