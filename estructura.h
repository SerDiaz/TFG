#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H


#include <QWidget>
#include <QGridLayout>
#include "myrectangle.h"
#include <QtCore>
#include <QtGui>
//#include <window.h>


class QDataWidgetMapper;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QGroupBox;
class QStandardItemModel;
class QTextEdit;
class Myrectangle;


class Estructura : public QWidget
{

public:
    Estructura(QWidget *p = 0);
    void asignar(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi);
    void crear(QVBoxLayout *boxlayout);
    void horarios();
    void aviones();
    void vuelos();
    void pintarVuelos();
    void borrarWidget();
    void mostrarWidget();

    QString getFecha();
    int getTamano();
    void herencia();

private:
    QHBoxLayout *horasLayout;
    QGridLayout *avionesLayout;
    QVBoxLayout *vuelosHoraLayout;
    QString fecha;
    QString *nomVuelo;
    QString *origen;
    QString *destino;
    float *hInicio;
    float *hFin;
    QString *piloto;
    QString *avion;
    QLabel *label;
    QLabel *nameLabel;
    int numeroHoras = 33;
    QLabel *hora[33];

    int numeroAviones;
    int numeroPilotos;
    int tam;

    float convertirHora(QString *hora);
    int vueloCercano(QString vuelo, QString *nombre, float hora1,float horas[]);
    int buscarPosicion(int lista, QString *nombreSiguiente);
    int *listaPilotos();
    bool ultimo(int i);


    Myrectangle *myrectangle;
    QGraphicsView *view;
    QGraphicsScene *scene;

};

#endif // ESTRUCTURA_H

