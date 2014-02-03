#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include "plot.h"
#include "qextserialport.h"
#include "kalmanplot.h"

//class SerialPort;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions(void);
    void createMenus(void);
    void createStatusBar(void);



public slots:
    void startReadingPort(void);
    void stopReadingPort(void);
    void saveCurve(void);
    void loadCurve(void);
    void clearCurve(void);
    void selectSerialPort(void);
    void about(void);
    void onDataReceived(void);
    void calculer(void);

signals:
    void dataAcquired();

private:

     QextSerialPort* m_port;

    KalmanPlot* m_plot;
    //QwtPlotCurve* m_curve;
    //QVector<QPointF> m_points;


    QMenu* m_fileMenu;
    QMenu* m_viewMenu;
    QMenu* m_setupMenu;
    QMenu* m_helpMenu;

    QAction* m_startRead;
    QAction* m_stopRead;
    QAction* m_calculer;
    QAction* m_saveCurve;
    QAction* m_loadCurve;
    QAction* m_quit;

    QAction* m_clearCurve;

    QAction* m_selectSerialPort;

    QAction* m_about;
    QAction* m_aboutQt;

    QLineEdit* m_status;
    QLabel* m_labelStatusBar;
    QLineEdit* m_dataMeasured;

    void receive();


};

#endif // MAINWINDOW_H
