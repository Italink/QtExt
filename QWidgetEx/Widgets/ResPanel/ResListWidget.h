#ifndef ResListWidget_h__
#define ResListWidget_h__

#include <QListWidget>

class ResListWidget : public QListWidget {
	Q_OBJECT
public:
	ResListWidget();
	void addItem(QString text);
protected:
	void dropEvent(QDropEvent* event) override;
	void rowsInserted(const QModelIndex& parent, int start, int end) override;
	void startDrag(Qt::DropActions supportedActions) override;

Q_SIGNALS:
	void dropItems(int dstIndex ,QList<QListWidgetItem*>);
private:
	QList<QListWidgetItem*> insertItems_;
	int dstIndex_ = -1;
};

#endif // ResListWidget_h__
