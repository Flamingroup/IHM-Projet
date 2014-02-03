#include "plot.h"
#include <fstream>

#include <iostream>
Plot::Plot( QWidget *parent ):
    QwtPlot( parent )

{


    this->setAutoReplot(true);
    m_currentX = 0;
    m_paintedPoints = 0;

    m_curve = new QwtPlotCurve("Values received on serial port");
    m_curve->attach(this);
    m_curve->setSamples(m_points);
    QPen pen = m_curve->pen();
    pen.setColor(QColor(255,0,0,127));
    m_curve->setPen(pen);
    m_pas = 1;
}

Plot::~Plot()
{
}


void Plot::updCurve(const float p)
{
    QPointF point(m_currentX, p);

    m_points.append(point);
    m_curve->setSamples(m_points);

    setAxisScale(xBottom, 0, m_currentX);
    setAxisAutoScale(yLeft);
    m_currentX += m_pas;
}


void Plot::saveCurve(string filepath)
{

    if(m_currentX != 0)
    {
        std::ofstream output(filepath.c_str(), std::ios_base::trunc);   // if file exist, erase it and write date then

        //todo : check opening


        std::string line;

        float i = 0;
        while(i<m_points.size())
        {
            line = QString::number(m_points[i].y()).toStdString() + '\n';
            output<<line;
            ++i;
        }

        output.close();
    }
}

void Plot::clearCurve(void)
{
    m_points.clear();
    m_curve->setSamples(m_points);

    m_currentX = 0;
}

