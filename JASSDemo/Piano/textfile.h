#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QObject>
#include <QQmlEngine>
#include <QFile>
#include <QTextStream>


class TextFile : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_SINGLETON

	public:
		explicit TextFile(QObject *parent = nullptr);

		Q_INVOKABLE QString readFile(const QString &uri) const;

	signals:
};

#endif // TEXTFILE_H
