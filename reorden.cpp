#include "reorden.h"

#include <QtWidgets>
#include <stdio.h>
#include <iostream>


//8200 comprobar caso(antes del grande)
// CUANDO AFECTA A LA VEZ AL VUELO DEL AVIÓN SIGUIENTE Y AL VUELO DEL PILOTO SIGUIENTE Y AMBOS SON DISTINTOS PETA
Reorden::Reorden(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr, QWidget *parent)
    : QWidget(parent)
{
    tam = ta;
    tamArchivo=taAr;

    listaAbierta=new int[tam*3+1];
    listaCerrada=new int[tam*3+1];
    costF= new float [tam*3+1];
    costF[1]=0;
    vuelosLista=new QString[(tam*3+1)];
    vuelosRutaSeguida=new QStringList[(tam*3+1)];
    tipoOperacion=new int [6];
    vueloOperacion=new int [tam*3+1];
    listaDondeEsta=new int [tam*3+1];
    retrasoIndividual=new float [tam*3+1];
    dosReordenamientos=new bool[tam*3+1];
    dosReordenamientosElementoForaneo=new unsigned[tam*3+1];
    dosReordenamientosPrimerElemento=new unsigned[tam*3+1];

    caminosComprobados=0;
    numeroDeElementosEnListaAbierta=0;
    numeroDeElementosEnListaCerrada=0;

//    costeRetraso ESTE VA A SER VARIABLE. EL COSTE PARA EL RETRASO DE 1 HORA ES 6
    tipoOperacion[0]=6;
//    costeCAvion+CPioloto SIEMPRE VA A SER EL MISMO
    tipoOperacion[1]=17;
//    costeCPiloto SIEMPRE VA A SER EL MISMO
    tipoOperacion[2]=2;
//    costeCAvion SIEMPRE VA A SER EL MISMO
    tipoOperacion[3]=15;

//    costeCancelar
    tipoOperacion[4]=100;
//    costeImposible
    tipoOperacion[5]=1000000000;
//    óptimo caso 0
    tipoOperacion[10]=0;
//    óptimo caso 1
    tipoOperacion[11]=0;
//    óptimo caso 2
    tipoOperacion[12]=0;
//    óptimo caso 3
    tipoOperacion[13]=0;
//    óptimo caso 4
    tipoOperacion[14]=0;




    nomVuelo=new QString;
    origen=new QString;
    destino=new QString;
    hInicio=new float;
    hFin=new float;
    piloto=new QString;
    avion=new QString;


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
}


void Reorden::algoritmo(QString vuelo, float ret){

    retraso = ret;

    float finVueloActual=hFin[busquedaPosicion((vuelo))];
    float inicioAvionSiguiente=1000;
    float inicioPilotoSiguiente=1000;
    QString vueloPilotoSiguiente=busquedaVueloPilotoSiguiente(vuelo);
    QString vueloAvionSiguiente=busquedaVueloAvionSiguiente(vuelo);


    if(vueloPilotoSiguiente!="empty")
        inicioPilotoSiguiente=hInicio[busquedaPosicion(vueloPilotoSiguiente)];
    if(vueloAvionSiguiente!="empty")
        inicioAvionSiguiente=hInicio[busquedaPosicion(vueloAvionSiguiente)];

//    GUARDO EL PRIMER VUELO EN LA RUTA QUE SIGUE HE INDICO QUE SU ACCIÓN SIEMPRE VA A SER RETRASAR


//    COMPROBAR SI PASA ALGO POR RETRASAR. PUEDE SER QUE AVION TENGA VUELO O PILOTO TENGA VUELO
    if( inicioAvionSiguiente>finVueloActual+0.5+retraso
            && inicioPilotoSiguiente>finVueloActual+0.5+retraso){
        vuelosLista[0]=vuelo;
        QString s = QString::number(0);
        vuelosRutaSeguida[0] << s;
//        SI EL AEROPUERTO NO HA CERRADO
        if(finVueloActual+retraso<=22.5){
//          NO PASO POR ALGORITMO. RETRASO ESTE Y YA ESTA
            vueloOperacion[0]=0;
        }else{
//          NO PASO POR ALGORITMO. CANCELO ESTE Y YA ESTA"
            vueloOperacion[0]=4;
        }
        retrasoIndividual[0]=retraso;
        writing= new Reescritura(tam,numeroAviones,numeroPilotos,fecha,nomVuelo,origen,destino,piloto,hInicio,hFin,avion,vuelosLista,vuelosRutaSeguida[0],vueloOperacion,retrasoIndividual,tamArchivo);
        writing->rewriting();

    //    SI NO SE PUEDE HACEMOS ALGORITMO
    }else{

        insertarListaAbierta(vuelo,0,-1,-1);
        insertarRutaSeguida(-1);


        QString vueloSiguiente=0;

//        SI EL UNICO QUE NO PUEDE ES EL PILOTO
        if(inicioAvionSiguiente>finVueloActual+0.5+retrasoIndividual[caminosComprobados]
                && inicioPilotoSiguiente<=finVueloActual+0.5+retrasoIndividual[caminosComprobados]){

            vueloSiguiente=busquedaVueloPilotoSiguiente(vuelo);
//          TODOS LOS DEMÁS CASOS
        }else{
            vueloSiguiente =busquedaVueloAvionSiguiente(vuelo);
        }

//          SI PUDIERA IR HACIA SU SIGUIENTE DESTINO INCLUIR EN LA LISTA CANCELAR DESTINO
//        bool puede=sePuedeCancelar(posVuelo,posVueloSiguiente);
//          ¿SE PUDO CANCELAR?:

//        if(puede==1){
            insertarListaAbierta(vuelo,4,-1,-1);
            insertarRutaSeguida(-1);
//        }




    //    EMPEZAMOS CON EL AVION SIGUIENTE AL QUE SE VEA AFECTADO PUES ESTE DIRECTAMENTE SE RETRASA
        algoritmoComun();



//        std::cout << "--------------LISTA CERRADA-------------------" << std::endl;

        for(int i = 1; i <= numeroDeElementosEnListaCerrada; i++){
            int posicionAnterior;
            if(vuelosRutaSeguida[listaCerrada[i]].size()>1){
                posicionAnterior= vuelosRutaSeguida[listaCerrada[i]].at(vuelosRutaSeguida[listaCerrada[i]].size()-2).toLocal8Bit().toInt();
            }else{
                posicionAnterior= vuelosRutaSeguida[listaCerrada[i]].at(vuelosRutaSeguida[listaCerrada[i]].size()-1).toLocal8Bit().toInt();
            }

            if(numeroDeElementosEnListaCerrada==(i)){
//              FIN DEL PROGRAMA. GUARDAR LOS DATOS MEDIANTE CLASE WRITING
                writing= new Reescritura(tam,numeroAviones,numeroPilotos,fecha,nomVuelo,origen,destino,piloto,hInicio,hFin,avion,vuelosLista,vuelosRutaSeguida[listaCerrada[i]],vueloOperacion,retrasoIndividual,tamArchivo);
                writing->rewriting();
            }
        }


//        SE REINICIALIZAN LAS VARIABLES
        delete listaAbierta;
        delete listaCerrada;
        delete costF;
        delete vuelosRutaSeguida;
        delete vuelosLista;
        delete listaDondeEsta;
        delete vueloOperacion;
        delete retrasoIndividual;
        delete dosReordenamientos;
        delete dosReordenamientosElementoForaneo;
        delete dosReordenamientosPrimerElemento;



        vuelosLista=new QString[(tam*3+1)];
        listaAbierta=new int[tam*3+2];
        listaCerrada=new int[tam];
        costF= new float [tam*3+1];
        vueloOperacion=new int [tam*3+1];
        listaDondeEsta=new int [tam*3+1];
        retrasoIndividual=new float [tam*3+1];
        dosReordenamientos=new bool[tam*3+1];
        dosReordenamientosElementoForaneo=new unsigned [tam*3+1];
        dosReordenamientosPrimerElemento=new unsigned [tam*3+1];


        vuelosRutaSeguida=new QStringList[(tam*3+1)];
        caminosComprobados=0;
        costF[1]=0;
        numeroDeElementosEnListaAbierta=0;
        numeroDeElementosEnListaCerrada=0;
        retraso=0;
    }

}

