#include <cmath>
#include <assert.h>
#include "LowPassFilter.h"

const double TOL = 1E-6;

LowPassFilter::LowPassFilter()
{
    m_alpha = 0;
    m_y = 0;
    m_s = 0;
}

LowPassFilter::LowPassFilter(double alpha)
{
    m_alpha = setAlpha(alpha);
    m_y = 0;
    m_s = 0;
}

double LowPassFilter::setAlpha(double alpha)
{
    assert(alpha > 0 && alpha < 1 + TOL);
    return alpha;
}

//call function
double LowPassFilter::filter(double value, double alpha)
{
    double s;
    if(fabs(m_alpha) < TOL) //if alpha = 0
        m_alpha = setAlpha(alpha);
    if(fabs(m_alpha) < TOL)
        s = value;
    else
        s = m_alpha*value + (1.0-m_alpha)*m_s;
    m_y = value;
    m_s = s;
    return s;
}

double LowPassFilter::returnLastValue() const
{
    return m_y;
}
