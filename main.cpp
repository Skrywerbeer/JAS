#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <alsa/asoundlib.h>

#include "sinegenerator.h"
#include "organ.h"

using namespace std;

int main(int argc, char **argv) {
//	Organ organ;
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("qrc:/qml/main.qml");

	return app.exec();
}