void Reorden::algoritmoComun(){




//    AÑADIMOS A LA LISTA ABIERTA LAS TRES DISTINTAS OPCIONES QUE PUEDE SUCEDER
//    EL TIPO DE OPERACIÓN 5 CORRESPONDE A QUE DA IGUAL EL TIPO DE OPERACION QUE SEA

    while(numeroDeElementosEnListaAbierta!=0){

        int id=borrarListaAbierta(1);
        insertarListaCerrada(id);
        int posicionActual=busquedaPosicion(vuelosLista[id]);

        switch (vueloOperacion[id]) {
            case 0:
                retrasarAviones(posicionActual,id);
              break;
            case 1:
                busquedaPilotoYAvionSustitucion(posicionActual,id);
              break;
            case 2:
                busquedaPilotoSustitucion(posicionActual,id);
              break;
            case 3:
                busquedaAvionSustitucion(posicionActual,id);
              break;
            case 4:
                cancelar(posicionActual,id);
              break;
            case 15:
                 numeroDeElementosEnListaAbierta=0;
                 insertarListaCerrada(id);
              break;

        }
    }
}




void Reorden::retrasarAviones(int posicionActual, int idCaminoPadre){
//    std::cout << "---------EMPIEZA 0--------------" << std::endl;

    QString vuelo=vuelosLista[idCaminoPadre];

    QString vueloAvionSiguiente=busquedaVueloAvionSiguiente(vuelo);
    int posicionSiguienteAvion=-1;
    QString vueloPilotoSiguiente=busquedaVueloPilotoSiguiente(vuelo);
    int posicionSiguientePiloto=-1;
    if(vueloAvionSiguiente!="empty")
       posicionSiguienteAvion = busquedaPosicion(vueloAvionSiguiente);
    if(vueloPilotoSiguiente!="empty")
       posicionSiguientePiloto=busquedaPosicion(vueloPilotoSiguiente);

    if(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5 <= 22.5){

        if(posicionSiguienteAvion!=-1 && posicionSiguientePiloto!=-1){
            if(hInicio[posicionSiguienteAvion]>=(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5)
                    && hInicio[posicionSiguientePiloto]>=(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5)){
                nuevoEnListaCerrada(nomVuelo[posicionSiguienteAvion],nomVuelo[posicionActual],idCaminoPadre);

            }else{
//                SI NO SE PUEDE Y EL PILOTO Y EL AVION VAN A PARTICIPAR EN EL SIGUIENTE VUELO
                if(posicionSiguienteAvion==posicionSiguientePiloto){
//                    std::cout << "*************1º else posicionSiguienteAvion==posicionSiguientePiloto***********" << std::endl;
                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion],-1);
//                    SI AVION Y PILOTO TIENEN DISTINTOS VUELOS (O ALGUNO NO TIENE MÁS) Y PILOTO NO MOLESTA PERO EL AVION CHOCA
                }else if((hInicio[posicionSiguientePiloto]>=(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5)
                          && hInicio[posicionSiguienteAvion]<(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5))){
//                    std::cout << "*************2º else. El avion choca pero piloto no***********" << std::endl;
                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion],-1);
//                    SI AVION Y PILOTO TIENEN DISTINTOS VUELOS (O ALGUNO NO TIENE MÁS) Y AVION NO MOLESTA
                }else if(hInicio[posicionSiguienteAvion]>=(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5)
                          && hInicio[posicionSiguientePiloto]<(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5)){
//                    std::cout << "*************3º else. El piloto choca pero avion no***********" << std::endl;
                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguientePiloto],-1);
                }else if(posicionSiguientePiloto!=posicionSiguienteAvion
                         && hInicio[posicionSiguienteAvion]<(hFin[posicionActual]+retraso+0.5)
                         && hInicio[posicionSiguientePiloto]<(hFin[posicionActual]+retraso+0.5)){
//                    std::cout << "**********VUELO AVION Y PILOTO DISTINTO Y LOS DOS SON AFECTADOS POR EL RETRASO*************" << std::endl;
//                    std::cout << "**********DOS REORDENAMIENTOS*************" << std::endl;
//                    std::cout << "**********PRIMER REORDENAMIENTOS*************" << std::endl;

                    int posListaVueloActual=buscarVuelo(vuelo,0);

                    dosReordenamientos[posListaVueloActual]=1;
                    dosReordenamientosPrimerElemento[posListaVueloActual]=posListaVueloActual;
                    dosReordenamientosElementoForaneo[posListaVueloActual]=posListaVueloActual;

                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguientePiloto],posListaVueloActual);

                    // LO USARÉ PARA COLOCARL EL VERDADERO VUELO FORÁNEO A CONTINUACIÓN
                    int posListaVueloReorden1=caminosComprobados;

