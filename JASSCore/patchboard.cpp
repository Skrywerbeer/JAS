#include "patchboard.h"

PatchBoard::PatchBoard(QObject *parent) :
    Source(parent) {
	_type = Source::Type::PatchBoard;
}

QQmlListProperty<Source> PatchBoard::sources() {
	return QQmlListProperty<Source>(this, this,
	                                &PatchBoard::appendSource,
	                                &PatchBoard::sourceCount,
	                                &PatchBoard::source,
	                                &PatchBoard::clearSources,
	                                &PatchBoard::replaceSource,
	                                &PatchBoard::removeLastSource);
}

void PatchBoard::appendSource(Source *source) {
	_sources.push_back(source);
}

qsizetype PatchBoard::sourceCount() const {
	return _sources.size();
}

Source *PatchBoard::source(qsizetype index) const {
	return _sources.at(index);
}

void PatchBoard::clearSources() {
	_sources.clear();
}

void PatchBoard::replaceSource(qsizetype index, Source *source) {
	_sources[index] = source;
}

void PatchBoard::removeLastSource() {
	_sources.pop_back();
}

Source *PatchBoard::output() const {
	return _output;
}

void PatchBoard::setOutput(Source *output) {
	if (output == _output)
		return;
	_output = output;
	emit outputChanged();
}

float PatchBoard::newSample() {
	if (_output == nullptr)
		throw std::runtime_error("PatchBoard does not have an output.");
	return _output->operator()();
}

void PatchBoard::reset() {
	for (auto &source : _sources)
		source->reset();
	_output->reset();
}

void PatchBoard::appendSource(QQmlListProperty<Source> *list, Source *source) {
	reinterpret_cast<PatchBoard *>(list->data)->appendSource(source);
}

qsizetype PatchBoard::sourceCount(QQmlListProperty<Source> *list) {
	return reinterpret_cast<PatchBoard *>(list->data)->sourceCount();
}

Source *PatchBoard::source(QQmlListProperty<Source> *list, qsizetype index) {
	return reinterpret_cast<PatchBoard *>(list->data)->source(index);
}

void PatchBoard::clearSources(QQmlListProperty<Source> *list) {
	reinterpret_cast<PatchBoard *>(list->data)->clearSources();
}

void PatchBoard::replaceSource(QQmlListProperty<Source> *list, qsizetype index, Source *source) {
	reinterpret_cast<PatchBoard *>(list->data)->replaceSource(index, source);
}

void PatchBoard::removeLastSource(QQmlListProperty<Source> *list) {
	reinterpret_cast<PatchBoard *>(list->data)->removeLastSource();
}
