#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlExtensionPlugin>
//Q_IMPORT_QML_PLUGIN(JASSCorePlugin)
//Q_IMPORT_QML_PLUGIN(JASSViewPlugin)

//#include "JASSCore/vca.h"
//#include "JASSCore/squareoscillator.h"
//#include "JASSCore/squarevco.h"
//#include "JASSCore/triangleoscillator.h"
//#include "JASSCore/trianglevco.h"
//#include "JASSCore/sineoscillator.h"
//#include "JASSCore/sinevco.h"
//#include "JASSCore/whitenoise.h"
//#include "JASSCore/decay.h"
//#include "JASSCore/adsr.h"
//#include "JASSCore/jass.h"

using namespace std;

int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine("qrc:/JASSComponents/main.qml");

	return app.exec();

//	TriangleOscillator osc;
//	osc.setFrequency(440);
//	osc.setAmplitude(0.1);
//	osc.setSlewRatio(0.1);
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

//	SquareOscillator osc;
//	osc.setDutyCycle(0.2);
//	osc.setAmplitude(0.1);
//	std::vector<float> data(512);
//	osc >> data;
//	std::cout << data;

//	WhiteNoise noise;
//	noise.setAmplitude(0.2);
//	std::vector<float> data(512);
//	noise >> data;
//	std::cout << data;

//	SineOscillator osc;
//	osc.setFrequency(440);
//	SineOscillator lfo;
//	lfo.setAmplitude(0.5);
//	lfo.setFrequency(20);
//	VCA vca;
//	vca.setInput(&osc);
//	vca.setCV(&lfo);
//	std::vector<float> data(10000);
//	vca >> data;
//	std::cout << data;

//	SineVCO vco;
//	vco.setDeviation(220);
//	SquareOscillator lfo;
//	lfo.setFrequency(110);
//	vco.setCV(&lfo);
//	std::vector<float> data(1000);
//	vco >> data;
//	std::cout << data;

//	SquareVCO vco;
//	vco.setDeviation(200);
//	SquareOscillator lfo;
//	lfo.setFrequency(110);
//	vco.setCV(&lfo);
//	std::vector<float> data(1000);
//	vco >> data;
//	std::cout << data;

//	TriangleVCO vco;
//	vco.setSlewRatio(1);
//	vco.setDeviation(100);
//	SquareOscillator lfo;
//	lfo.setFrequency(110);
//	vco.setCV(&lfo);
//	std::vector<float> data(1000);
//	vco >> data;
//	std::cout << data;

//	ADSR adsr;
//	adsr.setAttack(50);
//	adsr.setSustainLevel(0.8);
//	adsr.setSustain(50);
//	std::vector<float> data(JASS::SAMPLES_PER_MS*600);
//	adsr >> data;
//	std::cout << data;
}