//                    std::cout << "**********SEGUNDO REORDENAMIENTOS*************" << std::endl;
                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion],posListaVueloActual);

                    // COLOCANDO VUELOS FORÁNEOS
                    dosReordenamientosElementoForaneo[caminosComprobados]=posListaVueloReorden1;
                    dosReordenamientosElementoForaneo[posListaVueloReorden1]=caminosComprobados;

                    //AL VUELO PRINCIPAL LO DEJO ENLAZADO CON UN VUELO FORANEO PARA COMPROBAR LUEGO
                    dosReordenamientosElementoForaneo[posListaVueloActual]=caminosComprobados;



                }else{
//                    std::cout << "*************VUELO Y PILOTO DISTINTO Y NO PASA NINGUNO. AQUI ME QUEDO NO SIGO ESTE CAMINO***********" << std::endl;
                }
            }
//        SI EL AVIÓN NO TIENE VUELO SIGUIENTE PERO SI EL PILOTO, Y ESTE VUELO NO COLISIONA EN HORARIO CON EL ACTUAL RETRASADO
        }else{
            if(posicionSiguientePiloto==-1 && posicionSiguienteAvion==-1){
                std::cout << "**********AVION Y PILOTO LOS ÚLTIMOS. SE PUEDE RETRASAR*************" << std::endl;
                nuevoEnListaCerrada(nomVuelo[posicionActual],nomVuelo[posicionActual],idCaminoPadre);
            }else if(hInicio[posicionSiguienteAvion]>=(hFin[posicionActual]+retraso+0.5)){

//            std::cout << "**********AVION SE PUEDE RETRASAR*************" << std::endl;
            nuevoEnListaCerrada(nomVuelo[posicionSiguienteAvion],nomVuelo[posicionActual],idCaminoPadre);

            }else if(hInicio[posicionSiguientePiloto]>=(hFin[posicionActual]+retraso+0.5) ){

//                std::cout << "**********PILOTO SE PUEDE RETRASAR*************" << std::endl;
                nuevoEnListaCerrada(nomVuelo[posicionSiguientePiloto],nomVuelo[posicionActual],idCaminoPadre);

            }else if(hInicio[posicionSiguienteAvion]<(hFin[posicionActual]+retraso+0.5)
                     && posicionSiguienteAvion!= -1){
//                std::cout << "**********HAY QUE INSERTAR EN LISTA ABIERTA PORQUE NO SE PUEDE RETRASAR AVION*************" << std::endl;
                insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion],-1);
            }else if(hInicio[posicionSiguientePiloto]<(hFin[posicionActual]+retraso+0.5)
                     && posicionSiguientePiloto != -1){
//                std::cout << "**********HAY QUE INSERTAR EN LISTA ABIERTA PORQUE NO SE PUEDE RETRASAR PILOTO*************" << std::endl;
                insertar3enLista(vuelo,0,nomVuelo[posicionSiguientePiloto],-1);
            }else{
//                std::cout << "**********NO SE PUEDE RETRASAR YA QUE NO ENTRA EN NINGUNO DE LOS ANTERIORES CASO *************" << std::endl;
            }
        }
    }else{
//        std::cout << "IMPOSIBLE. AEROPUERTO CERRADO" << std::endl;
    }
}


