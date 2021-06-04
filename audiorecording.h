#ifndef AUDIORECORDING_H
#define AUDIORECORDING_H

#include "jass.h"
#include "source.h"

class AudioRecording : public Source{
		Q_OBJECT
		QML_ELEMENT
	public:
		AudioRecording(QObject *parent = nullptr);

		float operator()() override;
		void reset() override;
		Q_INVOKABLE void clearRecording();
		Q_INVOKABLE void save(const QString &filename) const;

		void operator<<(const std::vector<float> &newData);

	private:
		std::vector<float> _buffer;
		std::vector<float>::size_type _index = 0;
};

#endif // AUDIORECORDING_H
