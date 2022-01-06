#ifndef QObjectPanel_h__
#define QObjectPanel_h__

#include <QWidget>
#include <QSplitter>

class QPropertyPanel;
class QsciScintilla;
class QObjectEx;

class QObjectPanel :public QWidget {
	Q_OBJECT
public:
	QObjectPanel(QObjectEx* object);
protected:
	void closeEvent(QCloseEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
Q_SIGNALS:
	void objectChanged(QObject*);
	void closed();
private:
	QObjectEx* object_;
	QSplitter splitter_;
	QPropertyPanel* propertyPanel_;
	QsciScintilla* codeEditor_;
	int propertyPanelWidth_;
};

#endif // QObjectPanel_h__
