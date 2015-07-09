#include "window.h"
#include "estructura.h"
#include "reorden.h"

#include <QtWidgets>
#include <stdio.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <QAction>
#include <QFileDialog>
#include <QMenuBar>

using namespace std;
Window::Window(QWidget *parent)
    : QWidget(parent)
{


//    this->setFixedWidth(1202);
    this->setFixedWidth(1350);
    this->setFixedHeight(485);

//    cargarDatos();
    createMenus();

    mainLayout = new QVBoxLayout(this);

    std::cout << "outerLayout" << std::endl;
    estructura=new Estructura();

    std::cout << "Constructor estructura" << std::endl;

    std::cout << "ORDEN DE PINTAR 5" << std::endl;

//*******************
// DESCOMENTAR PARA QUE SE VEA TODO
//*******************
    estructura->crear(mainLayout);

    std::cout << "Se crea estructura" << std::endl;



//        QString av=tr("8414");
//    QString av=tr("8134");

//    reorden = new Reorden(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto,horarioInicio,horarioFin,avion,tamArchivo);

    std::cout << "ORDEN DE PINTAR 6" << std::endl;


    QHBoxLayout *formulario = new QHBoxLayout();
    QDialogButtonBox *buttonBox = new QDialogButtonBox;

    borrar = new QPushButton(tr("borrar"));
    crear = new QPushButton(tr("crear"));
//    probatura = new QPushButton(tr("probar"));
    QPushButton *cerrar = new QPushButton(tr("cerrar"));




    opcionesLayout = new QHBoxLayout;

    opcionesLayout->addWidget(borrar);
    opcionesLayout->addWidget(crear);
    opcionesLayout->addWidget(cerrar);
//    retrasoLayout->addWidget(probatura);
    crear->hide();
    borrar->hide();
    crearPress=0;     //PERMITE AL OPENFILE COMPROBAR QUE HA SIDO LA PRIMERA VEZ QUE ES USADO



    connect(cerrar, SIGNAL(clicked()), this, SLOT(close()));
    connect(borrar, SIGNAL(clicked()), this, SLOT(borrarEstructura()));
    connect(crear, SIGNAL(clicked()), this, SLOT(crearEstructura()));
//    connect(probatura, SIGNAL(clicked()), this, SLOT(probar()));




    formulario->addWidget(buttonBox);
    formulario->addLayout(opcionesLayout);


    mainLayout->setMenuBar(menuBar);
    mainLayout->addLayout(formulario);


   setWindowTitle(tr("TFG"));
}


void Window::probar(){
    cargarDatos();


  std::cout << "fileOpened: " << fileOpened.toStdString() << std::endl;


}


void Window::setDatos(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr,Estructura*est)
{
    numVuelos=ta;
    nAviones=nav;
    nPilotos=npi;
    fecha=fe;
    nombre=noV;
    nomA=ori;
    nomB=des;
    piloto=pi;
    horarioInicio=ini;
    horarioFin=fin;
    avion=avi;
    tamArchivo=taAr;
    estructura=est;

}


void Window::reordenarEstructura(QString nombreVuelo, float retraso)
{

    std::cout << "reordanEstructura*******************" << std::endl;
    std::cout << "tamArchivo: " << tamArchivo << std::endl;
    reorden = new Reorden(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto,horarioInicio,horarioFin,avion,tamArchivo);
    reorden->algoritmo(nombreVuelo,retraso);
    borrarEstructura();
    crearEstructura();
    std::cout << "PASO REORDEN" << std::endl;

}


void Window::crearEstructura(){
    crearPress=1;

    std::cout << "Crear estructura " << std::endl;



    crear->hide();
    borrar->show();

    std::cout << "PASA CREAR BOTONES " << std::endl;


    estructura->asignar(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto, horarioInicio, horarioFin, avion,tamArchivo,estructura);
    estructura->pintarVuelos();

    std::cout << "PASA CREAR" << std::endl;


}

void Window::borrarEstructura(){


    crear->show();
    borrar->hide();

    std::cout << "PASA BORRAR BOTONES " << std::endl;

    estructura->borrarWidget();

    std::cout << "PASA BORRAR " << std::endl;



}


