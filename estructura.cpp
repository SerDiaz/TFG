#include "estructura.h"

#include <QtWidgets>
#include <stdio.h>
#include <iostream>

Estructura::Estructura(QWidget *p)
        : QWidget(p)
{

}


void Estructura::asignar(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi)
{
    nomVuelo=new QString;
    origen=new QString;
    destino=new QString;
    hInicio=new float;
    hFin=new float;
    piloto=new QString;
    avion=new QString;


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

}


void Estructura::crear(QVBoxLayout *layoutGeneral){



//    Añadiendo horario
    horasLayout = new QHBoxLayout();
    horarios();
    layoutGeneral->addLayout(horasLayout);


//    Añadiendo aviones y vuelos
    avionesLayout = new QGridLayout();
    aviones();
    layoutGeneral->addLayout(avionesLayout);


}


void Estructura::horarios(){

    int numeroHoras = 33;
    int m=0;
    int h=0;

//    Creando Labels
    nameLabel = new QLabel(tr("Horas:"));
//    QLabel *hora[numeroHoras];


    for (int i = 0; i < numeroHoras; i++){
        hora[i] = new QLabel(this);
        QTime hora_minuto(6+h,0+m);
        QString hm;
        hm=hora_minuto.toString("hh:mm");
        hora[i]->setText(hm);
        m=m+30;
        if (m==60){
            m=0;
            h++;
        }
    }


    int a;
    a=hora[1]->width();

//    Añadiendo horario
    horasLayout->addWidget(nameLabel);
    horasLayout->addSpacing(12);


    for(int i= 0; i < numeroHoras; i++)
    {
       horasLayout->addWidget(hora[i]);
    }
}

void Estructura::aviones(){


        QVBoxLayout *aviones = new QVBoxLayout();

        int numeroAviones=18;

        QLabel *avion[numeroAviones];

//        Creando aviones
        aviones->addSpacing(3);
        QLabel *tamano = new QLabel(tr("Avion1"));
        aviones->addWidget(tamano);
        for (int i = 1; i < numeroAviones; i++){
           avion[i] = new QLabel(this);
           avion[i]->setText( tr("Avión %1").arg(i+1) );
//           avion[i]->setStyleSheet("QLabel { background-color : red; color : blue; }");
           aviones->addWidget(avion[i]);
        }

//        int a;
//        a=avion[1]->height();
//        std::cout << "Ancho .del avion " << a << std::endl;

        aviones->addSpacing(5);

//        Añadiendo al layout
        avionesLayout->addLayout(aviones,0,1);

//         Vuelos
        vuelosHoraLayout = new QVBoxLayout();






    }

void Estructura::pintarVuelos(){
//        vuelos(vuelosHora, origen, destino, nomVuelo, tam,hInicio, hFin,tam);
        vuelos();

//        Añadiendo vuelos al Layout
        avionesLayout->addLayout(vuelosHoraLayout,0,2);
}

