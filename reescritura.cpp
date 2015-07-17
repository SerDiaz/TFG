#include "reescritura.h"

#include <QtWidgets>
#include <stdio.h>
#include <iostream>

Reescritura::Reescritura(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi,QString *avLista, QStringList avRutSeg, int *avOp, float *ret, int taAr, QWidget *parent)
    : QWidget(parent)
{


    tam = ta;
    numeroAviones=nav;
    numeroPilotos=npi;
    fecha=fe;
    avion = avi;
    nomVuelo=noV;
    origen=ori;
    destino=des;
    hInicio=ini;
    hFin=fin;
    piloto=pi;

    avionesLista=avLista;
    avionesRutaSeguida=avRutSeg;
    retraso=ret;
    avionOperacion=avOp;

    tamArchivo=taAr;

    date=new QString[tamArchivo];
    nombre=new QString[tamArchivo];
    nomA=new QString[tamArchivo];
    nomB=new QString[tamArchivo];
    horarioInicio=new QString[tamArchivo];
    horarioFin=new QString[tamArchivo];

    aux = tr("ATN");


}

void Reescritura::rewriting(){
    readingGeneral();
    tamCambiado=avionesRutaSeguida.size();
    int auxInt;
    if(tamCambiado!=0){
        auxInt=avionesRutaSeguida.at(tamCambiado-1).toLocal8Bit().toInt();
    }

//    SI ES SOLO RETRASAR AVION LA ULTIMA LÍNEA NO HARÁ FALTA
    if(avionOperacion[auxInt]==10)
        tamCambiado--;


    posicionCambioDia=new int[tamCambiado];
    posicionCambioGeneral=new int[tamCambiado];
    operacionCambioDia=new int[tamCambiado];

    int z=0;

    int posicionAnterior=0;
    int posicion=0;


    for (int j = 0; j < tamCambiado; ++j){
          posicion = avionesRutaSeguida.at(j).toLocal8Bit().toInt();


          int posicionDia = busquedaPosicion(avionesLista[posicion]);
          posicionCambioDia[z]=posicionDia;
          posicionCambioGeneral[z]=busquedaPosicionGeneral(avionesLista[posicion],fecha);
          operacionCambioDia[z]=avionOperacion[posicion];

          z++;

          switch (avionOperacion[posicion]) {
              case 0:{
                hInicio[posicionDia]=hInicio[posicionDia]+retraso[posicion];
                hFin[posicionDia]=hFin[posicionDia]+retraso[posicion];
              }break;
              case 1:{
                pilotoCambiado=busquedaPiloto(avionesLista[posicion]);
                borrarVueloPiloto(avionesLista[posicion],pilotoCambiado);
                avionCambiado=busquedaAvion(avionesLista[posicion]);
                borrarVueloAvion(avionesLista[posicion],avionCambiado);
              }break;
              case 2:{
                pilotoCambiado=busquedaPiloto(avionesLista[posicion]);
                borrarVueloPiloto(avionesLista[posicion],pilotoCambiado);
              }break;

              case 3:{
                avionCambiado=busquedaAvion(avionesLista[posicion]);
                borrarVueloAvion(avionesLista[posicion],avionCambiado);
              }break;
              case 4:{
                pilotoCambiado=busquedaPiloto(avionesLista[posicion]);
                borrarVueloPiloto(avionesLista[posicion],pilotoCambiado);
                avionCambiado=busquedaAvion(avionesLista[posicion]);
                borrarVueloAvion(avionesLista[posicion],avionCambiado);
                nomVuelo[posicionDia]="empty";

              }break;
              case 11:{
                int pi=busquedaPiloto(avionesLista[posicion]);
                insertarVueloPiloto(avionesLista[posicionAnterior],pi);
                int av=busquedaAvion(avionesLista[posicion]);
                insertarVueloAvion(avionesLista[posicionAnterior],av);

              }break;
              case 12:{
                int pi=busquedaPiloto(avionesLista[posicion]);
                insertarVueloPiloto(avionesLista[posicionAnterior],pi);
              }break;
              case 13:{
                int av=busquedaAvion(avionesLista[posicion]);
                insertarVueloAvion(avionesLista[posicionAnterior],av);
              }break;

              //EN LOS DEMÁS CASOS QUE ENCUENTRE NO HACE NADA
          }
          posicionAnterior=posicion;
    }
    actionRewritting();

}

