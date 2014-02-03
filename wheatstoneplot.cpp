#include "wheatstoneplot.h"
#include <QMessageBox>

wheatstonePlot::wheatstonePlot(QWidget *parent) : Plot(parent)
{
    m_pas = 0.2;
}

void wheatstonePlot::calculer()
{
    if(m_currentX > 1+m_pas)
    {
        findMinMax();
        tpsMontee();

        QMessageBox::information(this, "Results", QString("Max : %1 ").arg(m_max)

                                 + QString("Min : %3 ").arg(m_min)
                                 + QString("\nTemps Montée : %1").arg(m_tpsMontee)
                                 + QString ("\nTemps de Palier : %1").arg(m_tpsPalier)
                                 + QString ("\nPourcentage de niveau : %1%").arg(m_variation));
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Not enough value to execute this operation");
    }


}

void wheatstonePlot::findMinMax()
{

    float y = m_points[1].y();
    m_min = y; m_indexMin = 0;
    m_max = y; m_indexMax = 0;


    for(int i = 2; i < m_points.size(); ++i )
    {
        y = m_points[i].y();
        if(y > m_max){
            m_max = y;
            m_indexMax = i;
        }
        if(y < m_min){
            m_min = y;
            m_indexMin = i;
        }
    }

}

void wheatstonePlot::tpsMontee()
{
    m_tpsMontee = 0;
    float min = 1.10*m_min;
    float max = 0.9*m_max;
    float indexMax = 0;
    float indexMin = 0;
    bool findMin=false, findMax=false;
    float y;

    for(int i =0; i < m_points.size(); ++i )
    {
        y = m_points[i].y();
        if(y >= max && (!findMax) ){
            indexMax = i;
            findMax = true;
        }
        if(y >= min && !findMin){
            min = y;
            indexMin = i;
            findMin = true;
        }
    }

    m_tpsMax10 = m_pas*indexMax;
    m_tpsMin10 = m_pas*indexMin;
    m_tpsMontee = (m_tpsMax10) - (m_tpsMin10);

}


void wheatstonePlot::tpsPalier()
{
    m_tpsPalier = 0;
    float max30 = 0.7*m_max;
    float indexSeuil = 0;
    float y;

    for(int i =0; i < m_points.size(); ++i )
    {
         y = m_points[i].y();
        if(y < max30){
            indexSeuil = i;
            break;
        }
    }

    m_tpsMax30 = m_pas*indexSeuil;

    m_tpsPalier = m_tpsMax10 - m_tpsMax30;

}

void wheatstonePlot::variation()
{
    float seuil1, seuil2;

    seuil1 = m_points[(m_tpsPalier+1)/m_pas].y();
    seuil2 = m_points[(m_tpsPalier-1)/m_pas].y();

    m_variation = (seuil2 - seuil1) * 100;
}

