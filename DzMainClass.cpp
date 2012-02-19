#include "DzMainClass.hpp"
#include "DzCopyer.hpp"
#include <QFileDialog>
#include <QDateTime>
#include <QIntValidator>
#include <QDebug>
#include <iostream>

DzMainClass::DzMainClass()
{
	sourceDirectoryChooserLabel = new QLabel(trUtf8("Quellverzeichnis:"));
	sourceDirectoryChooserFile = new QLineEdit;
	sourceDirectoryChooserButton = new QPushButton(trUtf8("Durchsuchen..."));
	sourceDirectoryChooserLayout = new QHBoxLayout;
	sourceDirectoryChooserLayout->addWidget(
		sourceDirectoryChooserLabel);
	sourceDirectoryChooserLayout->addWidget(
		sourceDirectoryChooserFile);
	sourceDirectoryChooserLayout->addWidget(
		sourceDirectoryChooserButton);
	sourceDirectoryChooserWidget = new QWidget();
	sourceDirectoryChooserWidget->setLayout(
		sourceDirectoryChooserLayout);

	destDirectoryChooserLabel = new QLabel(trUtf8("Zielverzeichnis:"));
	destDirectoryChooserFile = new QLineEdit;
	destDirectoryChooserButton = new QPushButton(trUtf8("Durchsuchen..."));
	destDirectoryChooserLayout = new QHBoxLayout;
	destDirectoryChooserLayout->addWidget(
		destDirectoryChooserLabel);
	destDirectoryChooserLayout->addWidget(
		destDirectoryChooserFile);
	destDirectoryChooserLayout->addWidget(
		destDirectoryChooserButton);
	destDirectoryChooserWidget = new QWidget();
	destDirectoryChooserWidget->setLayout(
		destDirectoryChooserLayout);

	fileChooserLabel = new QLabel(trUtf8("CSV-Datei:"));
	fileChooserFile = new QLineEdit;
	fileChooserButton = new QPushButton(trUtf8("Durchsuchen..."));
	fileChooserLayout = new QHBoxLayout;
	fileChooserLayout->addWidget(
		fileChooserLabel);
	fileChooserLayout->addWidget(
		fileChooserFile);
	fileChooserLayout->addWidget(
		fileChooserButton);
	fileChooserWidget = new QWidget();
	fileChooserWidget->setLayout(
		fileChooserLayout);

	columnChooserLabel = new QLabel(trUtf8("Spalte:"));
	columnLine = new QLineEdit(trUtf8("1"));
	columnLine->setMaxLength(3);
	columnLine->setValidator(
		new QIntValidator());

	separatorChooserLabel = new QLabel(trUtf8("Trennzeichen:"));
	separatorChooserLine = new QLineEdit(trUtf8(";"));
	separatorChooserLine->setMaxLength(1);

	settingsLineLayout = new QHBoxLayout;
	settingsLineLayout->addWidget(
		columnChooserLabel);
	settingsLineLayout->addWidget(
		columnLine);
	settingsLineLayout->addWidget(
		separatorChooserLabel);
	settingsLineLayout->addWidget(
		separatorChooserLine);
	settingsLineWidget = new QWidget();
	settingsLineWidget->setLayout(
		settingsLineLayout);

	logMessages = new QTextEdit();

	progressBar = new QProgressBar();
	simulated = new QCheckBox(trUtf8("Simulieren"));

	progressAndSimulatedLayout = new QHBoxLayout;
	progressAndSimulatedLayout->addWidget(
		progressBar);
	progressAndSimulatedLayout->addWidget(
		simulated);
	progressAndSimulatedWidget = new QWidget();
	progressAndSimulatedWidget->setLayout(
		progressAndSimulatedLayout);

	goButton = new QPushButton(trUtf8("Go!"));

	layout = new QVBoxLayout();

	layout->addWidget(
		sourceDirectoryChooserWidget);

	layout->addWidget(
		destDirectoryChooserWidget);

	layout->addWidget(
		fileChooserWidget);

	layout->addWidget(
		settingsLineWidget);

	layout->addWidget(
		logMessages);

	layout->addWidget(
		progressAndSimulatedWidget);

	layout->addWidget(
		goButton);

	window = new QWidget();

	window->setLayout(
		layout);

	window->show();

	QObject::connect(
		sourceDirectoryChooserButton,
		SIGNAL(clicked()),
		this,
		SLOT(sourceDirectoryChooserClicked()));

	QObject::connect(
		destDirectoryChooserButton,
		SIGNAL(clicked()),
		this,
		SLOT(destDirectoryChooserClicked()));

	QObject::connect(
		fileChooserButton,
		SIGNAL(clicked()),
		this,
		SLOT(fileChooserClicked()));

	QObject::connect(
		goButton,
		SIGNAL(clicked()),
		this,
		SLOT(goClicked()));
}

