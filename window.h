#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>
#include <QItemSelection>
#include <QLineEdit>
#include <QPushButton>
#include <Qtcore>
#include <QtGui>
#include <QGraphicsScene>
#include "estructura.h"
#include "reorden.h"
#include "rectangulo.h"
#include "convertirhora.h"


class Rectangulo;
class Estructura;
class Reorden;
class Middle;


class Window : public QWidget, public ConvertirHora
{
    Q_OBJECT


public:
    Window(QWidget *parent = 0);
    void cargarDatos();
    void guardarDatos(QString nombreArchivo);
    void setDatos(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr,Estructura *est);



public slots:
    void borrarEstructura();
    void crearEstructura();
    void reordenarEstructura(QString nombreVuelo, float retraso);


private:

    QVBoxLayout *mainLayout;
    QVBoxLayout *estructraLayout;
    QHBoxLayout *opcionesLayout;

    QPushButton *aceptar;
    QPushButton *borrar;
    QPushButton *crear;
    QPushButton *probatura;



    QString fecha;
    QString *piloto;
    QString *avion;
    QString *nomA;
    QString *nomB;
    float *horarioInicio;
    float *horarioFin;
    QString *nombre;
    int numVuelos;
    int nAviones;
    int nPilotos;

    int tamArchivo;


    Estructura *estructura;
    Reorden *reorden;

//    ************
//    ************
//    ************


    void createMenus();

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *exitAction;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
    bool crearPress;

    QLineEdit *retrasoEdit;
    QLineEdit *avionEdit;
    QString fileOpened;



    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
private slots:
    void openFile();
    void saveFile();




};

#endif // WINDOW_H
