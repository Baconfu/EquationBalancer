#ifndef SPECIES_H
#define SPECIES_H

#include <QString>
#include <QVector>


class Specimen
{
public:
    Specimen(QVector<QString> identifiers,QVector<int> quantities);

    void addElement(QString identifier,int quantity){identifiers.append(identifier);quantities.append(quantity);}

    QString getIdentifier(int id){return identifiers[id];}
    int getQuantity(int id){return quantities[id];}


private:
    QVector<QString> identifiers;
    QVector<int> quantities;
};

#endif // SPECIES_H
