#include "mainwindow.h"
#include "portselection.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QMessageBox>
#include <time.h>
#include <iostream>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <QGridLayout>
#include <QFileDialog>
#include <fstream>
#include <QBuffer>
#include <QVariant>
///
#include <sstream>      // std::stringstream
///
using namespace std;

bool RXfree = true;
char m_RXmessage[7];
quint16 messByte = 0;
QBuffer buffer;
QByteArray tableau;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateQuery()));
    m_timer->start(1000);
    m_plot = new Plot(this);
    m_vect = new QListView(this);
    ListModel=new QStandardItemModel();
    this->setMinimumSize(700, 500);
    m_vect->setMinimumWidth(150);
    m_vect->setMaximumWidth(250);
    m_command=new QLineEdit(this);
    m_sendCommand = new QPushButton(this);
    connect(m_sendCommand, SIGNAL(clicked()), this, SLOT(onSendCommandPressed()));
    m_sendCommand->setText("Envoyer commande");
    /*
     *Pour que le bouton ajuste sa taille lorsque l'on agrandit la fenetre
     *m_sendCommand->????();
     */
    m_sendCommand->setMinimumWidth(150);
    m_sendCommand->setMaximumWidth(250);

    QwtPlotMagnifier* magnifier = new QwtPlotMagnifier(m_plot->canvas());
    QwtPlotPanner* panner = new QwtPlotPanner(m_plot->canvas());
    panner->setMouseButton(Qt::LeftButton);

    QWidget * centralArea = new QWidget;
    QHBoxLayout *plotAndVect = new QHBoxLayout;
    QHBoxLayout *cmdLineAndButton = new QHBoxLayout;
    QVBoxLayout *central = new QVBoxLayout;

    plotAndVect->addWidget(m_plot);
    plotAndVect->addWidget(m_vect);
    cmdLineAndButton->addWidget(m_command);
    cmdLineAndButton->addWidget(m_sendCommand);

    central->addLayout(plotAndVect);
    central->addLayout(cmdLineAndButton);
    centralArea->setLayout(central);

    this->setCentralWidget(centralArea);


    this->createActions();
    this->createMenus();
    this->createStatusBar();


}

MainWindow::~MainWindow()
{
    
}

void MainWindow::createMenus(void)
{
    m_fileMenu = menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_startRead);
    m_fileMenu->addAction(m_stopRead);
     m_fileMenu->addAction(m_calculer);
    m_fileMenu->addAction(m_saveCurve);
    m_fileMenu->addAction(m_loadCurve);
    m_fileMenu->addAction(m_quit);

    m_viewMenu = menuBar()->addMenu("&View");
    m_viewMenu->addAction(m_clearCurve);

    m_setupMenu = menuBar()->addMenu("&Setup");
    m_setupMenu->addAction(m_selectSerialPort);

    m_helpMenu = menuBar()->addMenu("&Help");
    m_helpMenu->addAction(m_about);
    m_helpMenu->addAction(m_aboutQt);
}