void Window::cargarDatos(){
    QString aux;

    //Lectura
    QFile file_for_reading("vuelosabril12.txt");
    file_for_reading.open(QIODevice::ReadOnly);
    QTextStream text_stream_for_reading(&file_for_reading);


    text_stream_for_reading >> aux;

    QString auxFecha=aux;
    int tam=0;
    numVuelos=0;
    fecha="05/04/2012";
    while (aux!=0){
        text_stream_for_reading >> aux;
        text_stream_for_reading >> aux;
        text_stream_for_reading >> aux;
        text_stream_for_reading >> aux;
        text_stream_for_reading >> aux;
        text_stream_for_reading >> aux;
        text_stream_for_reading >> aux;

        auxFecha=aux;
        if(auxFecha==fecha)
            numVuelos++;
        tam++;
    }


    nombre=new QString[numVuelos];
    nomA=new QString[numVuelos];
    nomB=new QString[numVuelos];
    horarioInicio=new float[numVuelos];
    horarioFin=new float[numVuelos];



    text_stream_for_reading.seek(0);



    tamArchivo=tam;

    int z=0;
    QString aux2;
    for(int i = 0; i < tamArchivo; i++){
        text_stream_for_reading >> aux2;
        if(aux2==fecha){
            text_stream_for_reading >> aux;
            text_stream_for_reading >> nombre[z];
//            if(nombre[z] == tr("107"))
//                std::cout << "z: " << z << " avion: " << nombre[z].toStdString() << std::endl;
            text_stream_for_reading >> nomA[z];
            text_stream_for_reading >> nomB[z];
            text_stream_for_reading >> aux;
            QString *auxHoraInicio=new QString(aux);
            horarioInicio[z]=aFloat(auxHoraInicio);
            text_stream_for_reading >> aux;
            QString *auxHoraFin=new QString(aux);
            horarioFin[z]=aFloat(auxHoraFin);
            z++;
        }else{
            text_stream_for_reading >> aux;
            text_stream_for_reading >> aux;
            text_stream_for_reading >> aux;
            text_stream_for_reading >> aux;
            text_stream_for_reading >> aux;
            text_stream_for_reading >> aux;
        }
    }


        file_for_reading.close();
////        ************************************


//        QFile salida(fileOpened);
        QFile salida("salida05_04_2012.txt");

        salida.open(QIODevice::ReadOnly);
        QTextStream text_salida(&salida);

        text_salida >> aux;
        text_salida >> aux;
        text_salida >> aux;


        nAviones=-1;
        while (aux!="---"){
            text_salida >> aux;
            nAviones++;
        }

        nPilotos=-1;
        while (aux!=0){
            text_salida >> aux;
            nPilotos++;
        }


        text_salida.seek(0);

        text_salida >> aux;
        text_salida >> aux;
        text_salida >> aux;



        avion = new QString[nAviones];
        z=0;
        while (z<nAviones){
            text_salida >> avion[z];
            z++;

        }

        text_salida >> aux;

        int w=0;
        piloto = new QString[nPilotos];
        while (w<nPilotos){
            text_salida >> piloto[w];
            w++;

        }
         salida.close();

         std::cout << "AQUI" << std::endl;


}


void Window::createMenus()
{
    menuBar = new QMenuBar;

    std::cout << "hola" << std::endl;
    fileMenu = new QMenu(tr("&Archivo"), this);
    menuBar->addMenu(fileMenu);

    openAct = new QAction(tr("&Abrir..."),this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAct = new QAction(tr("&Guardar como..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    fileMenu->addSeparator();

    exitAct = new QAction(tr("&Salir"), this);
    fileMenu->addAction(exitAct);

    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


//    toolMenu = new QMenu(tr("&Tools"), this);
//    menuBar->addMenu(toolMenu);

    std::cout << "Acabo crear menu" << std::endl;


}

void Window::openFile()
{



    fileOpened = QFileDialog::getOpenFileName(
                this
                ,tr("Open File"),"",
                "All files(*.*);;Text File(*.txt)"
                );
//    QMessageBox::information(this,tr("Nombre del Archivo"),fileOpened);

    std::cout << fileOpened.toStdString() << std::endl;
    if(fileOpened!=""){
        cargarDatos();
        std::cout << "fileOpened: " << fileOpened.toStdString() << std::endl;
        if(crearPress==0)
            crear->show();
    }
}

void Window::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
//    if (!fileName.isEmpty())
//        addressWidget->writeToFile(fileName);
}

void Window::updateActions(const QItemSelection &selection)
{
//    QModelIndexList indexes = selection.indexes();

//    if (!indexes.isEmpty()) {
//        removeAct->setEnabled(true);
//        editAct->setEnabled(true);
//    } else {
//        removeAct->setEnabled(false);
//        editAct->setEnabled(false);
//    }
}
