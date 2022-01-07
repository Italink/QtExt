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

#endif // ScriptPanel_h__
