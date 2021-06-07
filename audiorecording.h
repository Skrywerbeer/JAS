#ifndef AUDIORECORDING_H
#define AUDIORECORDING_H

#include "jass.h"
#include "source.h"

class AudioRecording : public Source{
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(int sampleCount
		           READ sampleCount
		           NOTIFY bufferChanged)
		Q_PROPERTY(int startingIndex
		           READ startingIndex
		           WRITE setStartingIndex
		           NOTIFY startingIndexChanged)
		Q_PROPERTY(int endingIndex
		           READ endingIndex
		           WRITE setEndingIndex
		           NOTIFY endingIndexChanged)
		Q_PROPERTY(std::vector<qreal> buffer
		           READ buffer
		           NOTIFY bufferChanged)
	public:
		AudioRecording(QObject *parent = nullptr);

		int sampleCount() const;

		int startingIndex() const;
		void setStartingIndex(int index);

		int endingIndex() const;
		void setEndingIndex(int index);

		std::vector<qreal> buffer() const;

		float operator()() override;
		void reset() override;
		Q_INVOKABLE void clear();
		Q_INVOKABLE void save(const QString &filename) const;

		void operator<<(const std::vector<float> &newData);

	signals:
		void sampleCountChanged();
		void startingIndexChanged();
		void endingIndexChanged();
		void bufferChanged();

	private:
		std::vector<float> _buffer;
		std::vector<float>::size_type _index = 0;
		int _startingIndex;
		int _endingIndex;
};

#endif // AUDIORECORDING_H
