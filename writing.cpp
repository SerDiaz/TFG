#include "writing.h"

#include <QtWidgets>
#include <stdio.h>
#include <iostream>

Writing::Writing(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi,QString *avLista, QStringList avRutSeg, int *avOp, float *ret, int taAr, QWidget *parent)
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

void Writing::rewriting(){
    readingGeneral();
    std::cout << "Rewritting, size: " << avionesRutaSeguida.size() << std::endl;

    tamCambiado=avionesRutaSeguida.size();
    std::cout << "tamCambiado: " << tamCambiado << std::endl;

    int auxInt;
    if(tamCambiado!=0){
        auxInt=avionesRutaSeguida.at(tamCambiado-1).toLocal8Bit().toInt();
    }
    std::cout << "aux: " << auxInt << std::endl;
    std::cout << "Aviones Lista: " << avionesLista[auxInt].toStdString() << std::endl;


//    SI ES SOLO RETRASAR AVION LA ULTIMA LÍNEA NO HARÁ FALTA
    if(avionOperacion[auxInt]==10)
        tamCambiado--;

    std::cout << "tamCambiado2: " << tamCambiado << ", " <<
                 avionOperacion[auxInt] << std::endl;

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

          std::cout << "fecha: " << fecha.toStdString() << std::endl;
          std::cout << "posicionCambioGeneral[z]: " << posicionCambioGeneral[z] << std::endl;

          std::cout << "avionOperacion[posicion]" << avionesLista[posicion].toStdString() << std::endl;
          std::cout << "avionOperacion[posicion]" << avionOperacion[posicion] << std::endl;

//                 std::cout << avionesRutaSeguida[listaCerrada[i]].at(j).toLocal8Bit().constData() << std::endl;

          switch (avionOperacion[posicion]) {
              case 0:{
                std::cout << "*********WRITING 0********************"<< std::endl;
                std::cout << posicion << ". avion '" << avionesLista[posicion].toStdString()
                        << "', Hora Inicio de este avion '" << hInicio[posicionDia]
                           << "' y operacion '" << avionOperacion[posicion] << "'" << std::endl;
                hInicio[posicionDia]=hInicio[posicionDia]+retraso[posicion];
                hFin[posicionDia]=hFin[posicionDia]+retraso[posicion];
                std::cout << posicion << ". avion  '" << avionesLista[posicion].toStdString()
                          << "', Hora Inicio de este avion '" << hInicio[posicionDia]
                             << "' y operacion '" << avionOperacion[posicion] << "'" << std::endl;
              }break;
              case 1:{
                std::cout << "*********WRITING 1********************"<< std::endl;
                pilotoCambiado=busquedaPiloto(avionesLista[posicion]);
                borrarVueloPiloto(avionesLista[posicion],pilotoCambiado);
                avionCambiado=busquedaAvion(avionesLista[posicion]);
                borrarVueloAvion(avionesLista[posicion],avionCambiado);
              }break;
              case 2:{
                std::cout << "*********WRITING 2********************"<< std::endl;
                pilotoCambiado=busquedaPiloto(avionesLista[posicion]);
                borrarVueloPiloto(avionesLista[posicion],pilotoCambiado);
              }break;

              case 3:{
                std::cout << "*********WRITING 3********************"<< std::endl;
                avionCambiado=busquedaAvion(avionesLista[posicion]);
                borrarVueloAvion(avionesLista[posicion],avionCambiado);
              }break;
              case 4:{
                std::cout << "*********WRITING 4********************"<< std::endl;

                pilotoCambiado=busquedaPiloto(avionesLista[posicion]);
                borrarVueloPiloto(avionesLista[posicion],pilotoCambiado);
                avionCambiado=busquedaAvion(avionesLista[posicion]);
                borrarVueloAvion(avionesLista[posicion],avionCambiado);
                nomVuelo[posicionDia]="empty";

              }break;
              case 11:{
                std::cout <<"*********WRITING 11********************"<< std::endl;
                int pi=busquedaPiloto(avionesLista[posicion]);
                insertarVueloPiloto(avionesLista[posicionAnterior],pi);
                int av=busquedaAvion(avionesLista[posicion]);
                insertarVueloAvion(avionesLista[posicionAnterior],av);

              }break;
              case 12:{
                std::cout <<"*********WRITING 12********************"<< std::endl;
                int pi=busquedaPiloto(avionesLista[posicion]);
                insertarVueloPiloto(avionesLista[posicionAnterior],pi);
              }break;
              case 13:{
                std::cout <<"*********WRITING 13********************"<< std::endl;
                int av=busquedaAvion(avionesLista[posicion]);
                insertarVueloAvion(avionesLista[posicionAnterior],av);
              }break;
          }
          posicionAnterior=posicion;
    }
    std::cout << "AHORA A GUARDAR" << std::endl;
    actionRewritting();
    rewrittingPilotoAvion();

}

