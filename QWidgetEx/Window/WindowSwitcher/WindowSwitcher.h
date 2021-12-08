#ifndef WindowSwitcher_h__
#define WindowSwitcher_h__

#include <QWidget>
#include <QPropertyAnimation>
class SwitcherAnimBase;

class WindowSwitcher : public QWidget {
	Q_OBJECT
public:
	WindowSwitcher();
	struct WidgetLayer {
		QWidget* root = nullptr;
		QList<QWidget*> children;
		bool alignRightTop = true;
	};
	void turnTo(QWidget* widget, bool createNewLayer = true, bool clearChildren = true, bool alignRightTop = false);
	void splitTo(QWidget* widget);
	void setAnimDuration(int ms);
	void popLayer();
private:
	void playAnim(WidgetLayer from, WidgetLayer to);
	SwitcherAnimBase* getCurrentAnim();
protected:
	void paintEvent(QPaintEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;
protected:
	QList<WidgetLayer> widgetStack_;
	QVariantAnimation switchAnim_;
	struct AnimState {
		WidgetLayer from;
		WidgetLayer to;
		double process = -1;
	}currentState_;
	enum SwitcherAnimType {
		Rect
	}currentAnimType_ = SwitcherAnimType::Rect;
	QMap<SwitcherAnimType, SwitcherAnimBase*> animPainters;
};

#endif // WindowSwitcher_h__
