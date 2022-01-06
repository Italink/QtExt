#ifndef StaticRegisterBase_h__
#define StaticRegisterBase_h__

#include <map>
#include <unordered_map>
#include <sol/sol.hpp>

class StaticRegisterFactory;

struct StaticRegisterBase {
	struct VarInfo {
		std::string type;
		std::string name;
	};
	StaticRegisterBase(const char* typeName);
	virtual void registerLua(sol::state& lua) {};
	virtual std::vector<VarInfo> subVars() { return {}; }
};

class StaticRegisterFactory {
public:
	static StaticRegisterFactory* instance();
	void registerLua(sol::state& lua);;
private:
	friend struct StaticRegisterBase;
	void addRegister(const char* typeName, StaticRegisterBase* staticRegister);
	std::unordered_map<std::string, StaticRegisterBase*> staticRegisterMap;
};

#endif // StaticRegisterBase_h__
