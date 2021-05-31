#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "triangleoscillator.h"
#include "sineoscillator.h"
#include "decay.h"
#include "jass.h"
using namespace std;

//class Constant : public Source {
//		float operator()() override {
//			return 1.0;
//		}
//		void reset() override {}
//};

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("qrc:/qml/main.qml");

	return app.exec();
//	TriangleOscillator osc;
//	osc.setFrequency(440);
//	std::vector<float> data(512);
//	osc >> data;
//	std::cout << data;

//	std::vector<float> data(44100);
//	DecayEffect decay;
//	decay.setRate(200);
//	SineOscillator osc;
//	decay.setInput(&osc);
//	decay >> data;
//	std::cout << data;
}
