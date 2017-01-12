#ifndef LPF_H
#define LPF_H

class LowPassFilter
{
private:
    double m_alpha;
    double m_y;
    double m_s;
public:
    LowPassFilter();
    LowPassFilter(double alpha);
    double setAlpha(double alpha);
    double filter(double value, double alpha = 0);
    double returnLastValue() const;
};

#endif // LPF_H