void Reorden::busquedaPilotoYAvionSustitucion(int posicionActual,int idCaminoPadre){
//    std::cout << "---------EMPIEZA 1--------------" << std::endl;
    int masVuelosAfectados = hayMasVuelosAfectados(posicionActual);

    if(masVuelosAfectados!=-1){
//        std::cout << "*******HAY MAS VUELOS AFECTADOS********" << std::endl;
    }else{
        for(int i=0;i<posicionActual;i++){
        if((hFin[i]+0.5)<= hInicio[posicionActual] && origen[posicionActual]==destino[i]){
            QString vueloPilotoSiguiente = busquedaVueloPilotoSiguiente(nomVuelo[i]);
            QString vueloAvionSiguiente = busquedaVueloAvionSiguiente(nomVuelo[i]);

            if(vueloPilotoSiguiente == "empty" && vueloAvionSiguiente == "empty"){
                nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
//                ACABAR EL FOR
                i=posicionActual;

            }else{
                int posVueloPilotoSiguiente = busquedaPosicion(vueloAvionSiguiente);
                int posVueloAvionSiguiente = busquedaPosicion(vueloPilotoSiguiente);

//                YA NO HAY MÁS VUELOS PARA ESE PILOTO PERO SÍ PARA ESE AVION PERO EN PRINCIPIO NO HAY PROBLEMAS DE HORA
                if(posVueloPilotoSiguiente==-1 && posVueloAvionSiguiente!=-1
                        && hInicio[posVueloAvionSiguiente] > hFin[posicionActual]){

                    bool puede=avionPuedeVolver(posicionActual,posVueloAvionSiguiente);
                    if(puede==1){
//                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
//                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                    }
//                YA NO HAY MÁS VUELOS PARA ESE AVION PERO SÍ PARA ESE PILOTO PERO EN PRINCIPIO NO HAY PROBLEMAS DE HORA

                }else if(posVueloAvionSiguiente==-1 && posVueloPilotoSiguiente!=-1
                         && hInicio[posVueloPilotoSiguiente] > hFin[posicionActual]){

//                    std::cout << "AVION NO TIENE MAS, PILOTO SI" << std::endl;
                    bool puede=pilotoPuedeVolver(posicionActual,posVueloPilotoSiguiente);
                    if(puede==1){
//                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
//                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                    }
//                SI SIGUE HABIENDO ALGUNO QUE NO TENGA A CONTINUACIÓN MÁS VUELOS PERO NO ES EL CASO DE LOS ANTERIORES

                }else if(posVueloAvionSiguiente==-1 || posVueloPilotoSiguiente==-1){
//                    std::cout << "O NO TIENE MAS VUELOS EL PILOTO O EL AVION PERO NO SIRVE" << std::endl;
//                SI EL VUELO SIGUIENTE AQUI ES EL MISMO TANTO PARA PILOTO COMO PARA AVION
                }else if(posVueloPilotoSiguiente==posVueloAvionSiguiente
                         && hInicio[posVueloAvionSiguiente] > hFin[posicionActual]){
//                    std::cout << "CASO MISMO AVION MISMO PILOTO" << std::endl;
                    bool puede=avionPuedeVolver(posicionActual,posVueloAvionSiguiente);
                    if(puede==1){
//                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
//                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                    }

//                SI EL PILOTO VA A COGER OTRO VUELO DISTINTO AL AVION QUE LLEVO POR ÚLTIMA VEZ PERO ESO ES DESPUÉS A ESTE VUELO
                }else if(posVueloPilotoSiguiente!=posVueloAvionSiguiente
                         && hInicio[posVueloPilotoSiguiente] > hFin[posicionActual]
                         && hInicio[posVueloAvionSiguiente] > hFin[posicionActual]){

//                    std::cout << "CASO DIFERENTE AVION Y PILOTO PERO PILOTO EN PRINCIPIO NO SABE SI PUEDE LLEGAR" << std::endl;

                    bool puedeAvion=pilotoPuedeVolver(posicionActual,posVueloPilotoSiguiente);
                    bool puedePiloto=pilotoPuedeVolver(posicionActual,posVueloPilotoSiguiente);

                    if(puedePiloto==1 && puedeAvion){

//                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
//                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                    }

                }else{
//                    std::cout << "NINGUN AVION CUMPLE LOS REQUISITOS" << std::endl;
                }
            }

        }
    }
  }
}


void Reorden::busquedaPilotoSustitucion(int posicionActual,int idCaminoPadre){
//    std::cout << "---------EMPIEZA 2--------------" << std::endl;
    for(int i=0;i<posicionActual;i++){
        if((hFin[i]+0.5)<= hInicio[posicionActual] && origen[posicionActual]==destino[i]){
            QString vueloSiguiente = busquedaVueloPilotoSiguiente(nomVuelo[i]);

            if(vueloSiguiente == "empty"){
                nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
//                ACABAR EL FOR
                i=posicionActual;

            }else{
                int posVueloSiguiente = busquedaPosicion(vueloSiguiente);
                if(hInicio[posVueloSiguiente] > hFin[posicionActual]){

                    bool puede=pilotoPuedeVolver(posicionActual,posVueloSiguiente);
                    if(puede==1){
//                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
//                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],2,nomVuelo[i],-1);
                    }
                }else{
//                    std::cout << "NINGUN AVION CUMPLE LOS REQUISITOS" << std::endl;
                }
            }
        }
    }

}

void Reorden::busquedaAvionSustitucion(int posicionActual,int idCaminoPadre){
//    std::cout << "---------EMPIEZA 3--------------" << std::endl;
    for(int i=0;i<posicionActual;i++){
        if((hFin[i]+0.5)<= hInicio[posicionActual] && origen[posicionActual]==destino[i]){
            QString vueloSiguiente = busquedaVueloAvionSiguiente(nomVuelo[i]);

            if(vueloSiguiente == "empty"){
                nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
//                ACABAR EL FOR
                i=posicionActual;
            }else{
                int posVueloSiguiente = busquedaPosicion(vueloSiguiente);
                if(hInicio[posVueloSiguiente] > hFin[posicionActual]+0.5){
                    bool puede=avionPuedeVolver(posicionActual,posVueloSiguiente);
                    if(puede==1){
//                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
//                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        insertar3enLista(nomVuelo[posicionActual],3,nomVuelo[i],-1);
                    }
                }
            }
        }
    }
}

void Reorden::cancelar(int posicionActual, int idCaminoPadre)
{
//    std::cout << "---------EMPIEZA 4--------------" << std::endl;
    nuevoEnListaCerrada(nomVuelo[posicionActual],nomVuelo[posicionActual],idCaminoPadre);
}

bool Reorden::pilotoPuedeVolver(int posicionActual,int posicionDondeQuiereIr){

//    ES LA ULTIMA POSICION, POR TANTO NO TIENE PRISA POR VOLVER
    if(posicionDondeQuiereIr==-1){
        return 1;
    }else{
//        CONDICIONES PAA VOLVER:
//        ESTE EN EL MISMO AEROPUERTO QUE EL QUE QUIERE SUSTITUIR
//        EL VUELO SIGUIENTE NO SEA ANTES DE LA FINALIZACIÓN DEL QUE VA A SUSTITUIR

        for(int i=0;i<posicionDondeQuiereIr;i++){
            if(hFin[i]<(hInicio[posicionDondeQuiereIr]) && origen[i]==destino[posicionActual]
                    && destino[i]==origen[posicionDondeQuiereIr] && hInicio[i]>hFin[posicionActual]+retrasoIndividual[posicionActual])
            {
                return 1;
            }
        }
    }
    return 0;
}



bool Reorden::avionPuedeVolver(int posicionActual,int posicionDondeQuiereIr){

    if(posicionDondeQuiereIr==-1){
        return 1;
    }else{
        float duracionVuelo=hFin[posicionActual]-hInicio[posicionActual];
    //        1 PORQUE NECESITA MEDIA HORA PARA REPOSTAR CUANDO LLEGUE Y OTRA MEDIA CUANDO VUELVA
            if(hFin[posicionActual]+duracionVuelo+1+retrasoIndividual[posicionActual] < hInicio[posicionDondeQuiereIr])
                return 1;
    }

    return 0;
}


int Reorden::sePuedeCancelar(int posicionActual,int posicionDondeVa){

    if(posicionDondeVa==-1)
        return 1;

    for(int i=0;i<posicionDondeVa;i++){
        if(hFin[i]<(hInicio[posicionDondeVa]) && origen[i]==origen[posicionActual]
                && destino[i]==origen[posicionDondeVa] && hInicio[i]>=hInicio[posicionActual]
                && nomVuelo[posicionActual]!=nomVuelo[i] ){
            return 1;
        }
    }
    return 0;
}






void Reorden::insertar3enLista(QString vueloAnterior, int operacionAnterior, QString vuelo,int dosRutasReorden){

    int existe=buscarVuelo(vuelo,operacionAnterior);
    int posListaVueloAnterior=buscarVuelo(vueloAnterior,operacionAnterior);

    int posAnterior = busquedaPosicion(vueloAnterior);

    QString avionSiguiente = busquedaVueloAvionSiguiente(vuelo);
    QString pilotoSiguiente = busquedaVueloPilotoSiguiente(vuelo);
    int posAvionSiguiente = busquedaPosicion(avionSiguiente);
    int posPilotoSiguiente = busquedaPosicion(pilotoSiguiente);

    QString avionAnteriorSiguiente = busquedaVueloAvionSiguiente(vueloAnterior);
    QString pilotoAnteriorSiguiente = busquedaVueloPilotoSiguiente(vueloAnterior);


//    COMPRUEBO QUE EN SI ENTRARA EN EL CASO 1 Y SE SUSTITUYERA AVION Y PILOTO
//    EL PILOTO O AVION(O AMBOS)QUE YA NO VAYAN A REALIZAR ESA RUTA PUEDAN LLEGAR
//    A SU SIGUIENTE DESTINO CUYA HORA INICIA NO HA SIDO MODIFICADA

    int puedeVolverAvion=0;
    int puedeVolverPiloto=0;

    int tamFor=1;
    QString cambia="";
    puedeVolverPiloto=pilotoPuedeVolver(posAnterior,posPilotoSiguiente);
    puedeVolverAvion=avionPuedeVolver(posAnterior,posAvionSiguiente);

//    LAS OPERACIONES QUE SE PUDEN INCLUIR DETERMINAN TAMAÑO DEL FOR
//    SI EL PILOTO Y EL AVION SIGUIENTE ES EL MISMO NO PUEDE NI CAMBIAR PILOTO SOLO NI CAMBIAR AVION SOLO
    if(pilotoAnteriorSiguiente==avionAnteriorSiguiente){
//        VEMOS SI PUEDE CAMBIAR PILOTO_AVION
        if(puedeVolverAvion==1)
            tamFor=2;
//    SI NO VEMOS SI PUEDE CAMBIAR PILOTO
    }else if(pilotoAnteriorSiguiente==vuelo && puedeVolverPiloto==1){
        tamFor=2;
        cambia="piloto";
//    VEMOS SI PUEDE CAMBIAR AVION
    }else if(avionAnteriorSiguiente==vuelo && puedeVolverAvion==1){
        tamFor=2;
        cambia="avion";
    }


//    SI NO ESTÁ EN NINGUNA LISTA
    if(existe==-1){
//        SI NO COINCIDEN SE INSERTAN EN LA LISTA LAS POSIBILIDADES
        for(int i=0;i<tamFor;i++){
            if(tamFor==2 && cambia=="piloto" && i==1){
                i=2;
//                std::cout << "entro en el if PILOTO, i=" << i << std::endl;
            }
            if(tamFor==2 && cambia=="avion" && i==1){
                i=3;
//                std::cout << "entro en el if AVION, i=" << i << std::endl;
            }

            insertarListaAbierta(vuelo,i,posListaVueloAnterior,dosRutasReorden);
            insertarRutaSeguida(posListaVueloAnterior);
        }
    }else{
        for(int i=0;i<tamFor;i++){
            int j=i;
            if(tamFor==1 && cambia=="piloto")
                j=2;
            if(tamFor==1 && cambia=="avion")
                j=3;

            if(devolverCostF(existe+i)<(devolverCostF(posListaVueloAnterior)+tipoOperacion[j])){
                if(listaDondeEsta[existe+i]==0){
//                    std::cout << "EXISTE EN LISTA CERRADA" << std::endl;
                    reordenCerrada(existe+i);
                }else{
//                    std::cout << "EXISTE EN LISTA ABIERTA" << std::endl;
                    reordenAbierta(existe+i);
                }

            }
        }
    }
}
void Reorden::insertarListaAbierta(QString vuelo, int operacion, int posListaVueloAnterior,int dosRutasReorden){

// SIEMPRE SE VA A HACER A NO SER QUE SE HAGA DESPUÉS DE LA JUNTACIÓN DE DOS RUTAS DISTINTAS
    if(dosRutasReorden!=-2){
        caminosComprobados = caminosComprobados +1;

        if(posListaVueloAnterior!=-1){
            int posAnterior = busquedaPosicion(vuelosLista[posListaVueloAnterior]);
            int posActual = busquedaPosicion(vuelo);
            calcularRetraso(posListaVueloAnterior,posActual,posAnterior);
        }else{
            retrasoIndividual[caminosComprobados]=retraso;
        }

        //nombreAvion
        vuelosLista[caminosComprobados]=vuelo;

        //tipo de operacion
        vueloOperacion[caminosComprobados]=operacion;
        listaDondeEsta[caminosComprobados]=1;

        numeroDeElementosEnListaAbierta = numeroDeElementosEnListaAbierta+1;
        listaAbierta[numeroDeElementosEnListaAbierta] = caminosComprobados;

        if(posListaVueloAnterior==-1){
            dosReordenamientos[caminosComprobados]=0;
            dosReordenamientosElementoForaneo[caminosComprobados]=tam*3+1;
            dosReordenamientosPrimerElemento[caminosComprobados]=tam*3+1;
        }

        //ComprobarSiHayDosReordenamientos
        if(dosRutasReorden!=-1){
            dosReordenamientos[caminosComprobados]=1;
            dosReordenamientosElementoForaneo[caminosComprobados]=dosReordenamientosElementoForaneo[posListaVueloAnterior];
            dosReordenamientosPrimerElemento[caminosComprobados]=dosRutasReorden;

        }else if(dosReordenamientos[posListaVueloAnterior]==1){

            dosReordenamientos[caminosComprobados]=1;
            dosReordenamientosElementoForaneo[caminosComprobados]=dosReordenamientosElementoForaneo[posListaVueloAnterior];
            dosReordenamientosPrimerElemento[caminosComprobados]=dosReordenamientosPrimerElemento[posListaVueloAnterior];
        }else if(dosReordenamientosPrimerElemento[posListaVueloAnterior]==tam*3+1){
            //SI NO ES UN ELEMENTO CON DOS REORDENAMIENTOS
            dosReordenamientos[caminosComprobados]=0;
            dosReordenamientosElementoForaneo[caminosComprobados]=tam*3+1;
            dosReordenamientosPrimerElemento[caminosComprobados]=tam*3+1;
        }



        float cost=0;
    //    SI LA OPERACION ES RETRASAR EL COSTE ES VARIABLE. SE MULTIPLICA POR EL TIEMPO DEL RETRASO
        if(operacion==0){
            cost=tipoOperacion[operacion]*retrasoIndividual[caminosComprobados];
        }else{
            cost=tipoOperacion[operacion];
        }

        if(posListaVueloAnterior!=-1){
            insertarCostF(caminosComprobados,devolverCostF(posListaVueloAnterior)+cost);
        }else{
            insertarCostF(caminosComprobados,cost);
        }
    }

    int m = numeroDeElementosEnListaAbierta;

    while(m != 1){
        if(devolverCostF(listaAbierta[m]) <= devolverCostF(listaAbierta[m/2])){
           int temp = listaAbierta[m/2];
           listaAbierta[m/2] = listaAbierta[m];
           listaAbierta[m] = temp;

           m = m/2;
        }else{
          m=1;
        }

    }

}

int Reorden::borrarListaAbierta(int devolver){
    int aux=listaAbierta[1];

    listaAbierta[1] = listaAbierta[numeroDeElementosEnListaAbierta];
    numeroDeElementosEnListaAbierta = numeroDeElementosEnListaAbierta - 1;

    int v = 1;
    int u = v;
    int m=1;
    while(m!=0){

        if((2*u+1) <= numeroDeElementosEnListaAbierta){
            if(devolverCostF(listaAbierta[u]) >= devolverCostF(listaAbierta[2*u]))
                v=2*u;

            if(devolverCostF(listaAbierta[v]) >= devolverCostF(listaAbierta[2*u+1]))
                v = 2*u+1;


        }else if(2*u <= numeroDeElementosEnListaAbierta){
            m=0;
            if(devolverCostF(listaAbierta[u]) >= devolverCostF(listaAbierta[2*u]))
                v=2*u;
        }

        if(devolverCostF(listaAbierta[v])<devolverCostF(listaAbierta[u])){
            int temp = listaAbierta[u];
            listaAbierta[u] = listaAbierta[v];
            listaAbierta[v] = temp;
        }else{
            m=0;
        }
    }
    if(devolver==1){
        return aux;
    }else{
        return 0;
    }
}

void Reorden::nuevoEnListaCerrada(QString vuelo, QString vueloAnterior, int idCaminoPadre){

    caminosComprobados++;
    //vuelo
    vuelosLista[caminosComprobados]=vuelo;
    //tipo de operacion
    switch (vueloOperacion[idCaminoPadre]) {
        case 0:
            vueloOperacion[caminosComprobados]=10;
        break;
        case 1:
            vueloOperacion[caminosComprobados]=11;
        break;
        case 2:
            vueloOperacion[caminosComprobados]=12;
        break;
        case 3:
            vueloOperacion[caminosComprobados]=13;
        break;
        case 4:
            vueloOperacion[caminosComprobados]=14;
        break;


    }

    insertarCostF(caminosComprobados,devolverCostF(idCaminoPadre));


    insertarRutaSeguida(idCaminoPadre);
    int posAnterior = busquedaPosicion(vueloAnterior);
    int posActual = busquedaPosicion(vuelo);
    calcularRetraso(idCaminoPadre,posActual,posAnterior);

    if(dosReordenamientosPrimerElemento[idCaminoPadre]>=tam*3+1){
        numeroDeElementosEnListaAbierta=0;

    }else{
        int posVueloPrimerElemento=dosReordenamientosPrimerElemento[idCaminoPadre];

        dosReordenamientos[caminosComprobados]=1;
        dosReordenamientosElementoForaneo[caminosComprobados]=dosReordenamientosElementoForaneo[idCaminoPadre];
        dosReordenamientosPrimerElemento[caminosComprobados]=dosReordenamientosPrimerElemento[idCaminoPadre];


        if(dosReordenamientos[posVueloPrimerElemento]==1){


            dosReordenamientos[posVueloPrimerElemento]=0;
        }else{
            //    SE HA ENCONTRADO UN NODO FIN. CONCLUSIOND DEL ALGORITMO
            QStringList rutaSeguidaForanea=buscarOtraRutaSeguida();
//            std::cout << "*********QSTRING LIST 1***********" << std::endl;

            QStringList rutaSeguidaJunta=rutaSeguidaForanea+vuelosRutaSeguida[idCaminoPadre];
//            std::cout << "*********QSTRING LIST JUNTA***********" << std::endl;

//            AL JUNTAR LAS DOS LISTAS EL NODO COMUN DEL QUE COMIENZA SE REPETIRÁ. ELIMINARLO
            rutaSeguidaJunta.removeDuplicates();


            retrasoIndividual[caminosComprobados]=retrasoIndividual[posVueloPrimerElemento];

            //tipo de operacion especial para si sale ACABAR
            vueloOperacion[caminosComprobados]=15;

            numeroDeElementosEnListaAbierta = numeroDeElementosEnListaAbierta+1;
            listaAbierta[numeroDeElementosEnListaAbierta] = caminosComprobados;
            vuelosRutaSeguida[caminosComprobados] = rutaSeguidaJunta;

            int posUltimoAvionForaneo=rutaSeguidaForanea.size()-1;
            int posListaultimoAvionForaneo=rutaSeguidaForanea.at(posUltimoAvionForaneo).toLocal8Bit().toInt();
            insertarCostF(caminosComprobados,devolverCostF(caminosComprobados)+devolverCostF(posListaultimoAvionForaneo));
        }
    }



    insertarListaCerrada(caminosComprobados);


}

void Reorden::insertarListaCerrada(int id){

    listaDondeEsta[id]=0;

    numeroDeElementosEnListaCerrada = numeroDeElementosEnListaCerrada+1;
    listaCerrada[numeroDeElementosEnListaCerrada] = id;

}

int Reorden::buscarVuelo(QString vuelo,int operacion){

    for(int i=1;i<=caminosComprobados;i++){

        if(vuelosLista[i]==vuelo && operacion==9)
            return i;
        if(vuelosLista[i]==vuelo && vueloOperacion[i]==operacion)
            return i;
    }
    //SI NO HAY NINGÚN ELEMENTO IGUAL
    return -1;
}

void Reorden::reordenAbierta(int id){

    int posicion=posicionAbierta(id);

    caminosComprobados = caminosComprobados +1;

    vuelosRutaSeguida[caminosComprobados]=vuelosRutaSeguida[id];


    //nombreAvion
    vuelosLista[caminosComprobados]=vuelosLista[id];

    //tipo de operacion
    vueloOperacion[caminosComprobados]=vueloOperacion[id];

    listaDondeEsta[caminosComprobados]=1;

    listaAbierta[posicion] = caminosComprobados;

//    PROCEDEMOS A COMPROBAR SI EL ELEMENTO NUEVO CON MENOR COSTE DEBE IR MÁS ARRIBA
//    EN LA LISTA
    colocarAscendenteAbierta(posicion);
    std::cout << "HA PASADO" <<  std::endl;


//    LE AÑADIMOS EL COSTE IMPOSIBLE PARA QUE NUNCA SALGA Y
//    POR LE QUITAMOS EL NOMBRE DEL AVION POR SI RECORREMOS
//    OTRA VEZ TODOS LOS VUELOS
    vuelosLista[id]="0";
    insertarCostF(id,tipoOperacion[5]);


}



void Reorden::reordenCerrada(int id){

    int posicion=posicionCerrada(id);
    caminosComprobados = caminosComprobados +1;

    vuelosRutaSeguida[caminosComprobados]=vuelosRutaSeguida[id];

    //nombreAvion
    vuelosLista[caminosComprobados]=vuelosLista[id];

    //tipo de operacion
    vueloOperacion[caminosComprobados]=vueloOperacion[id];
    listaDondeEsta[caminosComprobados]=0;

    listaCerrada[posicion] = caminosComprobados;
//    insertarCostF(caminosComprobados,tiposOperacion[i]);

//    PROCEDEMOS A COMPROBAR SI EL ELEMENTO NUEVO CON MENOR COSTE DEBE IR MÁS ARRIBA
//    EN LA LISTA
    colocarAscendenteCerrada(posicion);

//    LE AÑADIMOS EL COSTE IMPOSIBLE PARA QUE NUNCA SALGA Y
//    POR LE QUITAMOS EL NOMBRE DEL AVION POR SI RECORREMOS
//    OTRA VEZ TODOS LOS VUELOS
    vuelosLista[id]="0";
    insertarCostF(id,tipoOperacion[5]);

}


void Reorden::colocarAscendenteAbierta(int pos){
    int m = pos;

    while(m != 1){
        if(devolverCostF(listaAbierta[m]) <= devolverCostF(listaAbierta[m/2])){
           int temp = listaAbierta[m/2];
           listaAbierta[m/2] = listaAbierta[m];
           listaAbierta[m] = temp;

           m = m/2;
        }else{
          m=1;
        }

    }
}


void Reorden::colocarAscendenteCerrada(int pos){
    int m = pos;

//    INTRODUCE LA TRAYECTORIA EN LA PILA EN EL LUGAR CORRECTO
    while(m != 1){
        if(devolverCostF(listaCerrada[m]) <= devolverCostF(listaCerrada[m/2])){
           int temp = listaCerrada[m/2];
           listaCerrada[m/2] = listaCerrada[m];
           listaCerrada[m] = temp;

           m = m/2;
        }else{
          m=1;
        }

    }
}

int Reorden::busquedaPosicion(QString vuelo){
    for(int i = 0;i<tam;i++){
        if(nomVuelo[i]==vuelo)
            return i;
    }
    return -1;
}


QString Reorden::busquedaVueloPilotoSiguiente(QString vuelo){
    for(int j = 0;j<numeroPilotos;j++){
        QStringList list = piloto[j].split(";",QString::SkipEmptyParts);
        QString *lista = new QString[list.size()];

        for(int k=0;k<list.size();k++){
            lista[k]=tr(list.at(k).toLocal8Bit().constData());
            if(k !=0 && lista[k-1]==vuelo)
                return (lista[k]);
        }
    }
    QString empty="empty";
    return empty;
}

QString Reorden::busquedaVueloAvionSiguiente(QString vuelo){

    for(int j = 0;j<numeroAviones;j++){
        QStringList list = avion[j].split(";",QString::SkipEmptyParts);
        QString *lista = new QString[list.size()];

        for(int k=0;k<list.size();k++){
            lista[k]=tr(list.at(k).toLocal8Bit().constData());
            if(k !=0 && lista[k-1]==vuelo)
              return (lista[k]);
        }
    }
    QString empty="empty";
    return empty;
}

void Reorden::insertarRutaSeguida(int posListaVueloAnterior){
    QString s = QString::number(caminosComprobados);
    if(posListaVueloAnterior!=-1){
        vuelosRutaSeguida[caminosComprobados]=vuelosRutaSeguida[posListaVueloAnterior];
    }
    vuelosRutaSeguida[caminosComprobados] << s;
}

void Reorden::calcularRetraso(int posListaVueloAnterior, int posActual, int posAnterior){
    if(vueloOperacion[posListaVueloAnterior]==0){
//        std::cout  << "Operacion 0---" << nomVuelo[posActual].toStdString() << std::endl;
        retrasoIndividual[caminosComprobados]=hFin[posAnterior]+retrasoIndividual[posListaVueloAnterior]+0.5-hInicio[posActual];
    }else{
//        std::cout  << "Resto de operaciones---" << std::endl;
        retrasoIndividual[caminosComprobados]=retrasoIndividual[posListaVueloAnterior];
    }
}


QStringList Reorden::buscarOtraRutaSeguida()
{
//    DEVUELVE LA RUTA DE LA OTRA TRAYECTORIA DE LA QUE DEPENDÍA
    for(int i=numeroDeElementosEnListaCerrada;i>0;i--){
        for (int j = 0; j < vuelosRutaSeguida[listaCerrada[i]].size(); ++j){
              int posicion = vuelosRutaSeguida[listaCerrada[i]].at(j).toLocal8Bit().toInt();
              if(dosReordenamientosElementoForaneo[caminosComprobados]==posicion){
                  return vuelosRutaSeguida[listaCerrada[i]];
              }
        }

    }
}


int Reorden::hayMasVuelosAfectados(int posActual)
{

    int posPrimerElemento=busquedaPosicion(vuelosLista[1]);
    QString vueloAvionSiguiente=busquedaVueloAvionSiguiente(nomVuelo[posActual]);
    int posAvionSiguiente=busquedaPosicion(vueloAvionSiguiente);
    QString vueloPilotoSiguiente=busquedaVueloAvionSiguiente(nomVuelo[posActual]);
    int posPilotoSiguiente=busquedaPosicion(vueloPilotoSiguiente);

    // SI HAY MÁS VUELOS EN LA LISTA Y COLISIONAN LAS HORAS
    if(hInicio[posAvionSiguiente]<=hFin[posPrimerElemento]+retraso+0.5){
        return posAvionSiguiente;
    }else if(hInicio[posPilotoSiguiente]<=hFin[posPrimerElemento]+retraso+0.5){
        return posPilotoSiguiente;
    }


    return -1;
}


void Reorden::insertarCostF(int posicion, float coste){
    costF[posicion]=coste;
}

float Reorden::devolverCostF(int posicion){
    return costF[posicion];
}

int Reorden::posicionAbierta(int id){
    for (int i=1;i<=numeroDeElementosEnListaAbierta;i++)
        if(listaAbierta[i]==id)
            return i;
}

int Reorden::posicionCerrada(int id){
    for (int i=0;i<numeroDeElementosEnListaCerrada;i++)
        if(listaCerrada[i]==id)
            return i;
}
