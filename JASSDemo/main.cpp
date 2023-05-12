#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlExtensionPlugin>

#include <QDir>

int main(int argc, char **argv) {
	Q_INIT_RESOURCE(resources);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("JASSDemoComponents", "Main");
//	QQmlApplicationEngine engine("qrc:/qt/qml/JASSDemo/Piano/main.qml");
	return app.exec();
}
