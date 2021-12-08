#include "SwitcherAnimRect.h"

template<typename T>
T interp(const T& from, const T& to, qreal progress) {
	return (from + (to - from) * progress);
}

template<>
QRect interp(const QRect& f, const QRect& t, qreal process) {
	QRect ret;
	ret.setCoords(interp<int>(f.left(), t.left(), process),
		interp<int>(f.top(), t.top(), process),
		interp<int>(f.right(), t.right(), process),
		interp<int>(f.bottom(), t.bottom(), process));
	return ret;
}

void SwitcherAnimRect::paint(QPainter& painter, qreal process)
{
	if (stages.isEmpty())
		return;
	QList<QPair<QRect, QRect>> anims = stages[qBound(0, int(stages.size() * process), stages.size() - 1)];
	qreal stageProcess = process == 0.0 ? 0 : fmod(process, 1.0 / stages.size()) * stages.size();
	for (auto& rects : anims) {
		QRect rect = interp(rects.first, rects.second, stageProcess);
		painter.fillRect(rect, QColor(255, 255, 255, 200));
	}
}

void SwitcherAnimRect::setupLayer(WindowSwitcher::WidgetLayer from, WindowSwitcher::WidgetLayer to) {
	SwitcherAnimBase::setupLayer(from, to);
	stages.clear();
	if (from_.root == to_.root) {		//∑÷¡—∂Øª≠
		QList<QPair<QRect, QRect>> anims;
		for (auto& it : to_.children) {
			if (!from_.children.contains(it)) {
				anims.push_back({ from_.root->geometry(),it->geometry() });
			}
		}
		stages.push_back(anims);
	}
	else {
		QList<QPair<QRect, QRect>> mergeStage;	//∫œ≤¢Ω◊∂Œ
		for (auto& it : from.children) {
			mergeStage.push_back({ it->geometry(),from.root->geometry() });
		}
		if (!mergeStage.isEmpty())
			stages.push_back(mergeStage);
		QList<QPair<QRect, QRect>> switchStage;			//«–ªªΩ◊∂Œ
		switchStage.push_back({ from.root->geometry() ,to.root->geometry() });
		stages.push_back(switchStage);
		QList<QPair<QRect, QRect>> spreadStage;
		for (auto& it : to_.children) {		//’πø™Ω◊∂Œ
			spreadStage.push_back({ to.root->geometry(),it->geometry() });
		}
		if (!spreadStage.isEmpty())
			stages.push_back(spreadStage);
	}
}