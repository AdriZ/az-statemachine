#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include "smdescription.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	// Open/Create file in write mode
	bool openOutFile( QFile & file );

public slots:
	void open();

private:
    Ui::MainWindow *ui;

	void createActions();
	void createMenus();

	bool generateDot( QString baseName );
	bool generateH( QString baseName );
	bool generateC( QString baseName );
	bool generateTxt( QString baseName );

	QMenu *fileMenu;
	QAction *openAct;
	QAction *exitAct;

	QString		m_inFileName;
	QFileInfo	m_inFileInfo;
	bool		m_inFileHasBeenParsed;
	SMDescription	m_stateMachineDesc;


private slots:
	void on_generateButton_clicked();

};

#endif // MAINWINDOW_H
