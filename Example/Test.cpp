#include "Test.h"
#include "QWidgetEx\Effect\QNeumorphism.h"

Test::Test()
{
	connect(this, &Test::enable_effectChanged, this, [this](QVariant var) {
		for (auto ins : QNeumorphism::instances) {
			ins->setEnabled(var.toBool());
		}
		});

	connect(this, &Test::insetChanged, this, [this](QVariant var) {
		for (auto ins : QNeumorphism::instances) {
			ins->setInset(var.toBool());
		}
		});

	connect(this, &Test::blur_sizeChanged, this, [this](QVariant var) {
		for (auto ins : QNeumorphism::instances) {
			ins->setBlurRadius(var.value<QBoundedDouble>().number());
		}
		});
	connect(this, &Test::strengthChanged, this, [this](QVariant var) {
		for (auto ins : QNeumorphism::instances) {
			ins->setStrength(var.value<QBoundedDouble>().number());
		}
		});
	connect(this, &Test::distanceChanged, this, [this](QVariant var) {
		for (auto ins : QNeumorphism::instances) {
			ins->setDistance(var.value<QBoundedDouble>().number());
		}
		});
	connect(this, &Test::angleChanged, this, [this](QVariant var) {
		for (auto ins : QNeumorphism::instances) {
			ins->setAngle(var.value<QBoundedDouble>().number());
		}
		});

}