int Reescritura::busquedaPosicion(QString vuelo){
    for(int i = 0;i<tam;i++){
        if(nomVuelo[i]==vuelo)
            return i;
    }
    return -1;
}



void Reescritura::actionRewritting(){
    QFile file_for_writing("vuelosAbrilModificado.txt");
    file_for_writing.open(QIODevice::WriteOnly | QIODevice::Truncate); //
    QTextStream text_stream_for_writing(&file_for_writing);


//        TODAS LAS POSICIONES QUE REQUIERAN ACTUALIZAR SUS DATOS SON LAS GUARDADAS EN POSICION CAMBIO
    for(int i=0; i < tamCambiado; i++){
        if(operacionCambioDia[i]==0){
            nombre[posicionCambioGeneral[i]]=nomVuelo[posicionCambioDia[i]];
            horarioInicio[posicionCambioGeneral[i]]=aString(hInicio[posicionCambioDia[i]]);;
            horarioFin[posicionCambioGeneral[i]]=aString(hFin[posicionCambioDia[i]]);
        }
    }

        QString espacio = tr(" ");
        QString salto = tr("\r\n");



//        ESCRIBIMOS NUEVO ARCHIVO
        for(int i = 0; i < tamArchivo; i++){
            if(nombre[i]!="empty"){ /*SI SE HA CANCELADO EL VUELO ES EMPTY*/
                text_stream_for_writing << date[i];
                text_stream_for_writing << espacio;
                text_stream_for_writing << aux;
                text_stream_for_writing << espacio;
                text_stream_for_writing << nombre[i];
                text_stream_for_writing << espacio;
                text_stream_for_writing << nomA[i];
                text_stream_for_writing << espacio;
                text_stream_for_writing << nomB[i];
                text_stream_for_writing << espacio;
                text_stream_for_writing << horarioInicio[i];
                text_stream_for_writing << espacio;
                text_stream_for_writing << horarioFin[i];
                text_stream_for_writing << salto;
            }
        }


    file_for_writing.close();




}


void Reescritura::readingGeneral(){
        QString aux;

        //Lectura
        QFile file_for_readingGeneral("vuelosabril12.txt");
        file_for_readingGeneral.open(QIODevice::ReadOnly);
        QTextStream text_stream_for_readingGeneral(&file_for_readingGeneral);

        date=new QString[tamArchivo];
        nombre=new QString[tamArchivo];
        nomA=new QString[tamArchivo];
        nomB=new QString[tamArchivo];
        horarioInicio=new QString[tamArchivo];
        horarioFin=new QString[tamArchivo];



        for(int i = 0; i < tamArchivo; i++){
            text_stream_for_readingGeneral >> date[i];
            text_stream_for_readingGeneral >> aux;
            text_stream_for_readingGeneral >> nombre[i];
            text_stream_for_readingGeneral >> nomA[i];
            text_stream_for_readingGeneral >> nomB[i];
            text_stream_for_readingGeneral >> horarioInicio[i];
            text_stream_for_readingGeneral >> horarioFin[i];
        }

        file_for_readingGeneral.close();

}



int Reescritura::busquedaAvion(QString vuelo){
    for(int j = 0;j<numeroAviones;j++){
        QStringList list = avion[j].split(";",QString::SkipEmptyParts);
        QString *lista = new QString[list.size()];

        for(int k=0;k<list.size();k++){
            lista[k]=tr(list.at(k).toLocal8Bit().constData());
            if(lista[k]==vuelo)
              return j;
        }
    }
    return -1;
}

