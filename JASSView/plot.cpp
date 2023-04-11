#include "plot.h"

Plot::Plot(QObject *parent) : QObject(parent) {
	connect(this, &Plot::inputChanged,
	        this, &Plot::changed);
	connect(this, &Plot::colorChanged,
	        this, &Plot::changed);
	connect(this, &Plot::widthChanged,
	        this, &Plot::changed);
}

Plot::~Plot() {

}

Source *Plot::input() const {
	return _input;
}

void Plot::setInput(Source *input) {
	if (input == _input)
		return;
	_input = input;
	emit inputChanged();
}

QColor Plot::color() const {
	return _color;
}

void Plot::setColor(const QColor &color) {
	if (color == _color)
		return;
	_color = color;
	emit colorChanged();
}

qreal Plot::width() const {
	return _width;
}

void Plot::setWidth(qreal width) {
	if (width == _width)
		return;
	else if (width < 0)
		throw std::runtime_error("Plot: Negative widths are not supported.");
	_width = width;
	emit widthChanged();
}

//QGradient Plot::gradient() const {
//	return _gradient;
//}

//void Plot::setGradient(QGradient gradient) {
//	if (gradient == _gradient)
//		return;
//	_gradient = gradient;
//	emit gradientChanged();
//}

