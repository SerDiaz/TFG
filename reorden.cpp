#include "reorden.h"
#include "writing.h"

#include <QtWidgets>
#include <stdio.h>
#include <iostream>


//8200 comprobar caso(antes del grande)
Reorden::Reorden(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr, QWidget *parent)
    : QWidget(parent)
{
    tam = ta;
    tamArchivo=taAr;
    std::cout << "Reorden****************" << std::endl;
    std::cout << "tamArchivo: " << tamArchivo << std::endl;

    listaAbierta=new int[tam*3+1];
    listaCerrada=new int[tam*3+1];
    costF= new int [tam*3+1];
    costF[1]=0;
    avionesLista=new QString[(tam*3+1)];
    avionesRutaSeguida=new QStringList[(tam*3+1)];
    tiposOperacion=new int [6];
    avionOperacion=new int [tam*3+1];
    listaDondeEsta=new int [tam*3+1];
    retrasoIndividual=new float [tam*3+1];

    caminosComprobados=0;
    numeroDeElementosEnListaAbierta=0;
    numeroDeElementosEnListaCerrada=0;

//    costeRetraso ESTE VA A SER VARIABLE. EL COSTE PARA EL RETRASO DE 1 HORA ES 6
    tiposOperacion[0]=6;
//    costeCAvion+CPioloto SIEMPRE VA A SER EL MISMO
    tiposOperacion[1]=17;
//    costeCPiloto SIEMPRE VA A SER EL MISMO
    tiposOperacion[2]=2;
//    costeCAvion SIEMPRE VA A SER EL MISMO
    tiposOperacion[3]=15;

//    costeCancelar
    tiposOperacion[4]=100;
//    costeImposible
    tiposOperacion[5]=1000000000;
//    óptimo caso 0
    tiposOperacion[10]=0;
//    óptimo caso 1
    tiposOperacion[11]=0;
//    óptimo caso 2
    tiposOperacion[12]=0;




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

void Reorden::menu(QHBoxLayout *layout){

    layout->addSpacing(60);
    QPushButton *buttons[3];

//    for (int i = 0; i < 3; ++i) {
//        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
//        layout->addWidget(buttons[i]);

//    }

    buttons[0] = new QPushButton(tr("Reorden"));
    buttons[1] = new QPushButton(tr("Otro"));

    layout->addWidget(buttons[0]);
    layout->addWidget(buttons[1]);


    QDialogButtonBox *buttonBox = new QDialogButtonBox;


//    QPushButton *rotateWidgetsButton = buttonBox->addButton(tr("SLOTO"),QDialogButtonBox::ActionRole);

    QPushButton * closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));


//    connect(rotateWidgetsButton, SIGNAL(clicked()), this, SLOT(sloto()));



    layout->addWidget(buttonBox);

}

void Reorden::sloto(){
//    std::cout << "hola" << std::endl;
}

