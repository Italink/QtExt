#include "PageTabWidget.h"
#include <QProxyStyle>
#include <QStyleOption>
#include "QPainter"
#include "QBoxLayout"
#include "PageArea.h"

class CustomTabStyle : public QProxyStyle
{
public:
    /* sizeFromContents
     *  用于设置Tab标签大小
     * 1.获取原标签大小
     * 2.宽高切换
     * 3.强制宽高
     * 4.return
     * */
    QSize sizeFromContents(ContentsType type, const QStyleOption* option,
        const QSize& size, const QWidget* widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 60; // 设置每个tabBar中item的大小
            s.rheight() = 60;
        }
        return s;
    }

    /* drawControl
     *  画控件
     * 1.过滤CE_TabBarTabLabel
     * 2.选择状态下的背景绘制
     *      a.获取Rect
     *      b.保存旧的画笔
     *      c.设置新画笔
     *      d.画 Rect
     *      e.恢复旧的画笔
     * 3.设定Text对齐及选中/非选中状态下的Text颜色
     * 4.过滤CE_TabBarTab，对其进行绘制
     * */
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option))
            {
                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(QColor(0,100,200,50));
                    painter->drawRect(tab->rect);
                    painter->restore();
                }
			    if (tab->state & QStyle::State_MouseOver) {
					painter->save();
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(QColor(0, 100, 200, 50));
					painter->drawRect(tab->rect);
					painter->restore();
				}
           
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0x5d5d5d);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }
                tab->icon.paint(painter, QRect(tab->rect.x(), tab->rect.y(),tab->rect.width(), tab->iconSize.height()).adjusted(5,5,-5,-5));
                painter->drawText(QRect(tab->rect.x(), tab->rect.y()+tab->iconSize.height(), tab->rect.width(), tab->rect.height()- tab->iconSize.height()), tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

PageTabWidget::PageTabWidget()
{
    setIconSize(QSize(40,40));
	setTabPosition(QTabWidget::West);
    tabBar()->setStyle(new CustomTabStyle);
	QPalette p;
	p.setColor(QPalette::Window, Qt::transparent);
	setPalette(p);
    setStyleSheet("QTabWidget::pane { border: 0; background-color : transparent; }");

	switchAnim_.setDuration(200);
	switchAnim_.setStartValue(0.0);
	switchAnim_.setEndValue(1.0);

	connect(&switchAnim_, &QVariantAnimation::valueChanged, this, [this](QVariant var) {
		process_ = var.toDouble();
		update();
	});

	connect(this, &QTabWidget::currentChanged, this, [this](int index) {
		PageArea* area = dynamic_cast<PageArea*>(this->widget(index));
        if (area) {
            process_ = 0;
            switchAnim_.stop();
            switchAnim_.start();
        }
	});
}


void PageTabWidget::addPage(QString text, QIcon icon, QWidget* page)
{
	this->blockSignals(true);
	PageArea* area = new PageArea;
	area->setWidget(page);
    addTab(area, icon, text);
	this->blockSignals(false);
}

void PageTabWidget::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QRect rect = this->rect();
    rect.setLeft(this->tabBar()->width());
    //rect.setWidth(rect.width() * process_);
    painter.fillRect(rect, QColor(0, 100, 200, 50*process_));
}
