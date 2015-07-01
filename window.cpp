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
    this->setFixedHeight(465);

//    cargarDatos();
    createMenus();

    outerLayout = new QVBoxLayout(this);

    std::cout << "outerLayout" << std::endl;

    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene);
//    scene->addItem(outerLayout);
//    view->show();
//    outerLayout->
//    setScene(scene);

//    outerLayout->addWidget(view);

    QBrush redBrush(Qt::red);
    QPen blackpen(Qt::black);



    blackpen.setWidth(6);
    ellipse = scene->addEllipse(10,10,100,100,blackpen,redBrush);

    ellipse->setPos(100, 100);
    rectangle=scene->addRect(-100,-100,50,50,blackpen,redBrush);
    rectangle->setFlag(QGraphicsItem::ItemIsMovable);

    rectangle->setPos(150, 150);

    QPointF posicionEllipse= ellipse->QGraphicsItem::pos();
    int posicionX=posicionEllipse.x();
    int posicionY=posicionEllipse.y();

    std::cout << "posicionX: " << posicionX << std::endl;
    std::cout << "posicionY: " << posicionY << std::endl;

     QPointF posicionRectangle=rectangle->QGraphicsItem::pos();
     posicionX=posicionRectangle.x();
     posicionY=posicionRectangle.y();

     std::cout << "posicionX: " << posicionX << std::endl;
     std::cout << "posicionY: " << posicionY << std::endl;




//    estructura=new Estructura(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto, horarioInicio, horarioFin, avion);
    estructura=new Estructura();

    std::cout << "Constructor estructura" << std::endl;

//*******************
// DESCOMENTAR PARA QUE SE VEA TODO
//*******************
    estructura->crear(outerLayout);

    std::cout << "Se crea estructura" << std::endl;



//        QString av=tr("8414");
//    QString av=tr("8134");

//    reorden = new Reorden(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto,horarioInicio,horarioFin,avion,tamArchivo);



    QHBoxLayout *formulario = new QHBoxLayout();
//    reorden->menu(formulario);
//    outerLayout->addLayout(formulario);

    QDialogButtonBox *buttonBox = new QDialogButtonBox;

    QPushButton *closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    avionEdit = new QLineEdit(this);
    QLabel* avn = new QLabel("Avion:", this);
    retrasoEdit = new QLineEdit(this);
    QLabel* retraso = new QLabel("Retraso:", this);
    aceptar = new QPushButton(tr("Reordenar"));
    borrar = new QPushButton(tr("borrar"));
    QPushButton *mostrar = new QPushButton(tr("mostrar"));
    crear = new QPushButton(tr("crear"));
    probatura = new QPushButton(tr("probar"));



    retrasoLayout = new QHBoxLayout;
    retrasoLayout->addWidget(retraso);
    retrasoLayout->addWidget(retrasoEdit);
    retrasoLayout->addWidget(avn);
    retrasoLayout->addWidget(avionEdit);
    retrasoLayout->addWidget(aceptar);
    retrasoLayout->addWidget(borrar);
    retrasoLayout->addWidget(mostrar);
    retrasoLayout->addWidget(crear);
    retrasoLayout->addWidget(probatura);



//    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
//    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(aceptar, SIGNAL(clicked()), this, SLOT(hola()));
    connect(borrar, SIGNAL(clicked()), this, SLOT(borrarEstructura()));
    connect(mostrar, SIGNAL(clicked()), this, SLOT(mostrarEstructura()));
    connect(crear, SIGNAL(clicked()), this, SLOT(crearEstructura()));
    connect(probatura, SIGNAL(clicked()), this, SLOT(probar()));





    formulario->addWidget(buttonBox);
    formulario->addLayout(retrasoLayout);


    outerLayout->setMenuBar(menuBar);
    outerLayout->addLayout(formulario);


   setWindowTitle(tr("TFG"));
}


void Window::probar(){
    cargarDatos();


  std::cout << "fileOpened: " << fileOpened.toStdString() << std::endl;


}

