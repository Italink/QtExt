#include "LuaRegister.h"
#include "QObjectEx\QObjectEx.h"
#include "TypeRegister.inl"

LuaRegisterBase::LuaRegisterBase(const char* typeName)
{
	LuaRegisterFactory::instance()->addRegister(typeName, this);
}

LuaRegisterFactory::LuaRegisterFactory()
{
	addRegister("QVector2D", new Vec2StaticRegister());
	addRegister("QVector3D", new Vec3StaticRegister());
	addRegister("QVector4D", new Vec4StaticRegister());
	addRegister("QColor", new ColorStaticRegister());
	addRegister("QRange", new RangeStaticRegister());
	addRegister("QCombo", new ComboStaticRegister());
}


LuaRegisterFactory* LuaRegisterFactory::instance()
{
	static LuaRegisterFactory inst;

	return &inst;
}

void LuaRegisterFactory::registerAllType(sol::state& lua)
{
	for (auto& iter : staticRegisterMap) {
		iter.second->typeToLua(lua);
	}
}

void LuaRegisterFactory::registerType(sol::state& lua, std::string typeName) {
	LuaRegisterBase* luaReg = getLuaRegister(typeName);
	if (luaReg) {
		luaReg->typeToLua(lua);
	}
}

void LuaRegisterFactory::registerType(sol::state& lua, QObjectEx* obj)
{
	if (obj) {
		registerType(lua, obj->metaObject()->className());
	}
}

void LuaRegisterFactory::objectToLua(sol::state& lua, QObjectEx* obj, std::string varName)
{
	if (obj) {
		LuaRegisterBase* luaReg = getLuaRegister(obj->metaObject()->className());
		if (luaReg) {
			luaReg->objectToLua(obj, varName, lua);
		}
	}
}

LuaRegisterBase* LuaRegisterFactory::getLuaRegister(std::string typeName)
{
	return staticRegisterMap.at(typeName);
}


void LuaRegisterFactory::processApis(QStringList& apis, QString typeName, QString varName) {
	QString normailze = typeName.trimmed().replace("*", "");
	auto luaRegister = staticRegisterMap.find(normailze.toStdString());
	if (luaRegister == staticRegisterMap.end()) {
		return;
	}
	for (auto propertyInfo : luaRegister->second->propertyDescription()) {
		processApis(apis, propertyInfo.type, propertyInfo.name);
		apis << varName + "." + propertyInfo.name;
	}
}

QStringList LuaRegisterFactory::getApis(QString typeName, QString varName) {
	QStringList apis;
	processApis(apis, typeName, varName);
	return apis;
}

void LuaRegisterFactory::addRegister(const char* typeName, LuaRegisterBase* staticRegister)
{
	staticRegisterMap.insert({ typeName,staticRegister });
}