void Reorden::crear(QVBoxLayout *layoutGeneral){


//    Añadiendo horario
    QHBoxLayout *formulario = new QHBoxLayout();
//    horarios(horasLayout);
//    layoutGeneral->addLayo0ut(horasLayout);

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

//    QStringList fonts;
//        fonts << "Arial" << "Helvetica" << "Times" << "Courier";


//        QString a = fonts.at(2).toLocal8Bit();
//        std::cout << a.toStdString() << std::endl;


//        for (int i = 0; i < fonts.size(); ++i)
//             std::cout << fonts.at(i).toLocal8Bit().constData() << std::endl;



//    std::cout << "vuelo: " << vuelo.toStdString() << std::endl;
//    std::cout << "finVueloActual: " << finVueloActual << std::endl;
//    std::cout << "vueloPilotoSiguiente: " << vueloPilotoSiguiente.toStdString() << std::endl;
//    std::cout << "vueloAvionSiguiente: " << vueloAvionSiguiente.toStdString() << std::endl;
//    std::cout << "inicioAvionSiguiente: " << inicioAvionSiguiente << std::endl;
//    std::cout << "inicioPilotoSiguiente: " << inicioPilotoSiguiente << std::endl;

//    GUARDO EL PRIMER VUELO EN LA RUTA QUE SIGUE HE INDICO QUE SU ACCIÓN SIEMPRE VA A SER RETRASAR


//    COMPROBAR SI PASA ALGO POR RETRASAR. PUEDE SER QUE AVION TENGA VUELO O PILOTO TENGA VUELO
    if( inicioAvionSiguiente>finVueloActual+0.5+retraso
            && inicioPilotoSiguiente>finVueloActual+0.5+retraso){
        avionesLista[0]=vuelo;
        QString s = QString::number(0);
        avionesRutaSeguida[0] << s;
        avionOperacion[0]=0;
        retrasoIndividual[0]=retraso;
        std::cout << "NO PASO POR RETRASARLO. NO HACER ALGORITMO" << std::endl;
        writing= new Writing(tam,numeroAviones,numeroPilotos,fecha,nomVuelo,origen,destino,piloto,hInicio,hFin,avion,avionesLista,avionesRutaSeguida[0],avionOperacion,retrasoIndividual,tamArchivo);
        writing->rewriting();

    //    SI NO SE PUEDE HACEMOS ALGORITMO
    }else{

        insertarListaAbierta(vuelo,0,1);
        insertarRutaSeguida(-1);
        retrasoIndividual[caminosComprobados]=retraso;

        QString vueloSiguiente=0;

//        SI EL UNICO QUE NO PUEDE ES EL PILOTO
        if(inicioAvionSiguiente>finVueloActual+0.5+retrasoIndividual[caminosComprobados]
                && inicioPilotoSiguiente<=finVueloActual+0.5+retrasoIndividual[caminosComprobados]){

            vueloSiguiente=busquedaVueloPilotoSiguiente(vuelo);
//          TODOS LOS DEMÁS CASOS
        }else{
            vueloSiguiente =busquedaVueloAvionSiguiente(vuelo);
        }

        int posVuelo = busquedaPosicion(vuelo);
        int posVueloSiguiente = busquedaPosicion(vueloSiguiente);

//          SI PUDIERA IR HACIA SU SIGUIENTE DESTINO INCLUIR EN LA LISTA CANCELAR DESTINO
        bool puede=sePuedeCancelar(posVuelo,posVueloSiguiente);
        std::cout << "¿SE PUDO CANCELAR?: " << puede << std::endl;

        if(puede==1){
            insertarListaAbierta(vuelo,4,1);
            insertarRutaSeguida(-1);
            retrasoIndividual[caminosComprobados]=retraso;
        }




    //    EMPEZAMOS CON EL AVION SIGUIENTE AL QUE SE VEA AFECTADO PUES ESTE DIRECTAMENTE SE RETRASA
        algoritmoComun(vuelo,vueloSiguiente);



        std::cout << "--------------LISTA CERRADA-------------------" << std::endl;

        for(int i = 1; i <= numeroDeElementosEnListaCerrada; i++){
            std::cout << "---------" <<std::endl;
            std::cout << "Avion " << avionesLista[listaCerrada[i]].toStdString() << " operación: " << avionOperacion[listaCerrada[i]]<<std::endl;
            std::cout << "Coste TOTAL " << devolverCostF(listaCerrada[i]) <<std::endl;
            std::cout << "Ruta Seguida " <<std::endl;
            for (int j = 0; j < avionesRutaSeguida[listaCerrada[i]].size(); ++j){
                  int posicion = avionesRutaSeguida[listaCerrada[i]].at(j).toLocal8Bit().toInt();
                  std::cout << posicion << ". avion '" << avionesLista[posicion].toStdString()
                            << "', Hora Inicio de este avion '" << hInicio[busquedaPosicion(avionesLista[posicion])]
                               << "' y operacion '" << avionOperacion[posicion] << "'" << std::endl;
//                 std::cout << avionesRutaSeguida[listaCerrada[i]].at(j).toLocal8Bit().constData() << std::endl;

            }
//            POSICION ANTERIOR DEL ELEMENTO

            int posicionAnterior;
            if(avionesRutaSeguida[listaCerrada[i]].size()>1){
                posicionAnterior= avionesRutaSeguida[listaCerrada[i]].at(avionesRutaSeguida[listaCerrada[i]].size()-2).toLocal8Bit().toInt();
            }else{
                posicionAnterior= avionesRutaSeguida[listaCerrada[i]].at(avionesRutaSeguida[listaCerrada[i]].size()-1).toLocal8Bit().toInt();
            }
            std::cout << "posicion anterior: " << posicionAnterior <<std::endl;


            if(numeroDeElementosEnListaCerrada==(i)){
//              FIN DEL PROGRAMA. GUARDAR LOS DATOS MEDIANTE CLASE WRITING

                switch (avionOperacion[posicionAnterior]) {
                    case 0:{
                      int sizeRutaSeguida = avionesRutaSeguida[listaCerrada[i]].size();
                      int posicion = avionesRutaSeguida[listaCerrada[i]].at(sizeRutaSeguida-2).toLocal8Bit().toInt();
    //                      guardarReorden();
                      std::cout << "SIZE " << sizeRutaSeguida <<  std::endl;
                      std::cout << "SE RETRASA EL VUELO " << avionesLista[posicion].toStdString() << " Y SE SOLUCIONA" << std::endl;
                      std::cout << "*****************" <<  std::endl;
                    }break;
                    case 2:{
                      std::cout << "EL PILOTO DEL VUELO " << avionesLista[listaCerrada[i]].toStdString()<< " SE HARA CARGO" << std::endl;
                    }break;
                    case 3:{
                      std::cout << "EL AVION " << avionesLista[listaCerrada[i]].toStdString() << " SE HARA CARGO" << std::endl;
                    }break;
                }

                std::cout << "EYYY" << std::endl;
                std::cout << "MIRA A VER" << avionesRutaSeguida[0].size() << std::endl;

                writing= new Writing(tam,numeroAviones,numeroPilotos,fecha,nomVuelo,origen,destino,piloto,hInicio,hFin,avion,avionesLista,avionesRutaSeguida[listaCerrada[i]],avionOperacion,retrasoIndividual,tamArchivo);
                writing->rewriting();
//                guardarReorden();

            }
        }


        std::cout << "Caminos Comprobados: " << caminosComprobados << std::endl;

        delete listaAbierta;
        delete listaCerrada;
        delete costF;
        delete avionesRutaSeguida;
        delete avionesLista;
        delete listaDondeEsta;
        delete avionOperacion;


        avionesLista=new QString[(tam*3+1)];
        listaAbierta=new int[tam*3+2];
        listaCerrada=new int[tam];
        costF= new int [tam*3+1];
        avionOperacion=new int [tam*3+1];
        listaDondeEsta=new int [tam*3+1];
        avionesRutaSeguida=new QStringList[(tam*3+1)];
        caminosComprobados=0;
        costF[1]=0;
        numeroDeElementosEnListaAbierta=0;
        numeroDeElementosEnListaCerrada=0;

    }

}

void Reorden::algoritmoComun(QString vueloPadre, QString vueloHijo){




//    AÑADIMOS A LA LISTA ABIERTA LAS TRES DISTINTAS OPCIONES QUE PUEDE SUCEDER
//    EL TIPO DE OPERACIÓN 5 CORRESPONDE A QUE DA IGUAL EL TIPO DE OPERACION QUE SEA
//    insertar3enLista(vueloPadre, 5,vueloHijo);


    while(numeroDeElementosEnListaAbierta!=0){
        std::cout << "*********************************************" << caminosComprobados <<  std::endl;
        std::cout << "numeroDeElementosEnListaAbierta " << numeroDeElementosEnListaAbierta <<  std::endl;

        int id=borrarListaAbierta(1);
        std::cout << id << " " << avionesLista[id].toStdString() << ": " <<devolverCostF(id) << "(operacion " << avionOperacion[id] << ")" <<  std::endl;

        insertarListaCerrada(id);


        int posicionActual=busquedaPosicion(avionesLista[id]);
        std::cout << "Voy a hacer la avionOperacion " << avionOperacion[id] << " del vuelo "<< avionesLista[id].toStdString()<< std::endl;

        switch (avionOperacion[id]) {
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
        }
    }
}




