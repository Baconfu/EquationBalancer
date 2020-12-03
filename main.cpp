#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVector>

#include <simsolver.h>
#include <fraction.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //QVector<int> matrix_1D = {2,0,0,-1,0,0,7,1,0,0,-1,-1,0,3,0,0,-3,0,0,8,1,0,-6,-2,2,0,-1,3,0,0};

    QVector<int> matrix_1D = {1,0,-1,0,0,1,0,0,0,-1,3,0,0,-1,-2,0,1,0,-2,0,0,1,-2,0,0};
    int row = 5;
    int column = 5;

    QVector<QVector<Fraction>> input;

    for(int i=0; i<row; i++){
        input.append(QVector<Fraction>());
        for(int j=0; j<column; j++){
            input[i].append(Fraction(matrix_1D[i * column + j]));
        }
    }

    SimSolver * solver = new SimSolver(input);

    solver->toEchelon();

    QVector<Fraction> answers = solver->findSmallestIntegerSolution();
    QString disp = "";
    for(int i=0; i<answers.length(); i++){
        disp = disp + answers[i].toString() + " ";

    }
    qDebug()<<disp;





    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
