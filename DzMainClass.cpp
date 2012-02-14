#include "DzMainClass.hpp"
#include <QFileDialog>
#include <iostream>

DzMainClass::DzMainClass()
{
	directoryChooserLabel = new QLabel(tr("Zeichensatzverzeichnis:"));
	directoryChooserFile = new QLineEdit;
	directoryChooserButton = new QPushButton(tr("Durchsuchen..."));
	directoryChooserLayout = new QHBoxLayout;
	directoryChooserLayout->addWidget(
		directoryChooserLabel);
	directoryChooserLayout->addWidget(
		directoryChooserFile);
	directoryChooserLayout->addWidget(
		directoryChooserButton);
	directoryChooserWidget = new QWidget();
	directoryChooserWidget->setLayout(
		directoryChooserLayout);

	fileChooserLabel = new QLabel(tr("CSV-Datei:"));
	fileChooserFile = new QLineEdit;
	fileChooserButton = new QPushButton(tr("Durchsuchen..."));
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

	textInput = new QTextEdit();
	goButton = new QPushButton(tr("Go!"));
	layout = new QVBoxLayout();

	layout->addWidget(
		directoryChooserWidget);

	layout->addWidget(
		fileChooserWidget);

	layout->addWidget(
		textInput);

	layout->addWidget(
		goButton);

	window = new QWidget();

	window->setLayout(
		layout);

	window->show();

	QObject::connect(
		directoryChooserButton,
		SIGNAL(clicked()),
		this,
		SLOT(directoryChooserClicked()));

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
}

void
DzMainClass::directoryChooserClicked()
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

		directoryChooserFile->setText(
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
		tr("CSV Files (*.csv)"));

	if (dialog.exec())
	{
		QStringList const directoryNames =
			 dialog.selectedFiles();

		Q_ASSERT(
			 directoryNames.size() == 1);

		directoryChooserFile->setText(
			directoryNames.at(
				0));
	}
}

DzMainClass::~DzMainClass()
{
}