void Reorden::retrasarAviones(int posicionActual, int idCaminoPadre){
    std::cout << "---------EMPIEZA 0--------------" << std::endl;

//    busquedaPilotoSustitucion(posicionActual);
//    busquedaAvionSutitucion(posicionActual);
    QString vuelo=avionesLista[idCaminoPadre];

    QString vueloAvionSiguiente=busquedaVueloAvionSiguiente(vuelo);
    int posicionSiguienteAvion=tam-1;
    QString vueloPilotoSiguiente=busquedaVueloPilotoSiguiente(vuelo);
    int posicionSiguientePiloto=tam-1;
    if(vueloAvionSiguiente!="empty")
       posicionSiguienteAvion = busquedaPosicion(vueloAvionSiguiente);
    if(vueloPilotoSiguiente!="empty")
       posicionSiguientePiloto=busquedaPosicion(vueloPilotoSiguiente);


    if(posicionSiguienteAvion!=0){
        std::cout << " vueloPilotoSiguiente : " << vueloPilotoSiguiente.toStdString() << std::endl;
        std::cout << " vueloAvionSiguiente : " << vueloAvionSiguiente.toStdString() << std::endl;

        std::cout << " avion vuelo: " << vuelo.toStdString() << std::endl;
        std::cout << " posicionSiguiente vuelo: " << nomVuelo[posicionSiguienteAvion].toStdString() << std::endl;
        std::cout << " posicionSiguiente INICIO: " << hInicio[posicionSiguienteAvion] << ", FIN: " << hFin[posicionSiguienteAvion] << std::endl;
        std::cout << " posicionActual vuelo: " << nomVuelo[posicionActual].toStdString() << std::endl;
        std::cout << " posicionActual INICIO: " << hInicio[posicionActual] << ", FIN: " << hFin[posicionActual] << std::endl;
        std::cout << " posicionSiguientePiloto vuelo: " << nomVuelo[posicionSiguientePiloto].toStdString() << std::endl;
        std::cout << " posicionSiguientePiloto INICIO: " << hInicio[posicionSiguientePiloto] << ", FIN: " << hFin[posicionSiguientePiloto] << std::endl;

        if(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5 <= 22.5){
            if(hInicio[posicionSiguienteAvion]>=(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5) && hInicio[posicionSiguientePiloto]>(hFin[posicionActual]+retraso+0.5)){

                nuevoEnListaCerrada(nomVuelo[posicionSiguienteAvion],nomVuelo[posicionActual],idCaminoPadre);


//                CASO RETRASAR AVION
            }else{
//                SI NO SE PUEDE Y EL PILOTO Y EL AVION VAN A PARTICIPAR EN EL SIGUIENTE VUELO
                if(posicionSiguienteAvion==posicionSiguientePiloto){
                    std::cout << "*************1º else posicionSiguienteAvion==posicionSiguientePiloto***********" << std::endl;
                    std::cout << " avion Siguiente" << nomVuelo[posicionSiguienteAvion].toStdString() << std::endl;
                    std::cout << " avion vuelo " << vuelo.toStdString() << std::endl;
//                    std::cout << "************"  << std::endl;
//                    std::cout << "No" << std::endl;

                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion]);
//                    std::cout << "avion siguiente: " << avionSiguiente.toStdString() << std::endl;
//                    algoritmo(avionSiguiente, retraso);

//                    SI AVION Y PILOTO TIENEN DISTINTOS VUELOS (O ALGUNO NO TIENE MÁS) Y PILOTO NO MOLESTA PERO EL AVION CHOCA
                }else if((hInicio[posicionSiguientePiloto]>(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5) && hInicio[posicionSiguienteAvion]<=(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5))){
                    std::cout << "*************2º else. El avion choca pero piloto no***********" << std::endl;
                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion]);
//                    SI AVION Y PILOTO TIENEN DISTINTOS VUELOS (O ALGUNO NO TIENE MÁS) Y AVION NO MOLESTA
                }else if((hInicio[posicionSiguienteAvion]>(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5))){
                    std::cout << "*************3º else. El piloto choca pero avion no***********" << std::endl;
                    insertar3enLista(vuelo,0,nomVuelo[posicionSiguientePiloto]);
                }else{
                    std::cout << "*************VUELO Y PILOTO DISTINTO Y NO PASA NINGUNO. AQUI ME QUEDO NO SIGO ESTE CAMINO***********" << std::endl;
                }
            }
        }else{
            std::cout << " avion " << nomVuelo[posicionActual].toStdString() << std::endl;
            std::cout << "IMPOSIBLE" << std::endl;
        }
    }else{
        if(hFin[posicionActual]+retrasoIndividual[idCaminoPadre]+0.5 < 22.5){
            std::cout << "**********Es ultima posicion pero se puede*************" << std::endl;
            std::cout << " avion Siguiente " << nomVuelo[posicionSiguienteAvion].toStdString() << std::endl;
            std::cout << " avion vuelo " << vuelo.toStdString() << std::endl;
            insertar3enLista(vuelo,0,nomVuelo[posicionSiguienteAvion]);
        }else{
            std::cout << " avion " << nomVuelo[posicionActual].toStdString() << std::endl;
            std::cout << "IMPOSIBLE ULTIMA POSICION" << std::endl;
        }
    }
    std::cout << "--------SE ACABO 0----------" << std::endl;
}