int Writing::busquedaPosicion(QString vuelo){
    for(int i = 0;i<tam;i++){
        if(nomVuelo[i]==vuelo)
            return i;
    }
    return -1;
}



void Writing::actionRewritting(){
    std::cout << "VAMOS A GUARDAR" << std::endl;
    QFile file_for_writing("vuelosAbrilModificado.txt");
    file_for_writing.open(QIODevice::WriteOnly | QIODevice::Truncate); //
    QTextStream text_stream_for_writing(&file_for_writing);

    std::cout << "actionRewritting******************" << std::endl;
    std::cout << "tamArchivo: " << tamArchivo << std::endl;




//        TODAS LAS POSICIONES QUE REQUIERAN ACTUALIZAR SUS DATOS SON LAS GUARDADAS EN POSICION CAMBIO
        for(int i=0; i < tamCambiado; i++){
            if(operacionCambioDia[i]==0){
                std::cout << "i: " << i << std::endl;
                std::cout << "posicionCambioDia: " << posicionCambioDia[i] << std::endl;
                std::cout << "posicionCambioGeneral: " << posicionCambioGeneral[i] << std::endl;


                std::cout << "nomVuelo[posicionCambioDia[i]]: " << nomVuelo[posicionCambioDia[i]].toStdString() << std::endl;
                std::cout << "nombre[posicionCambioGeneral[i]]: " << nombre[posicionCambioGeneral[i]].toStdString() << std::endl;

                std::cout << "horarioInicio[posicionCambioGeneral[i]]: " << horarioInicio[posicionCambioGeneral[i]].toStdString() << std::endl;
                std::cout << "horarioFin[posicionCambioGeneral[i]]: " << horarioFin[posicionCambioGeneral[i]].toStdString() << std::endl;
                std::cout << "hInicio[posicionCambioDia[i]]: " << hInicio[posicionCambioDia[i]] << std::endl;
                std::cout << "hFin[posicionCambioDia[i]]: " << hFin[posicionCambioDia[i]] << std::endl;

                nombre[posicionCambioGeneral[i]]=nomVuelo[posicionCambioDia[i]];
                horarioInicio[posicionCambioGeneral[i]]=aString(hInicio[posicionCambioDia[i]]);;
                horarioFin[posicionCambioGeneral[i]]=aString(hFin[posicionCambioDia[i]]);

                std::cout << "horarioInicio[posicionCambioGeneral[i]]: " << horarioInicio[posicionCambioGeneral[i]].toStdString() << std::endl;
                std::cout << "horarioFin[posicionCambioGeneral[i]]: " << horarioFin[posicionCambioGeneral[i]].toStdString() << std::endl;

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

void Writing::rewrittingPilotoAvion(){
    QString dia = fecha.split("/")[0];

    QString archivoLee= "salida" + dia+ "_04_2012.txt";
    QString archivo= "salida" + dia+ "_04_2012_Modificado.txt";


    QString aux;
    QFile file_for_PilotoAvion(archivoLee);
    file_for_PilotoAvion.open(QIODevice::ReadOnly);
    QTextStream PilotoAvion(&file_for_PilotoAvion);
        PilotoAvion >> aux;
        PilotoAvion >> aux;
    file_for_PilotoAvion.close();

    std::cout << "GUARDAR ACHIVO ESPECIFICO DIA:" << archivo.toStdString() << std::endl;
    QFile file_for_writing(archivo);
    file_for_writing.open(QIODevice::WriteOnly | QIODevice::Truncate); //
    QTextStream text_stream_for_writing(&file_for_writing);


            QString espacio = tr(" ");
            QString salto = tr("\r\n");

            text_stream_for_writing << fecha;
            text_stream_for_writing << salto;
            text_stream_for_writing << aux;
            text_stream_for_writing << salto;
            text_stream_for_writing << "0";
            text_stream_for_writing << salto;


            int i=0;
            while (i<numeroAviones){
                text_stream_for_writing << avion[i];
                text_stream_for_writing << salto;
                i++;

            }

            text_stream_for_writing << espacio;
            text_stream_for_writing << salto;
            text_stream_for_writing << "---";


            i=0;
            while (i<numeroPilotos){
                text_stream_for_writing << salto;
                text_stream_for_writing << piloto[i];
                i++;
            }



    file_for_writing.close();


}


void Writing::readingGeneral(){
        QString aux;

        //Lectura
        QFile file_for_readingGeneral("vuelosabril12.txt");
        file_for_readingGeneral.open(QIODevice::ReadOnly);
        QTextStream text_stream_for_readingGeneral(&file_for_readingGeneral);

        std::cout << "readingGeneral*********" << std::endl;
        std::cout << "tamArchivo: " << tamArchivo << std::endl;

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



int Writing::busquedaAvion(QString vuelo){
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

int Writing::busquedaPiloto(QString vuelo){
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

void Writing::borrarVueloAvion(QString vuelo, int av){
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

void Writing::borrarVueloPiloto(QString vuelo, int pi){
    std::cout <<  "piloto[pi] INICIO " << piloto[pi].toStdString() << std::endl;
    std::cout <<  "vuelo a borrar" <<  vuelo.toStdString() << std::endl;


    QStringList list = piloto[pi].split(";",QString::SkipEmptyParts);
    QString *lista = new QString[list.size()];
    QString pilotoNew = "";

    for(int k=0;k<list.size();k++){
        lista[k]=tr(list.at(k).toLocal8Bit().constData());

        if(lista[k]!=vuelo){
            pilotoNew = pilotoNew + lista[k] + ";" ;
            std::cout <<   "lista[k] " << lista[k].toStdString() << std::endl;
            std::cout <<   "PILOTO. DENTRO DEL FOR " << pilotoNew.toStdString() << std::endl;
        }
    }
    piloto[pi]=pilotoNew;
    std::cout << "piloto[pi] FINAL "<< piloto[pi].toStdString() << std::endl;

}

void Writing::insertarVueloAvion(QString vuelo, int av){
    std::cout << "INSERTAR VUELO AVION " << std::endl;
    std::cout << "av " << av << std::endl;
    std::cout << "vuelo " << vuelo.toStdString() << std::endl;

    std::cout << "avion[av] " << avion[av].toStdString() << std::endl;


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

        std::cout << "vuelo del bucle " << nomVuelo[posListaActual].toStdString() <<std::endl;
        std::cout << "hInicio[posListaActual] " << hInicio[posListaActual] <<std::endl;
        std::cout << "hInicio[posVuelo] " << hInicio[posVuelo] <<std::endl;
        std::cout << "vuelo de posListaSiguiente " << nomVuelo[posListaSiguiente].toStdString() <<std::endl;
        std::cout << "hInicio[posListaSiguiente] " << hInicio[posListaSiguiente] <<std::endl;

        if(hInicio[posVuelo]<hInicio[posListaActual] && avionNew=="")
            avionNew = vuelo + ";";

        avionNew = avionNew + lista[k] + ";";

        if(hInicio[posVuelo]>hInicio[posListaActual] && hInicio[posVuelo]<hInicio[posListaSiguiente]){
            avionNew = avionNew + vuelo + ";";
            std::cout << "ENTRO y CAMBIO" <<std::endl;
        }
    }
    avion[av]=avionNew;
    std::cout << "avion[av] FINAL "<< avion[av].toStdString() << std::endl;

}

void Writing::insertarVueloPiloto(QString vuelo, int pi){
    std::cout << "INSERTAR PILOTO AVION " << std::endl;
    std::cout << "piloto[pi] " << piloto[pi].toStdString()<<std::endl;


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

        std::cout << "vuelo del bucle " << nomVuelo[posListaActual].toStdString() <<std::endl;
        std::cout << "hInicio[posListaActual] " << hInicio[posListaActual] <<std::endl;
        std::cout << "hInicio[posVuelo] " << hInicio[posVuelo] <<std::endl;
        std::cout << "vuelo de posListaSiguiente " << nomVuelo[posListaSiguiente].toStdString() <<std::endl;
        std::cout << "hInicio[posListaSiguiente] " << hInicio[posListaSiguiente] <<std::endl;

        if(hInicio[posVuelo]<hInicio[posListaActual] && pilotoNew=="")
            pilotoNew = vuelo + ";";

        pilotoNew = pilotoNew + lista[k] + ";";

        if(hInicio[posVuelo]>hInicio[posListaActual] && hInicio[posVuelo]<hInicio[posListaSiguiente]){
            pilotoNew = pilotoNew + vuelo + ";";
            std::cout << "ENTRO y CAMBIO" <<std::endl;
        }
    }
    piloto[pi]=pilotoNew;
    std::cout << "piloto[pi] FINAL "<< piloto[pi].toStdString() << std::endl;

}

int Writing::busquedaPosicionGeneral(QString vuelo, QString fecha){
    std::cout << "busquedaPosicionGeneral******************"<< std::endl;
    std::cout << "vuelo: "<< vuelo.toStdString() << std::endl;
    std::cout << "fecha: "<< fecha.toStdString() << std::endl;
    std::cout << "tamArchivo: "<< tamArchivo << std::endl;


//    std::cout << "nombre[3]: "<< nombre[3].toStdString() << std::endl;
//    std::cout << "date[3]: "<< date[3].toStdString() << std::endl;



    for (int i=0; i<tamArchivo;i++){

        if(date[i]==fecha && nombre[i]==vuelo)
            return i;

    }
    return -1;

}


