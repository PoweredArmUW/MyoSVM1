#ifndef LPF_H
#define LPF_H

#include <cmath>
#include <assert.h>

const double TOL = 1E-6;

using namespace std;

class LowPassFilter
{
private:
    double m_alpha;
    double m_y;
    double m_s;
public:
    LowPassFilter()
    {
        m_alpha = 0;
        m_y = 0;
        m_s = 0;
    }

    LowPassFilter(double alpha)
    {
        m_alpha = setAlpha(alpha);
        m_y = 0;
        m_s = 0;
    }

    double setAlpha(double alpha)
    {
        assert(alpha > 0 && alpha < 1.0);
        return alpha;
    }

    //call function
    double filter(double value, double alpha = 0)
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

    double returnLastValue()
    {
        return m_y;
    }
};

#endif // LPF_H