void Reorden::busquedaPilotoYAvionSustitucion(int posicionActual,int idCaminoPadre){
    std::cout << "---------EMPIEZA 1--------------" << std::endl;
    for(int i=0;i<posicionActual;i++){
        if((hFin[i]+0.5)<= hInicio[posicionActual] && origen[posicionActual]==destino[i]){
            QString vueloPilotoSiguiente = busquedaVueloPilotoSiguiente(nomVuelo[i]);
            QString vueloAvionSiguiente = busquedaVueloAvionSiguiente(nomVuelo[i]);

            std::cout << "VueloActual: " << nomVuelo[i].toStdString()
                         << ", VueloPilotoSiguiente: " << vueloPilotoSiguiente.toStdString()
                         << ", VueloAvionSiguiente: " << vueloAvionSiguiente.toStdString() << std::endl;

            if(vueloPilotoSiguiente == "empty" && vueloAvionSiguiente == "empty"){
                nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
//                ACABAR EL FOR
                i=posicionActual;
                std::cout << "LOS DOS SON EMPTY" << std::endl;
                std::cout << "vuelo: " << nomVuelo[i].toStdString() << std::endl;
                std::cout << "Hora Inicio "<< hInicio[i] << std::endl;
//                std::cout << "Lugar "<< destino[i].toStdString() << std::endl;
//                std::cout << "De donde sale "<< origen[posicionActual].toStdString() << std::endl;
            }else{
                int posVueloPilotoSiguiente = busquedaPosicion(vueloAvionSiguiente);
                int posVueloAvionSiguiente = busquedaPosicion(vueloPilotoSiguiente);

//                YA NO HAY MÁS VUELOS PARA ESE PILOTO PERO SÍ PARA ESE AVION PERO EN PRINCIPIO NO HAY PROBLEMAS DE HORA
                if(posVueloPilotoSiguiente==-1 && posVueloAvionSiguiente!=-1 && hInicio[posVueloAvionSiguiente] > hFin[posicionActual]){
                    std::cout << "************** " << std::endl;
                    std::cout << "PILOTO NO TIENE MAS, AVION SI" << std::endl;
                    std::cout << "vueloAvionSiguiente: " << vueloAvionSiguiente.toStdString() << std::endl;

                    bool puede=avionPuedeVolver(posicionActual,posVueloAvionSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],1,nomVuelo[i]);
                    }
//                YA NO HAY MÁS VUELOS PARA ESE AVION PERO SÍ PARA ESE PILOTO PERO EN PRINCIPIO NO HAY PROBLEMAS DE HORA
                }else if(posVueloAvionSiguiente==-1 && posVueloPilotoSiguiente!=-1 && hInicio[posVueloPilotoSiguiente] > hFin[posicionActual]){
                    std::cout << "************** " << std::endl;
                    std::cout << "AVION NO TIENE MAS, PILOTO SI" << std::endl;
                    std::cout << "vueloPilotoSiguiente: " << vueloPilotoSiguiente.toStdString() << std::endl;

                    bool puede=pilotoPuedeVolver(posicionActual,posVueloPilotoSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],1,nomVuelo[i]);
                    }
//                SI SIGUE HABIENDO ALGUNO QUE NO TENGA A CONTINUACIÓN MÁS VUELOS PERO NO ES EL CASO DE LOS ANTERIORES
                }else if(posVueloAvionSiguiente==-1 || posVueloPilotoSiguiente==-1){
                    std::cout << "O NO TIENE MAS VUELOS EL PILOTO O EL AVION PERO NO SIRVE" << std::endl;
                    std::cout << "posVueloAvionSiguiente: " << posVueloAvionSiguiente << std::endl;
                    std::cout << "posVueloPilotoSiguiente: " << posVueloPilotoSiguiente << std::endl;

//                SI EL VUELO SIGUIENTE AQUI ES EL MISMO TANTO PARA PILOTO COMO PARA AVION
                }else if(posVueloPilotoSiguiente==posVueloAvionSiguiente && hInicio[posVueloPilotoSiguiente] > hFin[posicionActual]){
                    std::cout << "************** " << std::endl;
                    std::cout << "CASO MISMO AVION MISMO PILOTO" << std::endl;
                    std::cout << "vueloAvionSiguiente: " << vueloAvionSiguiente.toStdString() << std::endl;
                    std::cout << "vueloPilotoSiguiente: " << vueloPilotoSiguiente.toStdString() << std::endl;


                    bool puede=avionPuedeVolver(posicionActual,posVueloAvionSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],1,nomVuelo[i]);
                    }
//                SI EL PILOTO VA A COGER OTRO VUELO DISTINTO AL AVION QUE LLEVO POR ÚLTIMA VEZ PERO ESO ES DESPUÉS A ESTE VUELO
                }else if(posVueloPilotoSiguiente!=posVueloAvionSiguiente && hInicio[posVueloPilotoSiguiente] > hFin[posicionActual]){

                    std::cout << "************** " << std::endl;
                    std::cout << "CASO DIFERENTE AVION Y PILOTO PERO PILOTO EN PRINCIPIO NO SABE SI PUEDE LLEGAR" << std::endl;
                    std::cout << "vueloAvionSiguiente: " << vueloAvionSiguiente.toStdString() << std::endl;
                    std::cout << "vueloPilotoSiguiente: " << vueloPilotoSiguiente.toStdString() << std::endl;

                    bool puede=pilotoPuedeVolver(posicionActual,posVueloPilotoSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],1,nomVuelo[i]);
                    }
//                SI EL AVION VA A COGER OTRO VUELO DISTINTO AL PILOTO QUE LO LLEVO POR ÚLTIMA VEZ PERO ESO ES DESPUÉS A ESTE VUELO
                }else if(posVueloPilotoSiguiente!=posVueloAvionSiguiente && hInicio[posVueloAvionSiguiente] > hFin[posicionActual]){
                    std::cout << "************** " << std::endl;
                    std::cout << "PILOTO NO TIENE MÁS, AVION SÍ" << std::endl;
                    std::cout << "vueloAvionSiguiente: " << vueloAvionSiguiente.toStdString() << std::endl;

                    bool puede=avionPuedeVolver(posicionActual,posVueloAvionSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],1,nomVuelo[i]);
                    }
                }else{
                    std::cout << "NINGUN AVION CUMPLE LOS REQUISITOS" << std::endl;
                }
            }
        }
    }
    std::cout << "--------SE ACABO 1----------" << std::endl;

}


void Reorden::busquedaPilotoSustitucion(int posicionActual,int idCaminoPadre){
    std::cout << "---------EMPIEZA 2--------------" << std::endl;
    for(int i=0;i<posicionActual;i++){
        if((hFin[i]+0.5)<= hInicio[posicionActual] && origen[posicionActual]==destino[i]){
            QString vueloSiguiente = busquedaVueloPilotoSiguiente(nomVuelo[i]);
            std::cout << "VueloActual: " << nomVuelo[i].toStdString()
                         << ", VueloSiguiente: " << vueloSiguiente.toStdString() << std::endl;

            if(vueloSiguiente == "empty"){
                nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
//                ACABAR EL FOR
                i=posicionActual;
                std::cout << "NO MÁS VUELOS" << std::endl;
                std::cout << "vuelo: " << nomVuelo[i].toStdString() << std::endl;
                std::cout << "Hora Inicio "<< hInicio[i] << std::endl;
//                std::cout << "Lugar "<< destino[i].toStdString() << std::endl;
//                std::cout << "De donde sale "<< origen[posicionActual].toStdString() << std::endl;
            }else{
                int posVueloSiguiente = busquedaPosicion(vueloSiguiente);
                if(hInicio[posVueloSiguiente] > hFin[posicionActual]){
                    std::cout << "************** " << std::endl;
                    std::cout << "HAY MÁS" << std::endl;
                    std::cout << "vueloSiguiente: " << vueloSiguiente.toStdString() << std::endl;

                    bool puede=pilotoPuedeVolver(posicionActual,posVueloSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],2,nomVuelo[i]);
                    }
                }else{
                    std::cout << "NINGUN AVION CUMPLE LOS REQUISITOS" << std::endl;
                }
            }
        }
    }
    std::cout << "--------SE ACABO 2----------" << std::endl;

}

