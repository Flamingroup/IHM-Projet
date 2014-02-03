#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <string>

using std::string;

class QwtPlotMarker;
class QwtPlotDirectPainter;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget * parent = NULL );
    virtual ~Plot();
    void updCurve(const float p);
    void saveCurve(string filepath);
    void clearCurve(void);
protected:
    qint32 m_paintedPoints;
    QVector<QPointF> m_points;
    float m_currentX;
    float m_pas;

    QwtPlotCurve* m_curve;
};


#endif // PLOT_H
