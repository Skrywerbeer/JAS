#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlExtensionPlugin>

#include <QDir>

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("JASSDemoComponents", "Main");
	return app.exec();
}