void Reorden::busquedaAvionSustitucion(int posicionActual,int idCaminoPadre){
    std::cout << "---------EMPIEZA 3--------------" << std::endl;
    for(int i=0;i<posicionActual;i++){
        if((hFin[i]+0.5)<= hInicio[posicionActual] && origen[posicionActual]==destino[i]){
            QString vueloSiguiente = busquedaVueloAvionSiguiente(nomVuelo[i]);
            std::cout << "vueloSiguiente: " << vueloSiguiente.toStdString() << std::endl;

            if(vueloSiguiente == "empty"){
                nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
//                ACABAR EL FOR
                i=posicionActual;
                std::cout << "NO MÁS VUELOS" << std::endl;
                std::cout << "vuelo: " << nomVuelo[i].toStdString() << std::endl;
                std::cout << "Hora Inicio "<< hInicio[i] << std::endl;
//                std::cout << "Lugar "<< destino[i].toStdString() << std::endl;
//                std::cout << "De donde sale "<< origen[posicionActual].toStdString() << std::endl;
            }else{
                int posVueloSiguiente = busquedaPosicion(vueloSiguiente);
                if(hInicio[posVueloSiguiente] > hFin[posicionActual]+0.5){
                    std::cout << "************** " << std::endl;
                    std::cout << "HAY MÁS VUELOS" << std::endl;
                    std::cout << "vueloSiguiente: " << vueloSiguiente.toStdString() << std::endl;

                    bool puede=avionPuedeVolver(posicionActual,posVueloSiguiente);
                    if(puede==1){
                        std::cout << "SI PUEDE SUSTITUIR Y VOLVER" << std::endl;
                        nuevoEnListaCerrada(nomVuelo[i],nomVuelo[posicionActual],idCaminoPadre);
        //                ACABAR EL FOR
                        i=posicionActual;
                    }else{
                        std::cout << "NO PUEDE SUSTITUIR Y VOLVER. INSERTAR 3 EN LISTA" << std::endl;
                        std::cout << "nomVuelo[i]" << nomVuelo[i].toStdString() << std::endl;
                        std::cout << "nomVuelo[posicionActual]" << nomVuelo[posicionActual].toStdString() << std::endl;

                        insertar3enLista(nomVuelo[posicionActual],3,nomVuelo[i]);
                    }
                }
            }
        }
    }
    std::cout << "--------SE ACABO 3----------" << std::endl;

}



bool Reorden::pilotoPuedeVolver(int posicionActual,int posicionDondeVa){
//    std::cout << "vuelo posicionDondeIria: " << nomVuelo[posicionDondeIria].toStdString()<< std::endl;
//    std::cout << "hora: " << hInicio[posicionDondeIria]<< std::endl;
//    std::cout << "destino: " << destino[posicionDondeIria].toStdString()<< std::endl;
//    std::cout << "origen: " << origen[posicionDondeIria].toStdString()<< std::endl;

//    std::cout << "vuelo posicionSustituir: " << nomVuelo[posicionSustituir].toStdString() << std::endl;
//    std::cout << "posicionSustituir y de donde tiene que volver: " << destino[posicionSustituir].toStdString()<< std::endl;

    for(int i=0;i<posicionDondeVa;i++){
        if(hFin[i]<(hInicio[posicionDondeVa]) && origen[i]==destino[posicionActual]
                && destino[i]==origen[posicionDondeVa] && hInicio[i]>hFin[posicionActual])
        {
//            std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx"  << std::endl;
//            std::cout << "vuelo " << nomVuelo[i].toStdString() << std::endl;
//            std::cout << "hora: " << hInicio[i]<< std::endl;
//            std::cout << "fin: " << hFin[i]<< std::endl;
//            std::cout << "destino: " << destino[i].toStdString()<< std::endl;
//            std::cout << "origen: " << origen[i].toStdString()<< std::endl;
//            std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx"  << std::endl;

            return 1;
        }
    }

    return 0;
}

bool Reorden::avionPuedeVolver(int posicionActual,int posicionDondeVa){
    int duracionVuelo=hFin[posicionActual]-hInicio[posicionActual];
//        1 PORQUE NECESITA MEDIA HORA PARA REPOSTAR CUANDO LLEGUE Y OTRA MEDIA CUANDO VUELVA
        if(duracionVuelo+1 > hInicio[posicionDondeVa])
            return 1;
    return 0;
}

bool Reorden::puedeVolverMasRetraso(int posicionActual,int posicionDondeVa, float retraso){
    int duracionVuelo=hFin[posicionActual]-hInicio[posicionActual];
//        1 PORQUE NECESITA MEDIA HORA PARA REPOSTAR CUANDO LLEGUE Y OTRA MEDIA CUANDO VUELVA
        if(duracionVuelo+1+retraso > hInicio[posicionDondeVa])
            return 1;
    return 0;
}

int Reorden::sePuedeCancelar(int posicionActual,int posicionDondeVa){
//        std::cout << "vuelo posicionDondeVa: " << nomVuelo[posicionDondeVa].toStdString()<< std::endl;
//        std::cout << "hora: " << hInicio[posicionDondeVa]<< std::endl;
//        std::cout << "destino: " << destino[posicionDondeVa].toStdString()<< std::endl;
//        std::cout << "origen: " << origen[posicionDondeVa].toStdString()<< std::endl;

//        std::cout << "vuelo posicionActual: " << nomVuelo[posicionActual].toStdString() << std::endl;
//        std::cout << "posicionActual y de donde tiene que partir: " << origen[posicionActual].toStdString()<< std::endl;

    for(int i=0;i<posicionDondeVa;i++){
        if(hFin[i]<(hInicio[posicionDondeVa]) && origen[i]==origen[posicionActual]
                && destino[i]==origen[posicionDondeVa] && hInicio[i]>=hInicio[posicionActual]
                && nomVuelo[posicionActual]!=nomVuelo[i] ){
//                        std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx"  << std::endl;
//                        std::cout << "vuelo " << nomVuelo[i].toStdString() << std::endl;
//                        std::cout << "hora: " << hInicio[i]<< std::endl;
//                        std::cout << "fin: " << hFin[i]<< std::endl;
//                        std::cout << "destino: " << destino[i].toStdString()<< std::endl;
//                        std::cout << "origen: " << origen[i].toStdString()<< std::endl;
//                        std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxx"  << std::endl;

            return 1;
        }
    }
    return 0;
}