void MainWindow::createActions(void)
{
    m_startRead = new QAction("Start reading", this);
    connect(m_startRead, SIGNAL(triggered()), this, SLOT(startReadingPort()));
    m_stopRead = new QAction("Stop reading", this);
    connect(m_stopRead, SIGNAL(triggered()), this, SLOT(stopReadingPort()));
    m_calculer = new QAction("Calculer", this);
    connect(m_calculer, SIGNAL(triggered()), this, SLOT(calculer()));
    m_saveCurve = new QAction("Save curve", this);
    connect(m_saveCurve, SIGNAL(triggered()), this, SLOT(saveCurve()));
    m_loadCurve = new QAction("Load curve", this);
    connect(m_loadCurve, SIGNAL(triggered()), this, SLOT(loadCurve()));
    m_quit = new QAction("Exit", this);
    connect(m_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_clearCurve = new QAction("Clear curve", this);
    connect(m_clearCurve, SIGNAL(triggered()), this, SLOT(clearCurve()));

    m_selectSerialPort = new QAction("Select serial port", this);
    connect(m_selectSerialPort, SIGNAL(triggered()), this, SLOT(selectSerialPort()));

    m_about = new QAction("About this application", this);
    connect(m_about, SIGNAL(triggered()), this, SLOT(about()));
    m_aboutQt = new QAction("About Qt", this);
    connect(m_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


}

void MainWindow::createStatusBar(void)
{
    m_status = new QLineEdit("No port opened", this);
    m_status->setAlignment(Qt::AlignHCenter);
    m_status->setReadOnly(true);
    /*
    m_labelStatusBar = new QLabel("Measure in Volts");
    m_labelStatusBar->setAlignment(Qt::AlignHCenter);

    m_dataMeasured = new QLineEdit(this);
    m_dataMeasured->setAlignment(Qt::AlignHCenter);
    m_dataMeasured->setReadOnly(true);
    */
    statusBar()->addWidget(m_status,1);
    //statusBar()->addWidget(m_labelStatusBar);
    //statusBar()->addWidget(m_dataMeasured);

    m_port = new QextSerialPort;



}


void MainWindow::startReadingPort(void)
{
    if(!m_port->open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(0, "Error !", tr("Can't open port with specified settings !"));
    }

    else
    {
        m_status->setText(tr("Port %1 open, reading in process").arg(m_port->portName()));
        connect(m_port, SIGNAL(readyRead()), this, SLOT(onDataReceived()));
    }
}


void MainWindow::stopReadingPort(void)
{

        m_status->setText(tr("Reading stopped on port %1").arg(m_port->portName()));
        m_port->close();

}

void MainWindow::saveCurve(void)
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save file"), QString(), tr("CSV file (*.csv)"));
    m_plot->saveCurve(file.toStdString());
}

void MainWindow::loadCurve(void)
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), tr("CSV file (*.csv)"));
    vector<float> vect;
    ifstream curveFile(file.toStdString().c_str());
    if(!curveFile)
    {
        QMessageBox::warning(this, tr("Error while trying to open file"), tr("Can't open file, an error occured"));
        return;
    }

    else
    {
        m_plot->clearCurve(); //à implémenter pour enlever les valeurs lorsque l'on charge un fichier
        m_vect->clearSelection();
        ListModel->clear();

        string val;
        getline(curveFile, val);


        while(val.size() != 0)
        {
            m_plot->updCurve(QString(val.c_str()).toFloat());
            ListModel->appendRow(new QStandardItem(QString(val.c_str())));
            m_vect->setModel(ListModel);
            getline(curveFile, val);
        }

    }

    QMessageBox::information(this, tr("Loading curve"), tr("Curve has been loaded successfully !"));

}

void MainWindow::clearCurve(void)
{
    m_plot->clearCurve();
}

void MainWindow::selectSerialPort()
{
    m_port = new QextSerialPort;

    PortSelection *select = new PortSelection(m_port, this);
    select->exec();

    m_status->setText(tr("Port %1 is not open").arg(m_port->portName()));

}

void MainWindow::about()
{}

void MainWindow::onDataReceived(void)
{

    if(RXfree == true)
    {
        receive();
    }
}

void MainWindow::calculer()
{
   // feature disabled (corresponds to another coursework
    // m_plot->calculer();
}

void MainWindow::onSendCommandPressed()
{
    // do something
    if (!m_port->isOpen()){
        this->startReadingPort();
    }
    else {
            QString tmp_stock = m_command->text();
            if (!tmp_stock.isEmpty()) {
                tmp_stock.append("\r\n");
                m_port->write(tmp_stock.toStdString().c_str());
                m_status->setText("Command sent : "+tmp_stock);
            }
            m_command->setText("");
    }
}

void MainWindow::updateQuery()
{
    if (!m_port->isOpen()){
        //this->startReadingPort();
    }
    else {
        QString tmp_stock("0R2");
            if (!tmp_stock.isEmpty()) {
                tmp_stock.append("\r\n");
                m_port->write(tmp_stock.toStdString().c_str());
            }
    }
}

void MainWindow::receive()
{
    float val;
    tableau.append(m_port->readAll());
    m_status->setText("Receiving");
    //if non empty datagram
    if(tableau.contains('\n'))
    {
        string recu(tableau);//Th=
        string target="Th=";
        const char *temp;
        float f;
        stringstream flux;
        cout<<string(tableau)<<endl;
        /*
          string temp2(temp);
          int pos = temp2.find('\n');
          string temp3=temp2.substr(4, pos);
          cout<<"temp3"<<temp3<<endl;
          flux<<temp3;
          flux>>f;
          cout<<"T="<<f<<endl;
        *
        //m_dataMeasured->setText(QString(tableau));
        tableau.truncate(tableau.indexOf('\r'));
        val = tableau.toDouble();
        //array.clear();
        ///m_plot->updCurve(val);
        m_plot->updCurve(f);
        //QVariant * float_value=new QVariant(val);
        QString str(tableau);
        for (QString s : str.split(",")){
            ListModel->appendRow(new QStandardItem(s));
        }
        //ListModel->appendRow(new QStandardItem(float_value->toString()));
        tableau.clear();
        m_vect->setModel(ListModel);
        */
    }
}





