#pragma once

#ifdef SCRIPTSYSTEM_EXPORTS
#define SCRIPTSYSTEM_API __declspec(dllexport)
#else
#define SCRIPTSYSTEM_API __declspec(dllimport)
#endif