void Reorden::insertar3enLista(QString vueloAnterior, int operacionAnterior, QString vuelo){
    std::cout << "insertar3enLista vuelo:" << vuelo.toStdString() <<
              " que vino de " << vueloAnterior.toStdString() << " " << operacionAnterior
              << std::endl;
    std::cout << "************************* EXISTE VUELO EN LA LISTA?" << std::endl;
    int existe=buscarVuelo(vuelo,operacionAnterior);
    std::cout << "************************* HAY POSICION ANTERIOR?" << std::endl;
    int posVueloAnterior=buscarVuelo(vueloAnterior,operacionAnterior);
    std::cout << "num Elementos " << numeroDeElementosEnListaAbierta << std::endl;


    std::cout << "vueloAnterior: " << vueloAnterior.toStdString() << std::endl;
     std::cout << "posVueloAnterior: " << posVueloAnterior << std::endl;
    std::cout << "existe(valor): " << existe << std::endl;

//    QString vueloSiguienteAvion = busquedaVueloAvionSiguiente(vuelo);
//    QString vueloSiguientePiloto = busquedaVueloPilotoSiguiente(vuelo);

//    std::cout << "vueloSiguienteAvion: " << vueloSiguienteAvion.toStdString() << std::endl;
//    std::cout << "vueloSiguientePiloto: " << vueloSiguientePiloto.toStdString() << std::endl;


//    int posVueloSigAvion = busquedaPosicion(vueloSiguienteAvion);
//    int posVueloSigPiloto = busquedaPosicion(vueloSiguientePiloto);
    int posAnterior = busquedaPosicion(vueloAnterior);
    int posActual = busquedaPosicion(vuelo);

    QString avionSiguiente = busquedaVueloAvionSiguiente(vuelo);
    QString pilotoSiguiente = busquedaVueloPilotoSiguiente(vuelo);
    int posAvionSiguiente = busquedaPosicion(avionSiguiente);
    int posPilotoSiguiente = busquedaPosicion(pilotoSiguiente);


//    COMPRUEBO QUE EN SI ENTRARA EN EL CASO 1 Y SE SUSTITUYERA AVION Y PILOTO
//    EL PILOTO O AVION(O AMBOS)QUE YA NO VAYAN A REALIZAR ESA RUTA PUEDAN LLEGAR
//    A SU SIGUIENTE DESTINO CUYA HORA INICIA NO HA SIDO MODIFICADA

    int puedeVolverAvion=0;
    int puedeVolverPiloto=0;

    std::cout << "avionSiguiente: " << avionSiguiente.toStdString() << std::endl;
    std::cout << "pilotoSiguiente: " << pilotoSiguiente.toStdString() << std::endl;


    int tamFor=1;
    QString cambia="";

//    LAS OPERACIONES QUE SE PUDEN INCLUIR DETERMINAN TAMAÑO DEL FOR
//    SI EL PILOTO Y EL AVION SIGUIENTE ES EL MISMO NO PUEDE NI CAMBIAR PILOTO SOLO NI CAMBIAR AVION SOLO
    if(posPilotoSiguiente==posAvionSiguiente){
//        VEMOS SI PUEDE CAMBIAR PILOTO_AVION
        puedeVolverAvion=avionPuedeVolver(posAnterior,posAvionSiguiente);
        std::cout << "Entro en coincidente''''''''" << std::endl;
        if(puedeVolverAvion==1)
            tamFor=2;
//    SI NO VEMOS SI PUEDE CAMBIAR PILOTO
    }else if(posPilotoSiguiente==-1){
        std::cout << "Entro en piloto''''''''" << std::endl;
//        puedeVolverPiloto=pilotoPuedeVolver(posAnterior,posPilotoSiguiente);
//        if(puedeVolverPiloto){
            tamFor=3;
            cambia="piloto";
//        }
//    VEMOS SI PUEDE CAMBIAR AVION
    }else if(posAvionSiguiente==-1){
        std::cout << "Entro en avión''''''''" << std::endl;
//        puedeVolverAvion=avionPuedeVolver(posAnterior,posAvionSiguiente);
//        if(puedeVolverAvion){
            tamFor=3;
            cambia="avion";
//        }
    }


//    bool coincidenSiguiente=0;

    std::cout << "avionOperacion[posVueloAnterior:] " << avionOperacion[posVueloAnterior] << std::endl;
    std::cout << "vuelo anterior: " << nomVuelo[posAnterior].toStdString() << ", hFin[posAnterior] + retraso + 0.5: " << hFin[posAnterior]+retrasoIndividual[posVueloAnterior]+0.5 << std::endl;
    std::cout << "vuelo actual: " << nomVuelo[posActual].toStdString() << ", hInicio[posActual]: " << hInicio[posActual] << std::endl;
    std::cout << "retrasoIndividual[idCaminoPadre]: " << retrasoIndividual[posVueloAnterior] << std::endl;
    std::cout << "posAnterior: " << posAnterior <<  ", nombre vuelo: "<< nomVuelo[posAnterior].toStdString() << std::endl;
    std::cout << "posActual: " << posActual <<  ", nombre vuelo: "<< nomVuelo[posActual].toStdString() << std::endl;
    if(posPilotoSiguiente!=-1){
        std::cout << "posPilotoSiguiente: " << posPilotoSiguiente << ", nombre vuelo: "<< nomVuelo[posPilotoSiguiente].toStdString() << std::endl;
    }else{
        std::cout << "posPilotoSiguiente: " << posPilotoSiguiente<< std::endl;

    }
    if(posAvionSiguiente!=-1){
        std::cout << "posAvionSiguiente: " << posAvionSiguiente <<  ", nombre vuelo: "<< nomVuelo[posAvionSiguiente].toStdString() << std::endl;
    }else{
        std::cout << "posPilotoSiguiente: " << posAvionSiguiente << std::endl;
    }
    std::cout << "puedeVolverAvion: " << puedeVolverAvion << std::endl;
    std::cout << "puedeVolverPiloto: " << puedeVolverPiloto << std::endl;




//    if(avionOperacion[posVueloAnterior] == 0 && posPilotoSiguiente==posAvionSiguiente
//             && hFin[posAnterior]+retrasoIndividual[posVueloAnterior]+0.5>hInicio[posActual])
//        coincidenSiguiente=1;

//    std::cout << "coincidenSiguiente: " << coincidenSiguiente << std::endl;

//    int tamFor=5;
////    if(puedeVolverAvion == 0 || puedeVolverPiloto == 0){
//    if(seSobrePone==1){
//        tamFor=1;
//        if(coincidenSiguiente==1)
//         tamFor=2;
//    }


    std::cout << "tamFor: " << tamFor << std::endl;


//    SI NO ESTÁ EN NINGUNA LISTA
    if(existe==-1){
//        SI NO COINCIDEN SE INSERTAN EN LA LISTA LAS POSIBILIDADES
        for(int i=0;i<tamFor;i++){
            if(tamFor==3 && cambia=="avion"){
                i=3;
                std::cout << "entro en el if, i=" << i << std::endl;
            }
            std::cout << " ********* " <<  std::endl;
            std::cout << "----------Inicio DE INSERTAR "<< i << "-------- " << std::endl;
            insertarListaAbierta(vuelo,i,posVueloAnterior);
            insertarRutaSeguida(posVueloAnterior);
            calcularRetraso(posVueloAnterior,posActual,posAnterior);
            std::cout << "----------Final DE INSERTAR "<< i << "-------- " << std::endl;
        }
    }else{
        for(int i=0;i<tamFor;i++){
            std::cout << "existe(valor): " << existe << std::endl;
            int j=i;
            if(tamFor==3 && cambia=="avion")
                j=3;
            std::cout << " EN INSERTAR TODAVIA: Iteracion " << j <<" ,la lista abierta es " << existe+i
                         << " cuyo avion es "<< avionesLista[existe+i].toStdString()
                         << " operacion " << avionOperacion[existe+i]
                         << " y coste "<< devolverCostF(existe+i) << std::endl;
            if(devolverCostF(existe+i)<(devolverCostF(posVueloAnterior)+tiposOperacion[j])){
                if(listaDondeEsta[existe+i]==0){
                    std::cout << "EXISTE EN LISTA CERRADA" << std::endl;
                    reordenCerrada(existe+i);
                }else{
                    std::cout << "EXISTE EN LISTA ABIERTA" << std::endl;
                    reordenAbierta(existe+i);
                }

            }
        }
    }
}
void Reorden::insertarListaAbierta(QString vuelo, int i, int posVueloAnterior){

    caminosComprobados = caminosComprobados +1;

    //nombreAvion
    avionesLista[caminosComprobados]=vuelo;
//    avionesRutaSeguida[caminosComprobados]=

    //tipo de operacion
    avionOperacion[caminosComprobados]=i;
    listaDondeEsta[caminosComprobados]=1;

    numeroDeElementosEnListaAbierta = numeroDeElementosEnListaAbierta+1;
    listaAbierta[numeroDeElementosEnListaAbierta] = caminosComprobados;

    int cost=0;
//    SI LA OPERACION ES RETRASAR EL COSTE ES VARIABLE. SE MULTIPLICA POR EL TIEMPO DEL RETRASO
    if(tiposOperacion[i]==0){
        cost=tiposOperacion[i]*retrasoIndividual[i];
    }else{
        cost=tiposOperacion[i];
    }

    if(posVueloAnterior!=-1){
        insertarCostF(caminosComprobados,devolverCostF(posVueloAnterior)+cost);
    }else{
        insertarCostF(caminosComprobados,cost);
    }

    std::cout << "coste elemento " << caminosComprobados << ", vuelo " <<
                 avionesLista[caminosComprobados].toStdString() << ": " <<
                 devolverCostF(caminosComprobados) << std::endl;

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
    std::cout << "num Elementos " << numeroDeElementosEnListaAbierta << std::endl;

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
    avionesLista[caminosComprobados]=vuelo;
    //tipo de operacion
    switch (avionOperacion[idCaminoPadre]) {
        case 0:
            avionOperacion[caminosComprobados]=10;
        break;
        case 1:
            avionOperacion[caminosComprobados]=11;
        break;
        case 2:
            avionOperacion[caminosComprobados]=12;
        break;
        case 3:
            avionOperacion[caminosComprobados]=13;
        break;

    }


    std::cout << "COSTE: " << devolverCostF(idCaminoPadre) << std::endl;

    insertarCostF(caminosComprobados,devolverCostF(idCaminoPadre));

    std::cout << "caminosComprobados: " << caminosComprobados << std::endl;
    std::cout << "idCaminoPadre: " << idCaminoPadre << std::endl;


    insertarRutaSeguida(idCaminoPadre);
    int posAnterior = busquedaPosicion(vueloAnterior);
    int posActual = busquedaPosicion(vuelo);
    calcularRetraso(idCaminoPadre,posActual,posAnterior);

    //    SE HA ENCONTRADO UN NODO FIN. CONCLUSIOND DEL ALGORITMO
    numeroDeElementosEnListaAbierta=0;


    std::cout << "ESTA VA A SER EL ÚLTIMO A INSERTAR. SE HA RESOLVIDO EL PROBLEMA" <<  std::endl;
    insertarListaCerrada(caminosComprobados);


}

