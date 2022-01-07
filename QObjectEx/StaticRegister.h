#ifndef StaticRegisterBase_h__
#define StaticRegisterBase_h__

#include <map>
#include <unordered_map>
#include <sol/sol.hpp>
#include <QStringList>

class LuaRegisterFactory;
class QObjectEx;

struct LuaRegisterBase {
	struct propertyInfo {
		QString type;
		QString name;
	};
	LuaRegisterBase(const char* typeName);
	virtual void typeToLua(sol::state& lua) {};
	virtual std::vector<propertyInfo> propertyDescription() { return {}; }
	virtual void objectToLua(QObjectEx* object, std::string varName, sol::state& lua) {}
};

class LuaRegisterFactory {
public:
	static LuaRegisterFactory* instance();
	void registerAllType(sol::state& lua);
	void registerType(sol::state& lua, std::string typeName);
	void registerType(sol::state& lua, QObjectEx* obj);
	void objectToLua(sol::state& lua, QObjectEx* obj, std::string varName);
	LuaRegisterBase* getLuaRegister(std::string typeName);
	QStringList getApis(QString typeName, QString varName);
private:
	void processApis(QStringList& apis, QString typeName, QString varName);
private:
	friend struct LuaRegisterBase;
	void addRegister(const char* typeName, LuaRegisterBase* staticRegister);
	std::unordered_map<std::string, LuaRegisterBase*> staticRegisterMap;
};

#endif // StaticRegisterBase_h__
