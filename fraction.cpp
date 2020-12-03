#include "fraction.h"

#include <QDebug>

Fraction::Fraction(int t, int b)
{
    m_top = t;
    m_bot = b;
}

Fraction::Fraction(int top)
{
    m_top = top;
    m_bot = 1;
}

Fraction Fraction::multiply(Fraction f)
{
    return Fraction(m_top * f.top(),m_bot * f.bot()).reduce();
}

Fraction Fraction::multiply(int constant)
{
    if(constant!=0){
        return Fraction(m_top * constant,m_bot * constant);
    }else{
        return Fraction(0,1);
    }
}

Fraction Fraction::divide(Fraction f)
{
    return multiply(f.invert());
}

Fraction Fraction::divide(int constant)
{
    return multiply(Fraction(1,constant));
}

Fraction Fraction::add(Fraction f)
{
    if(f.bot() != m_bot){
        m_top = m_top * f.bot();
        f = f.multiply(m_bot);
        m_bot = f.bot();
    }
    return Fraction(m_top + f.top(), m_bot);
}

Fraction Fraction::add(int constant)
{
    return Fraction(m_top + constant * m_bot, m_bot);
}

Fraction Fraction::subtract(Fraction f)
{
    Fraction f2 = Fraction(f.top() * -1,f.bot());
    return add(f2);
}

bool Fraction::isInteger()
{
    if(m_top == m_bot){
        return true;
    }
    return false;
}

Fraction Fraction::reduce()
{
    if(m_top == 0){
        return Fraction(0,1);
    }
    int range = abs(m_top);
    if(abs(m_bot)<range){
        range = abs(m_bot);
    }
    for(int i=range; i>1; i--){
        if((m_top%i)==0 && (m_bot%i) == 0){
            return Fraction(int(m_top/i),int(m_bot/i));
        }
    }
    if(m_bot < 0){
        m_top *=-1;
        m_bot *=-1;
    }
    return *this;
}

QString Fraction::toString()
{
    if(m_top == 0){
        return "0";
    }
    if(m_bot == 1 || m_bot == -1){
        return QString::number(m_top/m_bot);
    }
    if(abs(m_top) == abs(m_bot)){
        return QString::number(int(m_top/m_bot));
    }
    if(m_bot<0){
        return QString::number(m_top*-1)+"/"+QString::number(m_bot*-1);
    }


    return QString::number(m_top)+"/"+QString::number(m_bot);
}


