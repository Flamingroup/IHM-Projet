#ifndef KALMANPLOT_H
#define KALMANPLOT_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <string>

using std::string;

class QwtPlotMarker;
class QwtPlotDirectPainter;


class KalmanPlot : public QwtPlot
{
    Q_OBJECT

public:
    KalmanPlot( QWidget * parent = NULL );
    virtual ~KalmanPlot();
    void updCurve(std::vector<float> newMeasures);
    void saveCurve(string filepath);
    void clearCurve(void);
protected:
     QVector<QPointF> m_pointsBrut;
     QVector<QPointF> m_pointsPrefiltre;
     QVector<QPointF> m_pointsKalman;

     QwtPlotCurve* m_curveBrut;
     QwtPlotCurve* m_curvePrefiltre;
     QwtPlotCurve* m_curveKalman;
    //QVector<QPointF> m_points;
    float m_currentX;
    float m_pas;

    QwtPlotCurve* m_curve;
};


#endif // KALMANPLOT_H
