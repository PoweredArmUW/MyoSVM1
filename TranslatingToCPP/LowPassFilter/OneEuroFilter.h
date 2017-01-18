#ifndef ONEEUROFILTER_H
#define ONEEUROFILTER_H

#include <cmath>
#include "assert.h"
#include "LowPassFilter.h"
const double TOL = 1E-6;
class OneEuroFilter
{
private:
    bool m_firstTime;
    double m_rate; //data update rate
    double m_mincutoff; //minimum cutoff frequency
    double m_dcutoff; //cutoff frequency for derivate
    double m_beta; //cutoff slope

    LowPassFilter m_xfilt; //low pass filter
    LowPassFilter m_dxfilt; //low pass filter for derivate

public:
    OneEuroFilter(double rate, double mincutoff = 1.0, double beta = 0.0, double dcutoff = 1.0)
    {
        m_firstTime = true;
        m_rate = rate;
        m_mincutoff = mincutoff;
        m_beta = beta;
        m_dcutoff = dcutoff;
    }

    double alpha(double rate, double cutoff)
    {
        double te = 1.0/(2.0*M_PI*cutoff);
        double tau = 1.0/(rate);
        return 1.0/(1.0+tau/te);
    }

    //call function
    double filter(double x)
    {
        double dx;
        if(m_firstTime)
        {
            m_firstTime = false;
            dx = 0;
        }
        else
        {
            dx = (x - m_xfilt.returnLastValue())*m_rate;
        }
        double edx = m_dxfilt.filter(dx, (*this).alpha(m_rate, m_dcutoff));
        double cutoff = m_mincutoff+m_beta*fabs(edx);
        return m_xfilt.filter(x, alpha(m_rate, cutoff));
    }
/*
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
*/
};
#endif // ONEEUROFILTER_H
