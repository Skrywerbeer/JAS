#include "linegraph.h"

LineGraph::LineGraph(QQuickItem *parent) : QQuickItem(parent) {
	setFlag(QQuickItem::ItemHasContents);
	connect(_horizontalAxis, &Axis::changed,
	        this, &LineGraph::update);
	connect(_verticalAxis, &Axis::changed,
	        this, &LineGraph::update);
	connect(_xInterval, &Interval::changed,
	        this, &LineGraph::update);
	connect(_yInterval, &Interval::changed,
	        this, &LineGraph::update);
	connect(_padding, &Padding::changed,
	        this, &LineGraph::update);
}

LineGraph::~LineGraph() {
	// NOTE: Check whether _horizontalAxis and _verticalAxis really need to be
	// deleted.
	delete _horizontalAxis;
	delete _horizontalAxisNode;
	delete _verticalAxis;
	delete _verticalAxisNode;
}

Padding *LineGraph::padding() const {
	return _padding;
}

Axis *LineGraph::horizontalAxis() const {
	return _horizontalAxis;
}

Axis *LineGraph::verticalAxis() const {
	return _verticalAxis;
}

Interval *LineGraph::xInterval() const {
	return _xInterval;
}

Interval *LineGraph::yInterval() const {
	return _yInterval;
}

Plot *LineGraph::primaryPlot() const {
	if (_plots.isEmpty())
		return nullptr;
	else
		return _plots.at(0);
}

void LineGraph::setPrimaryPlot(Plot *plot) {
	if (_plots.isEmpty()) {
		_plots.append(plot);
	}
	else {
		if (plot == _plots.at(0))
			return;
		replacePlot(0, plot);
	}
	emit plotsChanged();
}

QQmlListProperty<Plot> LineGraph::plots() {
	return QQmlListProperty<Plot>(this, this,
	                              &LineGraph::appendPlot,
	                              &LineGraph::plotCount,
	                              &LineGraph::plot,
	                              &LineGraph::clearPlots,
	                              &LineGraph::replacePlot,
	                              &LineGraph::removeLastPlot);
}

void LineGraph::appendPlot(const Plot *plot) {
	_plots.append(const_cast<Plot *>(plot));
	connect(plot, &Plot::changed,
	        this, &LineGraph::update);
	emit plotsChanged();
}

qsizetype LineGraph::plotCount() const {
	return _plots.size();
}

Plot *LineGraph::plot(qsizetype index) const {
	return _plots.at(index);
}

void LineGraph::clearPlots() {
	for (auto &plot : _plots)
		disconnect(plot, nullptr, this, nullptr);
	_plots.clear();
	emit plotsChanged();
}

void LineGraph::replacePlot(qsizetype index, Plot *plot) {
	_plots.replace(index, plot);
	emit plotsChanged();
}

void LineGraph::removeLastPlot() {
	auto plot = _plots.takeLast();
	disconnect(plot, nullptr, this, nullptr);
	emit plotsChanged();
}

QRectF LineGraph::availableCanvas() const {
	return QRectF(_padding->left(), _padding->top(), availableWidth(), availableHeight());
}

qreal LineGraph::availableWidth() const {
	const double available = width() - (_padding->left() + _padding->right());
	return available >= 0 ? available : 0;
}

qreal LineGraph::availableHeight() const {
	const double available = height() - (_padding->top() + _padding->bottom());
	return available >= 0 ? available : 0;
}

QSGNode *LineGraph::updatePaintNode(QSGNode *oldNode,
                                   UpdatePaintNodeData *data) {
	QSGNode *node = oldNode;
	if (!node) {
		node = new QSGNode;
		node->appendChildNode(_horizontalAxisNode);
		node->appendChildNode(_verticalAxisNode);
	}

	const int N = 1000;

	updateAxisNode(_horizontalAxisNode, _horizontalAxis);
	updateAxisNode(_verticalAxisNode, _verticalAxis);

	if (!_plots.isEmpty()) {
		while (_plots.size() != _plotNodes.size()) {
			if (_plots.size() > _plotNodes.size()) {
				PlotNode *plot = new PlotNode;
				plot->setPointCount(N);
				node->appendChildNode(plot);
				_plotNodes.append(plot);
			}
			else if (_plots.size() < _plotNodes.size()) {
				node->removeChildNode(_plotNodes.last());
				delete _plotNodes.takeLast();
			}
		}
		for (int i = 0; i < _plots.size(); ++i) {
			_plotNodes.at(i)->updateGeometry(availableCanvas(),
			                                 _xInterval,
			                                 _yInterval,
			                                 _plots.at(i));
			_plotNodes.at(i)->updateMaterial(_plots.at(i));
		}
	}
	return node;
}

void LineGraph::appendPlot(QQmlListProperty<Plot> *list,
                            Plot *plot) {
	reinterpret_cast<LineGraph *>(list->data)->appendPlot(plot);
}

qsizetype LineGraph::plotCount(QQmlListProperty<Plot> *list) {
	return reinterpret_cast<LineGraph *>(list->data)->plotCount();
}

Plot *LineGraph::plot(QQmlListProperty<Plot> *list, qsizetype index) {
	return reinterpret_cast<LineGraph *>(list->data)->plot(index);
}

void LineGraph::clearPlots(QQmlListProperty<Plot> *list) {
	reinterpret_cast<LineGraph *>(list->data)->clearPlots();
}

void LineGraph::replacePlot(QQmlListProperty<Plot> *list,
                            qsizetype index,
                            Plot *plot) {
	reinterpret_cast<LineGraph *>(list->data)->replacePlot(index, plot);
}

void LineGraph::removeLastPlot(QQmlListProperty<Plot> *list) {
	reinterpret_cast<LineGraph *>(list->data)->removeLastPlot();
}

void LineGraph::updateAxisNode(AxisNode *node, Axis *axis) {
	node->updateGeometry(availableCanvas(), axis);
	node->updateMajorTickMaterial(axis);
	node->updateMajorTickGeometry(availableCanvas(), axis);
	node->updateMinorTickMaterial(axis);
	node->updateMinorTickGeometry(availableCanvas(), axis);
}
