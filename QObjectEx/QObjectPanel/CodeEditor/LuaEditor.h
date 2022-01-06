#ifndef LuaEditor_h__
#define LuaEditor_h__

#include <QWidget>
#include <Qsci/qsciapis.h>
#include <Qsci/qscilexer.h>
#include <Qsci/qsciscintilla.h>
#include "Qsci/qscilexerlua.h"

class MyLexerLua : public QsciLexerLua {
public:
	virtual QStringList autoCompletionWordSeparators() const override {
		return QStringList();
	}
	virtual const char* blockStart(int* style = 0) const override {
		if (style)
			*style = Operator;
		return "{";
	}
};

class LuaEditor : public QsciScintilla
{
	Q_OBJECT
public:
	explicit LuaEditor(QWidget* parent = nullptr);
	QsciLexer* lexer;
	QsciAPIs* apis;
};

#endif // LuaEditor_h__
