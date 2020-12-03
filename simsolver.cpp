#include "simsolver.h"

#include <QDebug>

SimSolver::SimSolver(QVector<QVector<Fraction>> matrix)
{
    m_matrix = matrix;
    row_count = m_matrix.length();
    column_count = m_matrix[0].length();
    variable_count= column_count;
}

void SimSolver::divideRow(int row, Fraction factor)
{
    for(int i=0; i<m_matrix[row].length(); i++){
        m_matrix[row][i] = m_matrix[row][i].divide(factor);
    }

}

QVector<Fraction> SimSolver::multiplyRow(QVector<Fraction> row, Fraction factor)
{
    QVector<Fraction> out;
    for(int i=0; i<row.length(); i++){
        out.append(row[i].multiply(factor));
    }
    return out;
}

void SimSolver::subtractRow(int row1, int row2)
{
    for(int i=0; i<m_matrix[row1].length(); i++){
        m_matrix[row2][i] = m_matrix[row2][i].subtract(m_matrix[row1][i]);
    }
}

void SimSolver::subtractRow(QVector<Fraction> row1, int row2)
{
    for(int i=0; i<row1.length(); i++){
        m_matrix[row2][i] = m_matrix[row2][i].subtract(row1[i]);
    }
}

QVector<int> SimSolver::getFreeVar()
{
    QVector<int> out;
    for(int i=0; i<row_count; i++){
        bool pivotFound = false;
        for(int j=0; j<column_count; j++){
            if(pivotFound && !m_matrix[i][j].isNull()){
                if(!out.contains(j)){
                    out.append(j);
                }
            }
            if(!m_matrix[i][j].isNull()){
                pivotFound = true;
            }

        }
    }

    return out;
}

int SimSolver::getPivot(QVector<Fraction> row)
{
    for(int i=0; i<row.length(); i++){
        if(!row[i].isNull()){
            return i;
        }
    }
    return -1;
}

int SimSolver::LCM(QVector<int> integers)
{
    int multiple=1;
    for(int i=0; i<integers.length(); i++){
        multiple*=integers[i];
    }
    for(int i=2; i<multiple; i++){
        bool fail = false;
        for(int j=0; j<integers.length(); j++){
            if(i % integers[j] != 0){
                fail = true;
                break;
            }
        }

        if(!fail){
            return i;
        }
    }
    return multiple;
}



void SimSolver::toEchelon()
{
    int count = 0;

    int offset = 0;
    for(int i=0; i<row_count+offset; i++){
        count+=1;
        if(i == variable_count){
            break;
        }
        bool found = false;
        for(int loop=0; loop<row_count; loop++){
            if(m_matrix[i-offset][i].isNull()){
                QVector<Fraction> temp = m_matrix[i-offset];
                m_matrix.removeAt(i-offset);
                m_matrix.append(temp);
            }else{
                found = true;

                divideRow(i-offset,m_matrix[i-offset][i]);
                break;
            }
        }
        if(!found){
            offset+=1;
            continue;
        }


        if(count == 4){
            qDebug()<<"YOOO";
            for(int i=0; i<m_matrix.length(); i++){
                QString row = "";
                for(int j=0; j<m_matrix[0].length(); j++){
                    row+=m_matrix[i][j].reduce().toString() + " ";
                }
                qDebug()<<row;
            }
            qDebug()<<"\n";
        }



        for(int j=i-offset+1; j<row_count; j++){
            if(!m_matrix[j][i].isNull()){
                divideRow(j,m_matrix[j][i]);
                subtractRow(i-offset,j);
            }
        }

        for(int i=0; i<m_matrix.length(); i++){
            QString row = "";
            for(int j=0; j<m_matrix[0].length(); j++){
                row+=m_matrix[i][j].reduce().toString() + " ";
            }
            qDebug()<<row;
        }
        qDebug()<<"\n";
    }
    offset=0;

    for(int i=row_count-1; i>-1; i--){


        for(int c=i; c<variable_count; c++){
            if(!m_matrix[i][c].isNull()){
                offset=c;
                break;
            }
        }

        for(int j=i-1; j>-1; j--){
            if(m_matrix[j][offset].isNull()){
                continue;
            }
            subtractRow(multiplyRow(m_matrix[i],m_matrix[j][offset]),j);
        }
    }

    freeVar = getFreeVar();


    for(int i=0; i<m_matrix.length(); i++){
        QString row = "";
        for(int j=0; j<m_matrix[0].length(); j++){
            row+=m_matrix[i][j].reduce().toString() + " ";
        }
        qDebug()<<row;
    }
}

QVector<Fraction> SimSolver::getSolutionSet(QVector<Fraction> freeVariable_values)
{

    QVector<Fraction> answers;
    for(int i=0; i<variable_count; i++){
        answers.append(Fraction(0,1));
    }

    for(int i=0; i<freeVar.length(); i++){
        answers[freeVar[i]] = freeVariable_values[i];
    }

    for(int i=row_count-1; i>-1; i--){
        int pivot = getPivot(m_matrix[i]);
        for(int j=pivot+1; j<variable_count; j++){
            if(!answers[j].isNull() && !m_matrix[i][j].isNull()){
                answers[pivot] = answers[pivot].subtract(answers[j].multiply(m_matrix[i][j]));
            }

        }

    }
    return answers;


}

QVector<Fraction> SimSolver::findSmallestIntegerSolution()
{
    QVector<Fraction> freeVariable_values;
    for(int i=0; i<freeVar.length(); i++){
        QVector<int> denominators;
        for(int j=0; j<m_matrix.length(); j++){
            qDebug()<<m_matrix[j][freeVar[i]].toString();
            m_matrix[j][freeVar[i]] = m_matrix[j][freeVar[i]].reduce();

            if(!m_matrix[j][freeVar[i]].isNull()){
                denominators.append(m_matrix[j][freeVar[i]].bot());
            }
        }
        freeVariable_values.append(Fraction(LCM(denominators)));


    }
    for(int i=0; i<freeVariable_values.length(); i++){
        qDebug()<<freeVariable_values[i].toString();
    }
    return getSolutionSet(freeVariable_values);
}
