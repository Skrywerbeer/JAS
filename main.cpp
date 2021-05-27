#include <QGuiApplication>
#include <QQmlApplicationEngine>

using namespace std;

int main(int argc, char **argv) {
//	Organ organ;
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("qrc:/qml/main.qml");

	return app.exec();
}
