#pragma once

#pragma warning(disable:4251)

#ifdef RENDERBACKEND_EXPORTS
#define RENDERBACKEND_API __declspec(dllexport)
#else
#define RENDERBACKEND_API __declspec(dllimport)
#endif