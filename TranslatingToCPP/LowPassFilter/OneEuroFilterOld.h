#ifndef ONEEUROFILTEROLD_H
#define ONEEUROFILTEROLD_H

#include <cmath>
#include "assert.h"
#include "LowPassFilter.h"
const double TOL = 1E-6;
class OneEuroFilter
{
private:
    double m_freq;
    double m_mincutoff;
    double m_beta;
    double m_dcutoff;
    LowPassFilter m_x;
    LowPassFilter m_dx;
    double m_lasttime;
public:
    OneEuroFilter(double freq, double mincutoff = 1.0, double beta = 0.0, double dcutoff = 1.0)
    {
        assert(freq > 0);
        assert(mincutoff > 0);
        assert(dcutoff > 0 );

        m_freq = freq;
        m_mincutoff = mincutoff;
        m_beta = beta;
        m_dcutoff = dcutoff;
        m_x = LowPassFilter(mincutoff);
        m_dx = LowPassFilter(dcutoff);
        m_lasttime = 0;
    }

    double alpha(double rate, double cutoff)
    {
        double te = 1.0/m_freq;
        double tau = 1.0/(rate);
        return 1.0/(1.0+tau/te);
    }

    //call function
    double filter(double x, double timestamp = 0)
    {
        if(fabs(m_lasttime)> TOL && fabs(timestamp > TOL))
            m_freq = 1.0/(timestamp - m_lasttime);
        m_lasttime = timestamp;
        double prev_x = m_x.returnLastValue();
        double dx;
        if(fabs(prev_x) < TOL)
            dx = 0.0;
        else
            dx = (x - prev_x)*m_freq;
        double edx = m_dx.filter(dx, alpha(m_dcutoff));
        double cutoff = m_mincutoff + m_beta * fabs(edx);
        return m_x.filter(x, alpha(cutoff));
    }

    double checkAccuracy(double predicted[], double goldset[])
    {
        int arraySize = sizeof(predicted)/sizeof(*predicted);
        int correct = 0;
        for (int i = 0; i< arraySize; i ++)
        {
            if (predicted[i] == goldset[i])
                correct+=1;
        }
        return 100.0*correct/arraySize;
    }

};
#endif // ONEEUROFILTER_H

