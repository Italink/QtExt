#ifndef BindAdjuster_h__
#define BindAdjuster_h__

#include <functional>
#include <QMetaType>
#include "QVariant"

class QWidget;
class QVariant;


typedef std::function<void(QVariant)> Setter;
typedef std::function<QVariant()> Getter;

QWidget * createAdjuster(int typeId, Getter getter, Setter setter);

template <typename _Ty>
QWidget* createAdjuster(Getter getter, Setter setter) {
	return createAdjuster(QMetaTypeId2<_Ty>::qt_metatype_id(),getter,setter);
}

template <typename _Ty>
QWidget* createAdjuster(_Ty& refVar) {
	Setter setter = [&refVar](QVariant var) {
		refVar = var.value<_Ty>();
	};
	Getter getter = [&refVar](){
		return QVariant::fromValue<_Ty>(refVar);
	};
	return createAdjuster(QMetaTypeId2<_Ty>::qt_metatype_id(), getter, setter);
}

#endif // BindAdjuster_h__