void Reorden::insertarListaCerrada(int id){
    std::cout << "VOY A INSERTAR EN LISTA CERRADA: " << avionesLista[id].toStdString() <<  std::endl;

    listaDondeEsta[id]=0;

    numeroDeElementosEnListaCerrada = numeroDeElementosEnListaCerrada+1;
    listaCerrada[numeroDeElementosEnListaCerrada] = id;

}

int Reorden::buscarVuelo(QString vuelo,int operacion){
    std::cout << "********************************************* vuelo: " << vuelo.toStdString() <<  std::endl;
    std::cout << "********************************************* operacion: " << operacion <<  std::endl;
    std::cout << "********************************************* -------------" <<  std::endl;

    for(int i=1;i<=caminosComprobados;i++){
        std::cout << "********************************************* i: " << i <<  std::endl;
        std::cout << "********************************************* Avion lista: " << avionesLista[i].toStdString() <<  std::endl;
        std::cout << "********************************************* operacion: " << avionOperacion[i] <<  std::endl;
        std::cout << "********************************************* tipo operacion: " << listaDondeEsta[i] <<  std::endl;

        if(avionesLista[i]==vuelo && operacion==9)
            return i;
        if(avionesLista[i]==vuelo && avionOperacion[i]==operacion)
            return i;
    }
    //SI NO HAY NINGÚN ELEMENTO IGUAL
    return -1;
}

