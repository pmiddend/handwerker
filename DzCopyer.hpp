#ifndef DANIEL_ZEICHENSAETZE_DZCOPYER_HPP_INCLUDED
#define DANIEL_ZEICHENSAETZE_DZCOPYER_HPP_INCLUDED

#include <QString>
#include <QObject>
#include <QDir>

class DzCopyer
:
	public QObject
{
Q_OBJECT

public:
	explicit
	DzCopyer(
		QString const &sourceDir,
		QString const &destDir,
		QString const &csvFile,
		int column);

	void
	run(
		bool);

	~DzCopyer();
signals:
	void
	statusMessage(
		QString const &);

	void
	errorOccured(
		QString const &);

	void
	progress(
		int,
		int);
private:
	typedef
	QVector<QStringList>
	CSVFile;

	QDir sourceDir;
	QDir destDir;
	QString csvFile;
	int column;

	bool
	readCSV(
		CSVFile &);

	bool
	moveFile(
		bool,
		int,
		QString const &);
};

#endif
