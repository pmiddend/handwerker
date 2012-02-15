#ifndef DANIEL_ZEICHENSAETZE_DZMAINCLASS
#define DANIEL_ZEICHENSAETZE_DZMAINCLASS

#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>
#include <QObject>

class DzMainClass
:
	public QObject
{
Q_OBJECT

public:
	explicit
	DzMainClass();

	~DzMainClass();
public slots:
	void
	sourceDirectoryChooserClicked();

	void
	destDirectoryChooserClicked();

	void
	fileChooserClicked();

	void
	goClicked();

	void
	statusMessage(
		QString const &);

	void
	errorMessage(
		QString const &);

	void
	progress(
		int,
		int);
private:
	QLabel *sourceDirectoryChooserLabel;
	QLineEdit *sourceDirectoryChooserFile;
	QPushButton *sourceDirectoryChooserButton;
	QHBoxLayout *sourceDirectoryChooserLayout;
	QWidget *sourceDirectoryChooserWidget;

	QLabel *destDirectoryChooserLabel;
	QLineEdit *destDirectoryChooserFile;
	QPushButton *destDirectoryChooserButton;
	QHBoxLayout *destDirectoryChooserLayout;
	QWidget *destDirectoryChooserWidget;

	QLabel *fileChooserLabel;
	QLineEdit *fileChooserFile;
	QPushButton *fileChooserButton;
	QHBoxLayout *fileChooserLayout;
	QWidget *fileChooserWidget;

	QLabel *columnChooserLabel;
	QLineEdit *columnLine;
	QHBoxLayout *columnChooserLayout;
	QWidget *columnChooserWidget;

	QTextEdit *logMessages;

	QProgressBar *progressBar;
	QCheckBox *simulated;
	QHBoxLayout *progressAndSimulatedLayout;
	QWidget *progressAndSimulatedWidget;

	QPushButton *goButton;

	QVBoxLayout *layout;
	QWidget *window;
};

#endif
