#include "StaticRegister.h"

StaticRegisterBase::StaticRegisterBase(const char* typeName)
{
	StaticRegisterFactory::instance()->addRegister(typeName, this);
}

StaticRegisterFactory* StaticRegisterFactory::instance()
{
	static StaticRegisterFactory inst;
	return &inst;
}

void StaticRegisterFactory::registerLua(sol::state& lua)
{
	for (auto& iter : staticRegisterMap) {
		iter.second->registerLua(lua);
	}
}

void StaticRegisterFactory::addRegister(const char* typeName, StaticRegisterBase* staticRegister)
{
	staticRegisterMap.insert({ typeName,staticRegister });
}