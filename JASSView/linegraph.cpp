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
}

void LineGraph::replacePlot(qsizetype index, Plot *plot) {
	_plots.replace(index, plot);
}

void LineGraph::removeLastPlot() {
	auto plot = _plots.takeLast();
	disconnect(plot, nullptr, this, nullptr);
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
	GraphNode *node = static_cast<GraphNode *>(oldNode);
	if (!node) {
		node = new GraphNode;
		node->appendChildNode(_horizontalAxisNode);
		node->appendChildNode(_verticalAxisNode);
	}

	const int N = 1000;
	_horizontalAxisNode->updateGeometry(availableCanvas(), _horizontalAxis);
	_horizontalAxisNode->updateMajorTickMaterial(_horizontalAxis);
	_horizontalAxisNode->updateMajorTickGeometry(availableCanvas(), _horizontalAxis);
	_horizontalAxisNode->updateMinorTickMaterial(_horizontalAxis);
	_horizontalAxisNode->updateMinorTickGeometry(availableCanvas(), _horizontalAxis);

	_verticalAxisNode->updateGeometry(availableCanvas(), _verticalAxis);
	_verticalAxisNode->updateMajorTickMaterial(_verticalAxis);
	_verticalAxisNode->updateMajorTickGeometry(availableCanvas(), _verticalAxis);
	_verticalAxisNode->updateMinorTickMaterial(_verticalAxis);
	_verticalAxisNode->updateMinorTickGeometry(availableCanvas(), _verticalAxis);


	if (!_plots.isEmpty() && _plotNodes.isEmpty()) {
		_plotNodes.append(new PlotNode(2.0, _plots.at(0)->color()));
		_plotNodes[0]->setPointCount(N);
		node->appendChildNode(_plotNodes.at(0));
	}
	if (!_plotNodes.isEmpty()) {
		_plotNodes.at(0)->updateGeometry(availableCanvas(),
		                                 _xInterval,
		                                 _yInterval,
		                                 _plots.at(0));
		_plotNodes.at(0)->updateMaterial(_plots.at(0));
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