int Reescritura::busquedaPiloto(QString vuelo){
    for(int j = 0;j<numeroPilotos;j++){
        QStringList list = piloto[j].split(";",QString::SkipEmptyParts);
        QString *lista = new QString[list.size()];

        for(int k=0;k<list.size();k++){
            lista[k]=tr(list.at(k).toLocal8Bit().constData());
            if(lista[k]==vuelo)
                return j;
        }
    }
    return -1;

}

void Reescritura::borrarVueloAvion(QString vuelo, int av){
    QStringList list = avion[av].split(";",QString::SkipEmptyParts);
    QString *lista = new QString[list.size()];
    QString avionNew = "";

    for(int k=0;k<list.size();k++){
        lista[k]=tr(list.at(k).toLocal8Bit().constData());
        if(lista[k]!=vuelo)
            avionNew = avionNew + lista[k] + ";";
    }
    avion[av]=avionNew;
}

void Reescritura::borrarVueloPiloto(QString vuelo, int pi){

    QStringList list = piloto[pi].split(";",QString::SkipEmptyParts);
    QString *lista = new QString[list.size()];
    QString pilotoNew = "";

    for(int k=0;k<list.size();k++){
        lista[k]=tr(list.at(k).toLocal8Bit().constData());

        if(lista[k]!=vuelo){
            pilotoNew = pilotoNew + lista[k] + ";" ;

        }
    }
    piloto[pi]=pilotoNew;
}

void Reescritura::insertarVueloAvion(QString vuelo, int av){
    QStringList list = avion[av].split(";",QString::SkipEmptyParts);
    QString *lista = new QString[list.size()];
    QString avionNew=(tr(list.at(0).toLocal8Bit().constData()))+";";

    int posVuelo=busquedaPosicion(vuelo);
    int posListaActual=0;
    int posListaSiguiente=busquedaPosicion(tr(list.at(1).toLocal8Bit().constData()));


    for(int k=1;k<list.size();k++){
        lista[k]=tr(list.at(k).toLocal8Bit().constData());
        posListaActual=posListaSiguiente;
        if((list.size()-1)>k){
            posListaSiguiente=busquedaPosicion(list.at(k+1).toLocal8Bit().constData());
        }else{
            posListaSiguiente=tam-2;
        }

        if(hInicio[posVuelo]<hInicio[posListaActual] && avionNew=="")
            avionNew = vuelo + ";";

        avionNew = avionNew + lista[k] + ";";

        if(hInicio[posVuelo]>hInicio[posListaActual] && hInicio[posVuelo]<hInicio[posListaSiguiente]){
            avionNew = avionNew + vuelo + ";";
        }
    }
    avion[av]=avionNew;

}

void Reescritura::insertarVueloPiloto(QString vuelo, int pi){

    QStringList list = piloto[pi].split(";",QString::SkipEmptyParts);
    QString *lista = new QString[list.size()];
    QString pilotoNew="";

    int posVuelo=busquedaPosicion(vuelo);
    int posListaActual=0;
    int posListaSiguiente=busquedaPosicion(tr(list.at(0).toLocal8Bit().constData()));

    for(int k=0;k<list.size();k++){
        lista[k]=tr(list.at(k).toLocal8Bit().constData());
        posListaActual=posListaSiguiente;
        if((list.size()-1)>k){
            posListaSiguiente=busquedaPosicion(list.at(k+1).toLocal8Bit().constData());
        }else{
            posListaSiguiente=tam-2;
        }

        if(hInicio[posVuelo]<hInicio[posListaActual] && pilotoNew=="")
            pilotoNew = vuelo + ";";

        pilotoNew = pilotoNew + lista[k] + ";";

        if(hInicio[posVuelo]>hInicio[posListaActual] && hInicio[posVuelo]<hInicio[posListaSiguiente]){
            pilotoNew = pilotoNew + vuelo + ";";
        }
    }
    piloto[pi]=pilotoNew;

}

int Reescritura::busquedaPosicionGeneral(QString vuelo, QString fecha){
    for (int i=0; i<tamArchivo;i++){

        if(date[i]==fecha && nombre[i]==vuelo)
            return i;
    }

    return -1;
}


