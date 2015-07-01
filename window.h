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
//#include "reorden.h"

class Estructura;
class Reorden;


class Window : public QWidget
{
    Q_OBJECT


public:
    Window(QWidget *parent = 0);
    void cargarDatos();
    float convertirHora(QString *hora);
    void herencia();

public slots:
    void probar();
    void hola();
    void mostrarEstructura();
    void borrarEstructura();
    void hola(int i);
    void crearEstructura();

private:

    QVBoxLayout *outerLayout;
    QVBoxLayout *estructraLayout;
    QHBoxLayout *retrasoLayout;

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

    QLineEdit *retrasoEdit;
    QLineEdit *avionEdit;
    QString fileOpened;


    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();




};

#endif // WINDOW_H
