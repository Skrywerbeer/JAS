#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "triangleoscillator.h"
#include "sineoscillator.h"
#include "jass.h"
using namespace std;

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("qrc:/qml/main.qml");

	return app.exec();
//	TriangleOscillator osc;
//	osc.setFrequency(440);
//	std::vector<float> data(512);
//	osc >> data;
//	std::cout << data;
}