void Reorden::reordenAbierta(int id){
    std::cout << "num Elementos " << numeroDeElementosEnListaAbierta << std::endl;

    std::cout << "Cacho, entro en reorden. Ahora ID: " << id << std::endl;

    int posicion=posicionAbierta(id);

    std::cout << "Avion vuelo id: " << avionesLista[id].toStdString() << std::endl;

    std::cout << "Posicion " << posicion << std::endl;

    caminosComprobados = caminosComprobados +1;

    avionesRutaSeguida[caminosComprobados]=avionesRutaSeguida[id];


    //nombreAvion
    avionesLista[caminosComprobados]=avionesLista[id];

    //tipo de operacion
    avionOperacion[caminosComprobados]=avionOperacion[id];

    listaDondeEsta[caminosComprobados]=1;

    listaAbierta[posicion] = caminosComprobados;
//    insertarCostF(caminosComprobados,tiposOperacion[i]);
    std::cout << "HA LLEGADO AQUI" <<  std::endl;

//    PROCEDEMOS A COMPROBAR SI EL ELEMENTO NUEVO CON MENOR COSTE DEBE IR MÁS ARRIBA
//    EN LA LISTA
    colocarAscendenteAbierta(posicion);
    std::cout << "HA PASADO" <<  std::endl;


//    LE AÑADIMOS EL COSTE IMPOSIBLE PARA QUE NUNCA SALGA Y
//    POR LE QUITAMOS EL NOMBRE DEL AVION POR SI RECORREMOS
//    OTRA VEZ TODOS LOS VUELOS
    avionesLista[id]="0";
    insertarCostF(id,tiposOperacion[5]);


}



void Reorden::reordenCerrada(int id){

    int posicion=posicionCerrada(id);
    caminosComprobados = caminosComprobados +1;

    avionesRutaSeguida[caminosComprobados]=avionesRutaSeguida[id];

    //nombreAvion
    avionesLista[caminosComprobados]=avionesLista[id];

    //tipo de operacion
    avionOperacion[caminosComprobados]=avionOperacion[id];
    listaDondeEsta[caminosComprobados]=0;

    listaCerrada[posicion] = caminosComprobados;
//    insertarCostF(caminosComprobados,tiposOperacion[i]);

//    PROCEDEMOS A COMPROBAR SI EL ELEMENTO NUEVO CON MENOR COSTE DEBE IR MÁS ARRIBA
//    EN LA LISTA
    colocarAscendenteCerrada(posicion);

//    LE AÑADIMOS EL COSTE IMPOSIBLE PARA QUE NUNCA SALGA Y
//    POR LE QUITAMOS EL NOMBRE DEL AVION POR SI RECORREMOS
//    OTRA VEZ TODOS LOS VUELOS
    avionesLista[id]="0";
    insertarCostF(id,tiposOperacion[5]);

}


void Reorden::insertarCostF(int posicion, int coste){
    costF[posicion]=coste;
}

int Reorden::devolverCostF(int posicion){
    return costF[posicion];
}

int Reorden::posicionAbierta(int id){
    std::cout << "num Elementos " << numeroDeElementosEnListaAbierta << std::endl;

    for (int i=1;i<=numeroDeElementosEnListaAbierta;i++){
        std::cout << "Iteracion " << i << " ,la lista abierta es " << listaAbierta[i]
                     << " cuyo avion es "<< avionesLista[listaAbierta[i]].toStdString()
                     << " operacion " << avionOperacion[listaAbierta[i]]
                     << " y coste "<< devolverCostF(listaAbierta[i]) << std::endl;
    }
    for (int i=1;i<=numeroDeElementosEnListaAbierta;i++)
        if(listaAbierta[i]==id)
            return i;
}

int Reorden::posicionCerrada(int id){
    for (int i=0;i<numeroDeElementosEnListaCerrada;i++)
        if(listaCerrada[i]==id)
            return i;
}

void Reorden::colocarAscendenteAbierta(int pos){
    int m = pos;

    std::cout << "DENTRO DE COLOCAR ASCENDENTE ABIERTA" <<  std::endl;
    std::cout << "posicion" << pos << std::endl;


    while(m != 1){
//        std::cout << "m: " << m <<  std::endl;
//        std::cout << "listaAbierta[m]: " << listaAbierta[m] <<  std::endl;
//        std::cout << "listaAbierta[m/2]: " << listaAbierta[m/2] << std::endl;
        if(devolverCostF(listaAbierta[m]) <= devolverCostF(listaAbierta[m/2])){
           int temp = listaAbierta[m/2];
           listaAbierta[m/2] = listaAbierta[m];
           listaAbierta[m] = temp;

           m = m/2;
        }else{
          m=1;
        }

    }
    std::cout << "FUERA" <<  std::endl;

}


void Reorden::colocarAscendenteCerrada(int pos){
    int m = pos;

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

void Reorden::insertarRutaSeguida(int posVueloAnterior){
    QString s = QString::number(caminosComprobados);
    if(posVueloAnterior!=-1){
        avionesRutaSeguida[caminosComprobados]=avionesRutaSeguida[posVueloAnterior];
    }
    avionesRutaSeguida[caminosComprobados] << s;
}

void Reorden::calcularRetraso(int posVueloAnterior, int posActual, int posAnterior){
    std::cout  << "caminosComprobados: " << caminosComprobados << std::endl;
    for(int i=0;i<=caminosComprobados;i++)
        std::cout << "i: " << i << ", nombre: "<< avionesLista[i].toStdString()  << std::endl;


    std::cout  << "posActual: " << nomVuelo[posActual].toStdString() << std::endl;
    std::cout  << "posAnterior: " << nomVuelo[posAnterior].toStdString() << std::endl;




    if(avionOperacion[posVueloAnterior]==0){
        std::cout  << "Operacion 0---" << nomVuelo[posActual].toStdString() << std::endl;
        retrasoIndividual[caminosComprobados]=hFin[posAnterior]+retrasoIndividual[posVueloAnterior]+0.5-hInicio[posActual];
    }else{
        std::cout  << "Resto de operaciones---" << std::endl;
        retrasoIndividual[caminosComprobados]=retrasoIndividual[posVueloAnterior];
    }

    std::cout << avionesLista[caminosComprobados].toStdString() << ", retrasoIndividual[caminosComprobados]: " << retrasoIndividual[caminosComprobados] << std::endl;
    std::cout << avionesLista[posVueloAnterior].toStdString() << ", retrasoIndividual[posVueloAnterior]: " << retrasoIndividual[posVueloAnterior] << std::endl;
}


