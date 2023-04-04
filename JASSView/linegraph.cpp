#include "linegraph.h"

LineGraph::LineGraph(QQuickItem *parent) : QQuickItem(parent) {
	setFlag(QQuickItem::ItemHasContents);

}

Source *LineGraph::input() const {
	return _input;
}

void LineGraph::setInput(const Source *input) {
	if (input == _input)
		return;
	_input = const_cast<Source *>(input);
	emit inputChanged();
}

double LineGraph::startTime() const {
	return _startTime;
}

void LineGraph::setStartTime(const double time) {
	// NOTE: Will this even work as expected?
	if (time == _startTime)
		return;
	_startTime = time;
	emit startTimeChanged();
}

double LineGraph::endTime() const {
	return _endTime;
}

void LineGraph::setEndTime(const double time) {
	if (time == _endTime)
		return;
	_endTime = time;
	emit endTimeChanged();
}

QColor LineGraph::color() const {
	return _color;
}

void LineGraph::setColor(const QColor &color) {
	if (color == _color)
		return;
	_color = color;
	emit colorChanged();
}

QSGNode *LineGraph::updatePaintNode(QSGNode *oldNode,
                                   UpdatePaintNodeData *data) {
	QSGGeometryNode *node = static_cast<QSGGeometryNode *>(oldNode);

	QSGGeometry *geometry = nullptr;
	QSGFlatColorMaterial *material = nullptr;

	const int N = 1000;

	if (!node) {
		node = new QSGGeometryNode;
		geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
		                           N);
		geometry->setLineWidth(2);
		geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
		node->setGeometry(geometry);
		node->setFlag(QSGGeometryNode::OwnsGeometry);

		material = new QSGFlatColorMaterial;
		material->setColor(_color);
		node->setMaterial(material);
		node->setFlag(QSGGeometryNode::OwnsMaterial);
	}
	else {
		geometry = node->geometry();
		material = static_cast<QSGFlatColorMaterial *>(node->material());
	}
	if (_input == nullptr)
		return node;
	QSGGeometry::Point2D *const vertices = geometry->vertexDataAsPoint2D();
	linearPlot(vertices, N);
	material->setColor(_color);
	node->markDirty(QSGGeometryNode::DirtyMaterial);
	node->markDirty(QSGGeometryNode::DirtyGeometry);
	return node;
}

void LineGraph::linearPlot(QSGGeometry::Point2D *vertices, int count) {
	const int startSampleIndex = _startTime*JASS::SAMPLES_PER_MS;
	const int endSampleIndex = _endTime*JASS::SAMPLES_PER_MS;
	const double sampleStep = static_cast<double>(endSampleIndex - startSampleIndex)/
	                       static_cast<double>(count - 1);
	// NOTE: Maybe warn and swap startSample/endSampleIndex if sampleStep < 0
	Q_ASSERT(sampleStep > 0);
	_input->reset();
	for (int sampleIndex = 0, pointIndex = 0; pointIndex < count; ++sampleIndex) {

		const double X_STEP = width()/static_cast<double>(count - 1);
		const int nextPlottedIndex = pointIndex*sampleStep + startSampleIndex;
		if (sampleIndex < (nextPlottedIndex)) {
			// NOTE: This sample is discarded.
			_input->operator ()();
			continue;
		}
		else if (sampleIndex >= nextPlottedIndex) {
			vertices[pointIndex].set(pointIndex*X_STEP,
			                         (0.5 - _input->operator()()*0.45)*height());
			pointIndex++;
		}
	}
}

