#include "LuaEditor.h"
#include <QApplication>

LuaEditor::LuaEditor(QWidget* parent)
	:QsciScintilla(parent)
	, lexer(new MyLexerLua)
	, apis(new QsciAPIs(lexer))
{
	lexer->setAPIs(apis);
	apis->prepare();

	setFrameStyle(QFrame::NoFrame);
	//设置语法
	setLexer(lexer);//给QsciScintilla设置词法分析器
	//行号提示
	setMargins(1);
	setMarginsBackgroundColor(Qt::white);
	setMarginsFont(QFont("新宋体", 11));
	setMarginsForegroundColor(QColor(43, 145, 175));
	setMarginType(0, QsciScintilla::NumberMargin);//设置编号为0的页边显示行号。
	markerDefine(QsciScintilla::MarkerSymbol::CircledPlus, 0);
	setMarginWidth(0, 30);//设置页边宽度
	setAutoCompletionSource(QsciScintilla::AcsAll);   //设置源，自动补全所有地方出现的
	setAutoCompletionCaseSensitivity(true);           //设置自动补全大小写敏感
	setAutoCompletionThreshold(1);                    //设置每输入一个字符就会出现自动补全的提示
	setTabWidth(4);
	setIndentationGuides(false);
	setTabIndents(true);
	setAutoIndent(true);
	autoCompleteFromAll();
	setBraceMatching(QsciScintilla::StrictBraceMatch);
	SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 1);
	lexer->setDefaultFont(qApp->property("codeFont").value<QFont>());
	//    connect(this,&QsciScintilla::selectionChanged,this,[this](){
	//        int lineFrom,indexFrom,lineTo,indexTo;
	//        getSelection(&lineFrom,&indexFrom,&lineTo,&indexTo);
	//        int startPos=positionFromLineIndex(lineFrom,indexFrom);
	//        int endPos=positionFromLineIndex(lineTo,indexTo);
	//        this->fillIndicatorRange(lineFrom,indexFrom,lineTo,indexTo,INDIC_BOX);
	//        qDebug()<<this->selectedText()<<text(startPos,endPos);
	//    });
}