void Estructura::vuelos(){



    label=new QLabel();
    int largo=20.5;
    float anchoColumna=38.85;
    float inicioRectangle=anchoColumna/2;


    scene = new QGraphicsScene(this);
//    LE DAMOS COLOR A LA ESCENA(UN GRIS IGUAL QUE EL RESTO DE LA VENTANA
    QColor color(240,240,240);
    scene->setBackgroundBrush(color);

    scene->setSceneRect(0,0,1275,355);
    view = new QGraphicsView(scene);





//    Draw pixmap general
        QPixmap pixmap(1364,370);
        pixmap.fill(QColor("transparent"));

//    Draw painter general
        QPainter painter(&pixmap);
        painter.setBrush(QColor("grey"));

//        *************************************************************
//        CUADRICULA DE COLUMNAS Y FILAS
//        for(int i=1; i<=(370/20.5);i++){
//            painter.drawRect(0,(i*20.5),1200,0);
////            std::cout << (i*20.5)<<std::endl;
//        }

//        for(int i=1; i<=(1200/39.15);i++){
//            painter.drawRect((i*39.15),0,0,370);
////            std::cout << (i*39.15)<<std::endl;
//        }
        painter.setBrush(QColor("yellow"));

//***********************************************************
//        CUADRICULA, IMPORTANTE

//        for(int i=0; i<=(370/20.5);i++){
//            painter.drawRect(0,(i*20.5)+(10)+(1/4),1384,1);
////            std::cout << (i*20.5)+(10)+(1/4)<<std::endl;
//        }

//        for(int i=0; i<=(1384/38.85);i++){
//            painter.drawRect((i*38.85)+19+0.5+((15/2)/100),0,1,370);
////            std::cout << "iteracion " << i << ": " <<(i*38.85)+19+0.5+((15/2)/100)<<std::endl;
//        }

//        *************************************************************



        float xRectangle;
        float yRectangle;
//        Saber en que avion va cada vuelo
        int avionVuelo[tam];
        float horaInicioOrdenada[tam];
        float horaFinOrdenada[tam];
        int avionSiguiente[tam];
        QString *nombreSiguiente = new QString[tam];
        int z=0;

        myrectangle = new Myrectangle[tam]();
        Myrectangle *rectangleInd[tam];

        for(int i=0;i<tam;i++){
            z=0;

            for(int j = 0;j<numeroAviones;j++){
                QStringList list = avion[j].split(QRegExp(";"),QString::SkipEmptyParts);

                QString *lista = new QString[list.size()];
                for(int k=1;k<list.size();k++){
                    lista[k]=tr(list.at(k).toLocal8Bit().constData());

                    z++;
                    if(lista[k] == nomVuelo[i]){
                        avionVuelo[i]=j;

//                        ESTO ME AYUDARÁ A SABER CUAL ES LA RUTA DE CADA PILOTO PARA PINTARLO DESPUÉS
                        horaInicioOrdenada[z-1]=hInicio[i];
                        horaFinOrdenada[z-1]=hFin[i];
                        avionSiguiente[z-1]=avionVuelo[i];
                        nombreSiguiente[z-1]=nomVuelo[i];


                        xRectangle=inicioRectangle*(1+(4*(hInicio[i]-6)));
                        yRectangle=(10+20.5*j)-(largo/2);
                        float tamRectangle=anchoColumna*(hFin[i]-hInicio[i])*2;
                        float finRectangle = xRectangle+tamRectangle;
                        float auxNomPosicion;
                        if (tamRectangle < 40){
                            auxNomPosicion=4;
                        }else if(tamRectangle > 100){

                            auxNomPosicion=2.5;
                        }else{
                            auxNomPosicion = 3;
                        }

                        int vCercano=0;

                        painter.setBrush(QColor("white"));
//                        SI ESTÁN MUY JUNTOS LOS VUELOS NO SOBREPONER LOS NOMBRES. SOLO SE PINTA EL FINAL
                        if(k>0)
                            vCercano = vueloCercano(lista[k-1],nomVuelo,hInicio[i],hFin);


                        if(vCercano==0)
                            painter.drawText((xRectangle-19),yRectangle+3.5,30,30,0,origen[i]);

                        painter.drawRect(xRectangle,yRectangle,tamRectangle,20.5);
                        painter.drawText((xRectangle+(tamRectangle/auxNomPosicion)),yRectangle+3.5,30,30,0,lista[k]);


//                        SI ESTÁN MUY JUNTOS LOS VUELOS NO SOBREPONER LOS NOMBRES. SOLO SE PINTA EL FINAL
                        vCercano==0;
                        if(k<list.size()-1)
                            vCercano = vueloCercano(lista[k+1],nomVuelo,hFin[i],hInicio);
                        int pos=vCercano+finRectangle+2;
                        painter.drawText(pos,yRectangle+3.5,30,30,0,destino[i]);



                        rectangleInd[i]=&myrectangle[i];

//                        SI ESTÁN MUY JUNTOS LOS VUELOS NO SOBREPONER LOS NOMBRES. SOLO SE PINTA EL FINAL
                        if(k>0)
                            vCercano = vueloCercano(lista[k-1],nomVuelo,hInicio[i],hFin);


                        if(vCercano==0){
//                            scene->addText(origen[i])
                            QGraphicsTextItem *ori = new QGraphicsTextItem;
                            ori->setPos(xRectangle-25,yRectangle-.5);
                            ori->setPlainText(origen[i]);
                            scene->addItem(ori);
                        }
//                            painter.drawText((xRectangle-19),yRectangle+3.5,30,30,0,origen[i]);

                       myrectangle[i].setScene(scene);
                       myrectangle[i].posandscale(xRectangle,yRectangle,tamRectangle,20.5);
                       myrectangle[i].name_posFligth(lista[k],auxNomPosicion);
                       scene->addItem(rectangleInd[i]);

//                        SI ESTÁN MUY JUNTOS LOS VUELOS NO SOBREPONER LOS NOMBRES. SOLO SE PINTA EL FINAL
                       vCercano=0;
                       if(k<list.size()-1)
                           vCercano = vueloCercano(lista[k+1],nomVuelo,hFin[i],hInicio);
                       int posDes=vCercano+finRectangle+2;
                       QGraphicsTextItem *des = new QGraphicsTextItem;
                       des->setPos(posDes,yRectangle-.5);
                       des->setPlainText(destino[i]);
                       scene->addItem(des);
//                       painter.drawText(pos,yRectangle+3.5,30,30,0,destino[i]);

                    }
                }
            }
        }



        int *listaPi=listaPilotos();

        for(int i=0;i<tam;i++){


            int posicion = buscarPosicion(listaPi[i],nombreSiguiente);
            int posicionSiguiente;

            bool ult=ultimo(i);
            if(ult==0)
                posicionSiguiente = buscarPosicion(listaPi[i+1],nombreSiguiente);

//            std::cout<< i << ", " << listaPi[i] << " ,posicion" << posicion << " ,posicionSiguiente" << posicionSiguiente <<std::endl;


            float xRectangle1;
            float yRectangle1;
            float xRectangle2;
            float yRectangle2;
            float tamRectangle;


            if(ult==0){
                tamRectangle=anchoColumna*(horaFinOrdenada[posicion]-horaInicioOrdenada[posicion])*2;
                xRectangle1=inicioRectangle*(1+(4*(horaInicioOrdenada[posicion]-6)))+ tamRectangle;

                xRectangle2=inicioRectangle*(1+(4*(horaInicioOrdenada[posicionSiguiente]-6)));
                yRectangle1=(10+20.5* avionSiguiente[posicion])-(largo/2)+10.25;
                yRectangle2=(10+20.5*( avionSiguiente[posicionSiguiente]))-(largo/2)+10.25;



                scene->addLine(xRectangle1,yRectangle1,xRectangle2,yRectangle2);
                painter.drawLine(xRectangle1,yRectangle1,xRectangle2,yRectangle2);
            }


        }


//    scene = new QGraphicsScene(this);

//    scene = new QGraphicsScene(this);
//    scene->setSceneRect(0,0,1364,370);
//    QGraphicsView *view = new QGraphicsView(scene);





//   int tamRectangle=1;
//   myrectangle = new Myrectangle[tamRectangle]();
//   Myrectangle *rectangle[tamRectangle];



//     for(int i=0;i<tamRectangle;i++){
//         rectangle[i]=&myrectangle[i];
//         myrectangle[i].setScene(scene);
//         myrectangle[i].posandscale(0,0,50,50);
//         scene->addItem(rectangle[i]);
//         rectangle[i]->setPos(0,i*100);
//     }


//    label->setPixmap(pixmap);


//    vuelosHoraLayout->addWidget(label);
    vuelosHoraLayout->addWidget(view);

//    herencia();



}

