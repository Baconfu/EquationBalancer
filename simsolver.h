#ifndef SIMSOLVER_H
#define SIMSOLVER_H

#include <QVector>

#include <fraction.h>

class SimSolver
{
public:
    SimSolver(QVector<QVector<Fraction>> matrix);

    QVector<QVector<Fraction>> getState(){return m_matrix;}
    void toEchelon();

    QVector<Fraction> getSolutionSet(QVector<Fraction> freeVariable_values);

    QVector<Fraction> findSmallestIntegerSolution();

private:
    QVector<QVector<Fraction>> m_matrix;

    void divideRow(int row,Fraction factor);
    QVector<Fraction> multiplyRow(QVector<Fraction> row, Fraction factor);

    void subtractRow(int row1,int row2);
    void subtractRow(QVector<Fraction>,int row2);


    QVector<int> getFreeVar();
    int getPivot(QVector<Fraction> row);

    int LCM(QVector<int> integers);

    QVector<int> freeVar;


    int row_count = 0;
    int column_count = 0;
    int variable_count = 0;
};

#endif // SIMSOLVER_H