void Window::herencia(){
    std::cout << "HEREDA" << std::endl;
}

void Window::hola(){

    std::cout << "hola*******************" << std::endl;
    std::cout << "tamArchivo: " << tamArchivo << std::endl;
    reorden = new Reorden(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto,horarioInicio,horarioFin,avion,tamArchivo);


    if(avionEdit->text() != 0 && retrasoEdit->text() !=0)
      reorden->algoritmo(avionEdit->text(),retrasoEdit->text().toFloat());
     //        QString pos = reorden->busquedaVueloAvionSiguiente(av);


     //        // POSICION DE 107 la Z=12
     //        std::cout << "avion 8414" << std::endl;
     //        std::cout << "pos " << pos.toStdString() << std::endl;
    borrarEstructura();
    crearEstructura();
}

void Window::crearEstructura(){
    std::cout << "Crear estructura " << std::endl;

//    if(fileOpened!=""){
//        cargarDatos();
        estructura->asignar(numVuelos,nAviones,nPilotos,fecha,nombre,nomA,nomB,piloto, horarioInicio, horarioFin, avion);
        estructura->pintarVuelos();
//    }
}

void Window::mostrarEstructura(){
    estructura->mostrarWidget();

}

void Window::borrarEstructura(){
//    layout()->removeAt(widget);
//    delete widget;
//    foreach(outerLayout->children())
//    outerLayout->removeWidget(*parent);
//    QWidget w;
//    outerLayout->addWidget(w);

//    label = new QLabel(outerLayout);

//    label = new QLabel("text", outerLayout);



//    crear->setVisible(false);
//    probatura-> hide();

    estructura->borrarWidget();
//    retrasoLayout->removeWidget(retrasoEdit);
//    retrasoLayout->removeWidget(avionEdit);
//    retrasoLayout->removeWidget(aceptar);
//    retrasoLayout->removeWidget(borrar);
//    retrasoLayout->removeWidget(crear);
//    retrasoLayout->removeWidget(probatura);
//    delete retrasoLayout;

//    update();

//    delete widget;

//    delete outerLayout;
//    Window();
//    Window();
//    outerLayout = new QVBoxLayout(this);
    //    Window(this);
//        estructura->borrarWidget();

//    update();
//    Window();





}

void Window::hola(int i){
    std::cout << "hola " << i << endl;
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
            horarioInicio[z]=convertirHora(auxHoraInicio);
            text_stream_for_reading >> aux;
            QString *auxHoraFin=new QString(aux);
            horarioFin[z]=convertirHora(auxHoraFin);
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



}


float Window::convertirHora(QString *hora){

    float a = hora->split(":")[0].toFloat();
    float b = (hora->split(":")[1].toFloat() /100); /*100 conversion, 100 es decimal y 60 es minutos*/

//    10/60=5/3
    b=b*5/3;

    return (b + a);
}



//******************************************
//******************************************
//******************************************



void Window::createMenus()
{
    menuBar = new QMenuBar;

    std::cout << "hola" << std::endl;
    fileMenu = new QMenu(tr("&File"), this);
    menuBar->addMenu(fileMenu);

    openAct = new QAction(tr("&Open..."),this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exitAct);

    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


    toolMenu = new QMenu(tr("&Tools"), this);
    menuBar->addMenu(toolMenu);

    std::cout << "Acabo crear menu" << std::endl;


}

void Window::openFile()
{

    fileOpened = QFileDialog::getOpenFileName(
                this
                ,tr("Open File"),"",
                "All files(*.*);;Text File(*.txt)"
                );
    QMessageBox::information(this,tr("File Name"),fileOpened);

//    if (!fileName.isEmpty())
//        addressWidget->readFromFile(fileName);
}

void Window::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
//    if (!fileName.isEmpty())
//        addressWidget->writeToFile(fileName);
}

void Window::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

    if (!indexes.isEmpty()) {
        removeAct->setEnabled(true);
        editAct->setEnabled(true);
    } else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}
