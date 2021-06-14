#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "vca.h"
#include "squareoscillator.h"
#include "squarevco.h"
#include "triangleoscillator.h"
#include "trianglevco.h"
#include "sineoscillator.h"
#include "sinevco.h"
#include "whitenoise.h"
#include "decay.h"
#include "adsr.h"
#include "jass.h"
using namespace std;

//class Constant : public Source {
//		float operator()() override {
//			return 1.0;
//		}
//		void reset() override {}
//};

int main(int argc, char **argv) {
//	QGuiApplication app(argc, argv);
//	QQmlApplicationEngine engine("qrc:/qml/main.qml");

//	return app.exec();

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

	ADSR adsr;
	adsr.setAttack(50);
	adsr.setSustainLevel(0.8);
	adsr.setSustain(50);
	std::vector<float> data(JASS::SAMPLES_PER_MS*600);
	adsr >> data;
	std::cout << data;
}
