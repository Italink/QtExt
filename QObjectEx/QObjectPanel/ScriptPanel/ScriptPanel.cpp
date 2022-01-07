#include "ScriptPanel.h"
#include <QApplication>
#include "QObjectEx\StaticRegister.h"
#include <QVBoxLayout>
#include "StdoutCapture.h"

ScriptPanel::ScriptPanel(QObjectEx* object, QWidget* parent /*= nullptr*/)
	: object_(object)
	, luaEditor_(LuaRegisterFactory::instance()->getApis(object->metaObject()->className(), "this"))
	, logBox_(new QTextBrowser)
	, btTest_(new QPushButton("Test"))
{
	QVBoxLayout* v = new QVBoxLayout(this);
	v->setContentsMargins(0, 0, 0, 0);
	v->addWidget(&luaEditor_);
	luaEditor_.setFrameShape(QFrame::NoFrame);
	QHBoxLayout* h = new QHBoxLayout;
	v->addLayout(h);
	h->addWidget(logBox_);
	h->addWidget(btTest_);
	btTest_->setFixedWidth(50);
	logBox_->setMaximumHeight(300);
	connect(btTest_, &QPushButton::clicked, this, &ScriptPanel::runTest);
}

template <typename Handler>
bool sol_lua_check(sol::types<QString>, lua_State* L, int index, Handler&& handler, sol::stack::record& tracking) {
	// indices can be negative to count backwards from the top of the stack,
	// rather than the bottom up
	// to deal with this, we adjust the index to
	// its absolute position using the lua_absindex function
	int absolute_index = lua_absindex(L, index);
	// Check first and second second index for being the proper types
	bool success = sol::stack::check<QString>(L, absolute_index, handler);
	tracking.use(1);
	return success;
}

QString sol_lua_get(sol::types<QString>, lua_State* L, int index, sol::stack::record& tracking) {
	int absolute_index = lua_absindex(L, index);
	// Get the first element
	QString str = sol::stack::get<QString>(L, absolute_index);
	tracking.use(1);
	return str;
}

int sol_lua_push(lua_State* L, const QString& things) {
	int amount = sol::stack::push(L, things.toLocal8Bit().constData());
	return amount;
}

void ScriptPanel::runTest() {
	StdCapture::start();
	sol::state state;
	state.open_libraries();
	LuaRegisterFactory::instance()->registerType(state, object_);
	LuaRegisterFactory::instance()->objectToLua(state, object_, "this");

	state.script("function f ( a) print(a) return a end");

	// get the function out of Lua
	sol::function f = state["f"];

	QString things = f(QString{ "hello" });
	qDebug() << things;
	sol::protected_function_result ret = state.do_string(luaEditor_.text().toStdString());
	StdCapture::stop();
	QString msg = StdCapture::get();
	if (!ret.valid()) {
		sol::error err = ret;
		msg += err.what();
	}
	logBox_->clear();
	logBox_->append(msg);
}