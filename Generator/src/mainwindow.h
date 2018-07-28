#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include "smdescription.h"

#define APP_NAME "AZ-StateMachine Generator"
#define APP_V_MAJ "1"
#define APP_V_MIN "1"
#define APP_V_REV "0"


#define GENERATED_SRC_DIRNAME   "Generated_src"
#define GENERATED_DOC_DIRNAME   "Generated_doc"


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

    void openParsePreviousFile();

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
