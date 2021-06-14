#include <stdexcept>
#include "adsr.h"

ADSR::ADSR(QObject *parent) :
    Source(parent) {}

int ADSR::attack() const {
	return _attack;
}

void ADSR::setAttack(int ms) {
	if (ms == _attack)
		return;
	if (ms < 0)
		throw std::invalid_argument("Attempt to set attack to < 0 ADSR.");
	_attack = ms;
	emit attackChanged();
}

int ADSR::decay() const {
	return _decay;
}

void ADSR::setDecay(int ms) {
	if (ms == _decay)
		return;
	if (ms < 0)
		throw std::invalid_argument("Attempt to set decay to < 0 in ADSR.");
	_decay = ms;
	emit decayChanged();
}

int ADSR::sustain() const {
	return _sustain;
}

void ADSR::setSustain(int ms) {
	if (ms == _sustain)
		return;
	if (ms < 0)
		throw std::invalid_argument("Attempt to set sustain to < 0 in ADSR.");
	_sustain= ms;
	emit sustainChanged();
}

double ADSR::sustainLevel() const {
	return _sustainLevel;
}

void ADSR::setSustainLevel(double value) {
	if (value == _sustainLevel)
		return;
	if ((value < 0) || (value > 1))
		throw std::invalid_argument("Attempt to set sustain to outside valid range in ADSR.");
	_sustainLevel = value;
	emit sustainChangedLevel();
}

int ADSR::release() const {
	return _release;
}

void ADSR::setRelease(int ms) {
	if (ms == _release)
		return;
	if (ms < 0)
		throw std::invalid_argument("Attempt to set release to < 0 in ADSR.");
	_release = ms;
	emit releaseChanged();
}

ADSR::State ADSR::currentState() const {
	const int ATTACK_INDEX = JASS::SAMPLES_PER_MS*_attack;
	const int DECAY_INDEX = JASS::SAMPLES_PER_MS*_decay + ATTACK_INDEX;
	const int SUSTAIN_INDEX= JASS::SAMPLES_PER_MS*_sustain + DECAY_INDEX;
	const int RELEASE_INDEX = JASS::SAMPLES_PER_MS*_release + SUSTAIN_INDEX;
	if (_index <= ATTACK_INDEX)
		return State::Attacking;
	else if (_index <= (DECAY_INDEX))
		return State::Decaying;
	else if (_index <= SUSTAIN_INDEX)
		return State::Sustaining;
	else if (_index <= RELEASE_INDEX)
		return State::Releasing;
	else
		return State::Finished;
}

float ADSR::operator()() {
	int stateIndex = 0;
	switch (currentState()) {
		case (Attacking):
			// NOTE: Replace 1.0 with attackLevel.
			return (1.0/(JASS::SAMPLES_PER_MS*_attack))*_index++;
		case (Decaying):
			stateIndex = _index++ - JASS::SAMPLES_PER_MS*_attack;
			return (1.0 + ((_sustainLevel - 1.0)/(JASS::SAMPLES_PER_MS*_decay))*stateIndex);
		case (Sustaining):
			_index++;
			return _sustainLevel;
		case (Releasing):
			stateIndex = _index++ - JASS::SAMPLES_PER_MS*(_attack+_decay+_sustain);
			return (_sustainLevel - (_sustainLevel/(JASS::SAMPLES_PER_MS*_release))*stateIndex);
		case (Finished):
			return 0;
		default:
			throw std::runtime_error("ADSR in invalid state.");
	}
	return 0;
}

void ADSR::reset() {
	_index = 0;
}
