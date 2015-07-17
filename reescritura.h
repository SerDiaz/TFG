#ifndef WRITING_H
#define WRITING_H

#include <QWidget>
#include "convertirhora.h"


class Reescritura : public QWidget, public ConvertirHora
{
public:
    Reescritura(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, QString *avLista, QStringList avRutSeg, int *avOp, float *ret, int taAr, QWidget *parent = 0);
    void rewriting();
private:
    //TODOS LOS DATOS RECOGIDOS ANTERIORMENTE PARA ESCRIBIR UN ARCHIVO
    QString fecha;
    QString *nomVuelo;
    QString *origen;
    QString *destino;
    float *hInicio;
    float *hFin;
    QString *piloto;
    QString *avion;

    int numeroAviones;
    int numeroPilotos;
    int tam;
    int tamArchivo;


    //DATOS CAMBIADOS
    int *avionOperacion;
    QStringList avionesRutaSeguida;
    QString *avionesLista;
    float *retraso;
    int tamCambiado;
    QString *nomVueloCambiado;
    QString *origenCambiado;
    QString *destinoCambiado;
    float *hInicioCambiado;
    float *hFinCambiado;
    int *posicionCambioDia;
    int *posicionCambioGeneral;
    int *operacionCambioDia;

    int pilotoCambiado;
    int avionCambiado;

//    DATOS LEIDOS
    QString aux;
    QString *date;
    QString *nombre;
    QString *nomA;
    QString *nomB;
    QString *horarioInicio;
    QString *horarioFin;


    int busquedaPosicion(QString vuelo);
    void actionRewritting();
    void readingGeneral();
    int busquedaPosicionGeneral(QString vuelo, QString fecha);

    int busquedaPiloto(QString vuelo);
    int busquedaAvion(QString vuelo);
    void borrarVueloAvion(QString vuelo, int avion);
    void borrarVueloPiloto(QString vuelo, int piloto);
    void insertarVueloAvion(QString vuelo, int avion);
    void insertarVueloPiloto(QString vuelo, int piloto);
};

#endif // WRITING_H
