#include <cmath>
#include <iostream>
#include <array>

using namespace std;

class LowPassFilter()
{
private:
    double m_alpha;
    double m_y;
    double m_s;
public:
    LowPassFilter()
    {
        m_alpha = 0;
        y = 0;
        s = 0;
    }
    LowPassFilter(double alpha)
    {
        m_alpha = setAlpha(alpha);
        y = 0;
        s = 0; 
    }


    double setAlpha(double alpha)
    {
        if(alpha <= 0 || alpha > 1.0)
        {
            assert(alpha <= 0 || alpha > 1.0)
        }
        return alpha;
    }

    //call function
    double filter(double value, double timestamp = 0, double alpha = 0)
    {
        //this one is sketchy
        if(m_alpha == 0)
            m_alpha = setAlpha(alpha); 
        if(m_y == 0)
            m_s = value;
        else
            m_s = m_alpha*value + (1.0-m_alpha)*m_s;
        m_y = value;
        return m_s;
    }

    double returnLastValue()
    {
        return m_y;
    }
};

class OneEuroFilter()
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
    OneEuroFilter(int freq, double mincutoff = 1.0, beta = 0.0, dcutoff = 1.0)
    {
        assert(freq > 0);
        assert(mincutoff > 0);
        assert(dcutoff > 0 );
        m_freq = freq;
        m_mincutoff = mincutoff;
        m_beta = beta;
        m_dcutoff = dcutoff;
        m_x = LowPassFilter(mincutoff);
        m_dx = LowPassFilter(dcutoff)
        m_lasttime = 0;
    }

    double alpha(double cutoff)
    {
        double te = 1.0/m_freq;
        double tau = 1.0/(M_PI*2*cutoff);
        return 1.0/(1.0+tau/te);
    }

    //call function
    double filter(double x, double timestamp = 0)
    {
        if(m_lasttime && timestamp != 0)
            m_freq = 1.0/(timestamp - m_lasttime);
        m_lasttime = timestamp;
        double prev_x = m_x.returnLastValue();
        double dx;
        if(prev_x == 0)
            dx = 0.0;
        else
            dx = (x - prev_x)*m_freq;
        edx = m_dx.filter(dx, timestamp, alpha(m_dcutoff));
        double cutoff = m_mincutoff + m_beta * fabs(edx.filter); 
        return m_x.filter(x, timestamp, alpha(cutoff)); 
    }

    double checkAccuracy(double predicted[], double goldset[])
    {
        int correct = 0;
        for (int i = 0; i<predicted.size(); i ++)
        {
            if (predicted[i] == goldset[i])
                correct+=1;
        }
        return 100.0*correct/predicted.size();
    }

    double CustomScatter()
    {
        //code
    }
};

//load array
//split train and labels array

int freq = 200;
double mincutoff = 0.8, beta = 0.4, dcutoff = 1.0;
double duration = 1.0;

f=  OneEuroFilter(freq,mincutoff,beta,dcutoff);
double timestamp = 20;
//this wont run??
while (timestamp < duration)
{
    double filtered = f.filter(train, timestamp);  //does it take a array value??
    timestamp += 1.0/freq;
}

