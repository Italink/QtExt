#ifndef ScriptPanel_h__
#define ScriptPanel_h__

#include "LuaEditor.h"
#include "QObjectEx\QObjectEx.h"
#include <QPushButton>
#include <QTextBrowser>
#include <QWidget>

class ScriptPanel : public QWidget {
	Q_OBJECT
public:
	explicit ScriptPanel(QObjectEx* object, QWidget* parent = nullptr);
private:
	LuaEditor luaEditor_;
	QObjectEx* object_;
	QTextBrowser* logBox_;
	QPushButton* btTest_;
public:
	void runTest();
};

bool sol_lua_check(sol::types<QVector3D>, lua_State* L, int index, std::function<sol::check_handler_type> handler, sol::stack::record& tracking);
QVector3D sol_lua_get(sol::types<QVector3D>, lua_State* L, int index, sol::stack::record& tracking);
int sol_lua_push(sol::types<QVector3D>, lua_State* L, const QVector3D& v);

#endif // ScriptPanel_h__
