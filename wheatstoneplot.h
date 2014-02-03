#ifndef WHEATSTONEPLOT_H
#define WHEATSTONEPLOT_H

#include "plot.h"

class wheatstonePlot : public Plot
{
public:
    wheatstonePlot(QWidget * parent = NULL);
    void calculer(void);
private:
    float m_min, m_max, m_tpsMax10, m_tpsMax30, m_tpsMin10, m_tpsMontee, m_tpsPalier, m_variation;
    int m_indexMin, m_indexMax;
    void findMinMax();
    void tpsMontee();
    void tpsPalier();
    void variation();



};

#endif // WHEATSTONEPLOT_H