void Estructura::mostrarWidget(){
    view->show();
//    for(int i= 0; i < numeroHoras; i++)
//    {
//       hora[i]->show();
//    }
}

void Estructura::borrarWidget(){
//    vuelosHoraLayout->removeWidget(label);
//    vuelosHoraLayout->removeWidget(label);

    view->hide();
//    horasLayout->removeWidget(nameLabel);
//    for(int i= 0; i < numeroHoras; i++)
//    {
//       hora[i]->hide();
//    }

    delete vuelosHoraLayout;
    vuelosHoraLayout = new QVBoxLayout();

//    QWidget* stepchild;
//    stepchild=horasLayout->widget();
//    delete stepchild;


 //    update();

//    pintarVuelos();

}



float Estructura::convertirHora(QString *hora){

    float a = hora->split(":")[0].toFloat();
    float b = (hora->split(":")[1].toFloat() /100); /*100 conversion, 100 es decimal y 60 es minutos*/

//    10/60=5/3
    b=b*5/3;

    return (b + a);
}

int Estructura::vueloCercano(QString vuelo, QString *nombre, float hora1,float horas[]){
    float resta=0;
    for(int i=0;i<tam;i++){
        if(vuelo==nombre[i]){
            if(hora1>horas[1]){
                resta = (hora1-horas[i]);
            }else{
                resta = (horas[i]-hora1);
            }
            if(resta<0.75){
                return 5;
            }
        }
    }
    return 0;
}


int Estructura::buscarPosicion(int lista, QString *nombreSiguiente){
    for(int i=0;i<tam;i++){

          if(nombreSiguiente[i].toInt()==lista){
              return i;
          }


    }
}



int *Estructura::listaPilotos(){
    int aux=0;
    //¿TAMAÑO LISTA COMPLETA? SI NO NO FUNCIONA
    int lista[960];
    QString auxListaPilotos;
    for(int j=0;j<numeroPilotos;j++){
        QStringList list = piloto[j].split(QRegExp(";"),QString::SkipEmptyParts);
        for(int k=0;k<list.size();k++){
            if(tr(list.at(k).toLocal8Bit().constData())!=0){
              auxListaPilotos=tr(list.at(k).toLocal8Bit().constData());
              lista[aux]=auxListaPilotos.toInt();
              aux++;

            }

        }
    }

    int *plista=lista;

    return plista;
}

bool Estructura::ultimo(int i){
    int aux=0;
    int max=0;
    QString *listaPilotos = new QString[tam];

    for(int j=0;j<numeroPilotos;j++){
        QStringList list = piloto[j].split(QRegExp(";"),QString::SkipEmptyParts);


//        LAS LISTA QUE SE LEE TIENE LA ULTIMA POSICION DEL ARRAY VACIA
        max=list.size()-1;


        for(int k=0;k<=max;k++){

            listaPilotos[aux]=tr(list.at(k).toLocal8Bit().constData());

//            SI ES LA ÚLTIMA POSICIÓN DE LA LISTA DEVUELVE 1
            if(i==aux && k==max){
                return 1;
            }
            aux++;
        }
    }
    return 0;
}

void Estructura::herencia(){
    std::cout << "HERENCA" << std::endl;
}