void
DzMainClass::goClicked()
{
	DzCopyer copyer(
		sourceDirectoryChooserFile->text(),
		destDirectoryChooserFile->text(),
		fileChooserFile->text(),
		separatorChooserLine->text(),
		columnLine->text().toInt()-1);

	QObject::connect(
		&copyer,
		SIGNAL(statusMessage(QString const &)),
		this,
		SLOT(statusMessage(QString const &)));

	QObject::connect(
		&copyer,
		SIGNAL(errorOccured(QString const &)),
		this,
		SLOT(errorMessage(QString const &)));

	QObject::connect(
		&copyer,
		SIGNAL(progress(int,int)),
		this,
		SLOT(progress(int,int)));

	copyer.run(
		simulated->isChecked());
}

void
DzMainClass::statusMessage(
	QString const &s)
{
	logMessages->append(
		trUtf8("<em>")+QDateTime::currentDateTime().toString()+trUtf8("</em>: ")+s);
}

void
DzMainClass::errorMessage(
	QString const &s)
{
	logMessages->append(
		trUtf8("<font color=\"red\"><strong>")+
		trUtf8("<em>")+QDateTime::currentDateTime().toString()+trUtf8("</em>: ")+s+
		trUtf8("</strong></font>"));
}

void
DzMainClass::progress(
	int const done,
	int const total)
{
	progressBar->setMinimum(
		0);

	progressBar->setMaximum(
		total);

	progressBar->setValue(
		done);
}

void
DzMainClass::sourceDirectoryChooserClicked()
{
	QFileDialog dialog;

	dialog.setFileMode(
		QFileDialog::Directory);

	dialog.setOption(
		QFileDialog::ShowDirsOnly);

	if (dialog.exec())
	{
		QStringList const directoryNames =
			 dialog.selectedFiles();

		Q_ASSERT(
			 directoryNames.size() == 1);

		sourceDirectoryChooserFile->setText(
			directoryNames.at(
				0));
	}
}

void
DzMainClass::destDirectoryChooserClicked()
{
	QFileDialog dialog;

	dialog.setFileMode(
		QFileDialog::Directory);

	dialog.setOption(
		QFileDialog::ShowDirsOnly);

	if (dialog.exec())
	{
		QStringList const directoryNames =
			 dialog.selectedFiles();

		Q_ASSERT(
			 directoryNames.size() == 1);

		destDirectoryChooserFile->setText(
			directoryNames.at(
				0));
	}
}

void
DzMainClass::fileChooserClicked()
{
	QFileDialog dialog;

	dialog.setFileMode(
		QFileDialog::ExistingFile);

	dialog.setNameFilter(
		trUtf8("CSV Files (*.csv)"));

	if (dialog.exec())
	{
		QStringList const directoryNames =
			 dialog.selectedFiles();

		Q_ASSERT(
			 directoryNames.size() == 1);

		fileChooserFile->setText(
			directoryNames.at(
				0));
	}
}

DzMainClass::~DzMainClass()
{
}
