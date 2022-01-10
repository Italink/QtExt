#include "ScriptPanel.h"
#include <QApplication>
#include <QObjectEx/LuaRegister/LuaRegister.h>
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

void ScriptPanel::runTest() {
	StdCapture::start();
	sol::state state;
	state.open_libraries();
	
	LuaRegisterFactory::instance()->registerAllType(state);
	LuaRegisterFactory::instance()->objectToLua(state, object_, "this");
	sol::protected_function_result ret = state.do_string(luaEditor_.text().toStdString());
	StdCapture::stop();
	QString msg = StdCapture::get();
	if (!ret.valid()) {
		sol::error err = ret;
		msg += err.what();
	}
	logBox_->clear();
	logBox_->append(msg);
	object_->requestUpdate();
}