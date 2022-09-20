#pragma once
#include "Common.h"

class IScriptProxy;

class SCRIPTSYSTEM_API IScriptSystem
{
public:
	virtual void Update() = 0;
	virtual IScriptProxy* CreateProxy(const char* filename) = 0;
	virtual void ProcessScript(IScriptProxy* scriptProxy) = 0;
};
