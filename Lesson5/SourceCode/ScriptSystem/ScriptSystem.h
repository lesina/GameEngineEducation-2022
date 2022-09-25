#include "IScriptSystem.h"

class SCRIPTSYSTEM_API CScriptSystem final : public IScriptSystem {
public:
	CScriptSystem();

	virtual void Update() override;
	virtual IScriptProxy* CreateProxy(const char* filename) override;
	virtual void ProcessScript(IScriptProxy* scriptProxy) override;
};