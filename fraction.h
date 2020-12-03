#ifndef FRACTION_H
#define FRACTION_H

#include <QString>

class Fraction
{
public:
    Fraction(int top,int bot);
    Fraction(int top);



    Fraction multiply(Fraction f);
    Fraction multiply(int constant);

    Fraction divide(Fraction f);
    Fraction divide(int constant);

    Fraction add(Fraction f);
    Fraction add(int constant);

    Fraction subtract(Fraction f);
    Fraction subtract(int constant);

    bool isInteger();

    Fraction invert(){return Fraction(m_bot,m_top);}

    int top(){return m_top;}
    int bot(){return m_bot;}

    float evaluate(){return float(m_top)/float(m_bot);}

    Fraction reduce();

    bool isNull(){if(m_top == 0){return true;}else{return false;}}

    QString toString();


private:
    int m_top;
    int m_bot;
};

#endif // FRACTION_H
