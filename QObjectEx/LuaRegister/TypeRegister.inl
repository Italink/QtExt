#include "qvectornd.h"
#include "QTypeEx\QRange.h"
#include "QTypeEx\QCombo.h"

#define TypeToString(Type) sol::meta_function::to_string, [](const Type& var) {return QDebug::toString(var).toStdString();}

struct Vec2StaticRegister : public LuaRegisterBase {
	void typeToLua(sol::state& lua) override {
		lua.new_usertype<QVector2D>("QVector2D"
			, "x", sol::property(&QVector2D::x, &QVector2D::setX)
			, "y", sol::property(&QVector2D::y, &QVector2D::setY)
			, TypeToString(QVector2D)
		);
	}
	std::vector<propertyInfo> propertyDescription() override {
		return { {"float","x"},
				{"float","y"}
		};
	}
	void objectToLua(void* object, std::string varName, sol::state& lua) override {
		lua[varName] = static_cast<QVector2D*>(object);
	}
};

struct Vec3StaticRegister : public LuaRegisterBase {
	void typeToLua(sol::state& lua) override {
		lua.new_usertype<QVector3D>("QVector3D"
			, "x", sol::property(&QVector3D::x, &QVector3D::setX)
			, "y", sol::property(&QVector3D::y, &QVector3D::setY)
			, "z", sol::property(&QVector3D::z, &QVector3D::setZ)
			, TypeToString(QVector3D)
		);
	}
	std::vector<propertyInfo> propertyDescription() override {
		return { {"float","x"},
				{"float","y"},
				{"float","z"},
		};
	}
	void objectToLua(void* object, std::string varName, sol::state& lua) override {
		lua[varName] = static_cast<QVector3D*>(object);
	}
};

struct Vec4StaticRegister : public LuaRegisterBase {
	void typeToLua(sol::state& lua) override {
		lua.new_usertype<QVector4D>("QVector4D"
			, "x", sol::property(&QVector4D::x, &QVector4D::setX)
			, "y", sol::property(&QVector4D::y, &QVector4D::setY)
			, "z", sol::property(&QVector4D::z, &QVector4D::setZ)
			, "w", sol::property(&QVector4D::w, &QVector4D::setW)
			, TypeToString(QVector4D)
		);
	}
	std::vector<propertyInfo> propertyDescription() override {
		return { {"float","x"},
				{"float","y"},
				{"float","z"},
				{"float","w"},
		};
	}
	void objectToLua(void* object, std::string varName, sol::state& lua) override {
		lua[varName] = static_cast<QVector4D*>(object);
	}
};


struct ColorStaticRegister : public LuaRegisterBase {
	void typeToLua(sol::state& lua) override {
		lua.new_usertype<QColor>("QColor"
			, "red", sol::property(&QColor::red, &QColor::setRed)
			, "green", sol::property(&QColor::green, &QColor::setGreen)
			, "blue", sol::property(&QColor::blue, &QColor::setBlue)
			, "alpha", sol::property(&QColor::alpha, &QColor::setAlpha)
		    , TypeToString(QColor)
		);
	}
	std::vector<propertyInfo> propertyDescription() override {
		return { {"float","red"},
				{"float","green"},
				{"float","blue"},
				{"float","alpha"},
		};
	}
	void objectToLua(void* object, std::string varName, sol::state& lua) override {
		lua[varName] = static_cast<QVector4D*>(object);
	}
};

struct RangeStaticRegister : public LuaRegisterBase {
	void typeToLua(sol::state& lua) override {
		lua.new_usertype<QRange>("QRange"
			, "lower", sol::property(&QRange::getLower, &QRange::setLower)
			, "upper", sol::property(&QRange::getUpper, &QRange::setUpper)
			, TypeToString(QRange)
		);
	}
	std::vector<propertyInfo> propertyDescription() override {
		return { {"float","lower"},
				{"float","upper"},
		};
	}
	void objectToLua(void* object, std::string varName, sol::state& lua) override {
		lua[varName] = static_cast<QRange*>(object);
	}
};

struct ComboStaticRegister : public LuaRegisterBase {
	void typeToLua(sol::state& lua) override {
		lua.new_usertype<QCombo>("QCombo"
			, "currentIndex", sol::property(&QCombo::getCurrentIndex, &QCombo::setCurrentIndex)
			, "currentItem", sol::property(&QCombo::getCurrentItem, &QCombo::setCurrentItem)
			, TypeToString(QCombo)
		);
	}
	std::vector<propertyInfo> propertyDescription() override {
		return { {"int","currentIndex"},
				 {"QString","currentItem"},
		};
	}
	void objectToLua(void* object, std::string varName, sol::state& lua) override {
		lua[varName] = static_cast<QCombo*>(object);
	}
};
