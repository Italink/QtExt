#ifndef QObjectPanel_h__
#define QObjectPanel_h__

#include <QWidget>
#include <QSplitter>

class QPropertyPanel;
class ScriptPanel;
class QObjectEx;
class ImageButton;

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
	ImageButton* btRedo_;
	ImageButton* btUndo_;
	QObjectEx* object_;
	QSplitter splitter_;
	QPropertyPanel* propertyPanel_;
	ScriptPanel* scriptPanel_;
	int propertyPanelWidth_;
};

#endif // QObjectPanel_h__
