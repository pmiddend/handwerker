#include <QStringList>
#include <QVector>
#include <QTextStream>
#include <QSet>
#include <QFile>
#include "DzCopyer.hpp"

DzCopyer::DzCopyer(
	QString const &_sourceDir,
	QString const &_destDir,
	QString const &_csvFile,
	int _column)
:
	sourceDir(
		_sourceDir),
	destDir(
		_destDir),
	column(
		_column),
	csvFile(
		_csvFile)
{
}

void
DzCopyer::run(
	bool const simulated)
{
	CSVFile compiledFile;
	
	if(!this->readCSV(compiledFile))
		return;

	QSet<QString> visitedFiles;

	emit statusMessage(
		trUtf8("Bearbeite Zeilen..."));

	int currentLine = 0;
	int currentID = 0;
	for(CSVFile::const_iterator it = compiledFile.begin(); it != compiledFile.end(); ++it)
	{
		QString const correctColumn =
			it->at(
				column);

		if(!visitedFiles.contains(correctColumn))
		{
			visitedFiles.insert(
				correctColumn);

			this->moveFile(
				simulated,
				++currentID,
				correctColumn);
		}

		emit progress(
			++currentLine,
			static_cast<int>(
				compiledFile.size()));
	}

	emit statusMessage(
		trUtf8("<font color=\"green\"><strog>Fertig!</strong></font>"));
}

DzCopyer::~DzCopyer()
{
}

bool
DzCopyer::readCSV(
	CSVFile &compiledFile)
{
	emit statusMessage(
		trUtf8("Lese Datei \"")+
		csvFile+
		trUtf8("\" ein..."));


	QFile file(
		csvFile);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		emit errorOccured(
			trUtf8("Konnte Datei nicht öffnen: \"")+
			csvFile+
			trUtf8("\""));
		return false;
	}

	QTextStream in(
		&file);

	while (!in.atEnd()) 
	{
		QString const line =
			in.readLine();

		compiledFile.push_back(
			line.split(
				trUtf8(",")));
	}

	emit statusMessage(
		QString::number(compiledFile.size())+
		trUtf8(" Zeilen eingelesen..."));

	emit progress(
		0,
		static_cast<int>(
			compiledFile.size()));

	if(compiledFile.empty())
		return true;

	if(column < 0 || column >= compiledFile.at(0).size())
	{
		emit errorOccured(
			trUtf8("Ungültige Spalte: \"")+
			QString::number(column+1)+
			trUtf8("\", es gibt ")+
			QString::number(compiledFile.at(0).size())+
			trUtf8(" Spalten insgesamt"));

		compiledFile.clear();

		return false;
	}

	return true;
}

bool
DzCopyer::moveFile(
	bool const simulated,
	int const currentID,
	QString const &s)
{
	QStringList const filesMatching =
		sourceDir.entryList(
			QStringList(
				trUtf8("*")+
				s+
				trUtf8("*")));

	if(filesMatching.empty())
	{
		emit errorOccured(
			trUtf8("Zum Spalteneintrag: \"")+
			s+
			trUtf8("\" gibt es keine Dateien."));
		return false;
	}

	if(filesMatching.size() > 1)
	{
		emit errorOccured(
			trUtf8("Zum Spalteneintrag: \"")+
			s+
			trUtf8("\" gibt es mehrere Dateien: ")+
			filesMatching.join(
				trUtf8(", ")));
		return false;
	}

	QString const matchingFile =
		filesMatching.at(
			0);

	QString const targetPrefix =
		QString("%1").arg(
			currentID,
			5,
			10,
			QLatin1Char('0'));

	QString const targetFile =
		targetPrefix+
		trUtf8("_")+
		matchingFile;

	emit statusMessage(
		trUtf8("Verschiebe: \"")+
		matchingFile+
		trUtf8("\" nach \"")+
		targetFile+
		trUtf8("\""));

	if(!simulated)
	{
		if(!QFile::copy(sourceDir.absoluteFilePath(matchingFile),destDir.absoluteFilePath(targetFile)))
		{
			emit errorOccured(
				trUtf8("Fehler beim Verschieben!"));
			return false;
		}
	}

	return true;
}
