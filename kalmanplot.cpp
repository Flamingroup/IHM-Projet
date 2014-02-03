#include "kalmanplot.h"
#include <fstream>
#include <iostream>


KalmanPlot::KalmanPlot( QWidget *parent ):
    QwtPlot( parent )
{
    this->setAutoReplot(true);
    m_currentX = 0;

    m_curve = new QwtPlotCurve("Values received on serial port");

    m_curveBrut = new QwtPlotCurve("Brut values");
    m_curvePrefiltre = new QwtPlotCurve("Prefiltered values");
    m_curveKalman = new QwtPlotCurve("Filtered values");

    m_curveBrut->attach(this);
    m_curvePrefiltre->attach(this);
    m_curveKalman->attach(this);

    m_curveBrut->setSamples(m_pointsBrut);
    m_curvePrefiltre->setSamples(m_pointsPrefiltre);
    m_curveKalman->setSamples(m_pointsKalman);

    QPen penBrut = m_curveBrut->pen();
    penBrut.setColor(QColor(Qt::black)); // brut
    penBrut.setStyle(Qt::DashDotLine);
    m_curveBrut->setPen(penBrut);

    QPen penPrefiltre = m_curvePrefiltre->pen();
    penPrefiltre.setColor(QColor(Qt::darkRed)); // Prefiltre
    penPrefiltre.setStyle(Qt::DashLine);
    m_curvePrefiltre->setPen(penPrefiltre);

    QPen penKalman = m_curveKalman->pen();
    penKalman.setColor(QColor(Qt::green));
    penKalman.setStyle(Qt::SolidLine);
    m_curveKalman->setPen(penKalman);


    // Qt::darkRed  // prefiltre
    // Qt::green    // kalman
    //  brut
    //
    //   kalman



    m_pas = 1;
}

KalmanPlot::~KalmanPlot()
{
}

void KalmanPlot::updCurve(std::vector<float> newMeasures)    // replace parameter by vector<float> newValues
{
     QPointF p_brut(m_currentX, newMeasures[0]);
     QPointF p_prefiltre(m_currentX, newMeasures[1]);
     QPointF p_kalman (m_currentX, newMeasures[2]);

     m_pointsBrut.append(p_brut);
     m_pointsPrefiltre.append(p_prefiltre);
     m_pointsKalman.append(p_kalman);

    m_curveBrut->setSamples(m_pointsBrut);
    m_curvePrefiltre->setSamples(m_pointsPrefiltre);
    m_curveKalman->setSamples(m_pointsKalman);

    setAxisScale(xBottom, 0, m_currentX);   // modifier minimum (quand il y a trop de valeurs, trop tassé
    setAxisAutoScale(yLeft);
    m_currentX += m_pas;
}


void KalmanPlot::saveCurve(string filepath)
{

    if(m_currentX != 0)
    {
        std::ofstream output(filepath.c_str(), std::ios_base::trunc);   // if file exist, erase it and write date then

        //todo : check opening

        std::string line;

        float i = 0;
        while(i<m_pointsBrut.size())
        {
            line = QString::number(m_pointsBrut[i].y()).toStdString() + '\n';//line += QString::number(m_pointsBrut.y().toStdString()+";");
            line += QString::number(m_pointsPrefiltre[i].y()).toStdString()+";";
            line += QString::number(m_pointsKalman[i].y()).toStdString()+"\n";
            output<<line;
            ++i;
        }

        output.close();
    }
}

void KalmanPlot::clearCurve(void)
{

   m_pointsBrut.clear();
   m_pointsPrefiltre.clear();
   m_pointsKalman.clear();
    m_curveBrut->setSamples(m_pointsBrut);
    m_curvePrefiltre->setSamples(m_pointsPrefiltre);
    m_curveKalman->setSamples(m_pointsKalman);


    m_currentX = 0;
}

