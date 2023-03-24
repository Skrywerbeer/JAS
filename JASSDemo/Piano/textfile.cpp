#include "textfile.h"

TextFile::TextFile(QObject *parent)
    : QObject{parent} {}

QString TextFile::readFile(const QString &uri) const {
	QFile file(uri);
	if (!file.open(QIODevice::ReadOnly))
		throw std::runtime_error(QString("Could not open(%1) for reading")
	                             .arg(uri).toStdString());
	QTextStream stream(&file);
	return stream.readAll();
}

