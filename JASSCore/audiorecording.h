#ifndef AUDIORECORDING_H
#define AUDIORECORDING_H

#include "jass.h"
#include "source.h"

class RecordingGraph;

class AudioRecording : public Source{
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(std::size_t sampleCount
		           READ sampleCount
		           NOTIFY bufferChanged)
		Q_PROPERTY(std::size_t startingIndex
		           READ startingIndex
		           WRITE setStartingIndex
		           NOTIFY startingIndexChanged)
		Q_PROPERTY(std::size_t endingIndex
		           READ endingIndex
		           WRITE setEndingIndex
		           NOTIFY endingIndexChanged)
		Q_PROPERTY(double progress
		           READ progress
		           WRITE setProgress
		           NOTIFY progressChanged)
		Q_PROPERTY(std::vector<qreal> buffer
		           READ buffer
		           NOTIFY bufferChanged)
	public:
		AudioRecording(QObject *parent = nullptr);

		int sampleCount() const;

		std::size_t startingIndex() const;
		void setStartingIndex(std::size_t index);
		std::size_t endingIndex() const;
		void setEndingIndex(std::size_t index);
		double progress();
		void setProgress(double progress);

		std::vector<qreal> buffer() const;

		float newSample() override;
		void reset() override;
		Q_INVOKABLE void clear();
		Q_INVOKABLE void save(const QString &filename) const;

		void operator<<(const std::vector<float> &newData);

		friend RecordingGraph;

	signals:
		void sampleCountChanged();
		void startingIndexChanged();
		void endingIndexChanged();
		void progressChanged();
		void bufferChanged();

	private:
		std::vector<float> _buffer;
		std::size_t _index = 0;
		std::size_t _startingIndex = 0;
		std::size_t _endingIndex = 0;
};

#endif // AUDIORECORDING_H
