#ifndef JASS_H
#define JASS_H

#include <QtGlobal>

namespace jass {
	const float TAU{6.283185f};
#ifndef Q_OS_ANDROID
	const uint SAMPLE_RATE{44100};
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
	const uint SAMPLE_RATE{48000};
#endif // Q_OS_ANDROID
}

#endif // JASS_H
