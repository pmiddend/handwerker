#ifndef DANIEL_ZEICHENSAETZE_DZMAINCLASS
#define DANIEL_ZEICHENSAETZE_DZMAINCLASS

#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
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
	directoryChooserClicked();

	void
	fileChooserClicked();

	void
	goClicked();
private:
	QLabel *directoryChooserLabel;
	QLineEdit *directoryChooserFile;
	QPushButton *directoryChooserButton;
	QHBoxLayout *directoryChooserLayout;
	QWidget *directoryChooserWidget;

	QLabel *fileChooserLabel;
	QLineEdit *fileChooserFile;
	QPushButton *fileChooserButton;
	QHBoxLayout *fileChooserLayout;
	QWidget *fileChooserWidget;

	QTextEdit *textInput;
	QPushButton *goButton;
	QVBoxLayout *layout;
	QWidget *window;
};

#endif
