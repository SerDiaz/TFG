#ifndef REORDEN_H
#define REORDEN_H



#include <QWidget>
#include <QGridLayout>
#include <QDialog>




class QDataWidgetMapper;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QGroupBox;
class QStandardItemModel;
class QTextEdit;
class Writing;


class Reorden : public QWidget
{


public:
    Reorden(int ta, int nav, int npi, QString fe, QString *noV, QString *ori, QString *des, QString *pi, float *ini, float *fin, QString *avi, int taAr, QWidget *parent = 0);
    void crear(QVBoxLayout *layoutGeneral);
//    void algoritmo(QString vuelo,float retraso);
    int busquedaPosicion(QString vuelo);
    QString busquedaVueloPilotoSiguiente(QString vuelo);
    QString busquedaVueloAvionSiguiente(QString vuelo);
    void createHorizontalGroupBox();
    void menu(QHBoxLayout *layout);
    void busquedaPilotoSustitucion(int posicionActual, int idCaminoPadre);
    void busquedaAvionSustitucion(int posicionActual, int idCaminoPadre);
    void busquedaPilotoYAvionSustitucion(int posicionActual,int idCaminoPadre);
    void retrasarAviones(int posicionActual, int idCaminoPadre);
    bool pilotoPuedeVolver(int posicionActual,int posicionDondeVa);
    bool avionPuedeVolver(int posicionActual,int posicionDondeVa);
    bool puedeVolverMasRetraso(int posicionActual,int posicionDondeVa, float retraso);
    int sePuedeCancelar(int posicionActual,int posicionDondeVa);


public slots:
    void sloto();
    void algoritmo(QString vuelo, float retraso);



private:

    //COSTE
    int *listaAbierta;
    int *listaCerrada;
    int caminosComprobados;
    int numeroDeElementosEnListaAbierta;
    int numeroDeElementosEnListaCerrada;
    int *costF;
    int *costeG;
    QStringList *avionesRutaSeguida;
    QString *avionesLista;

    int *tiposOperacion;
    int *avionOperacion;
    int *listaDondeEsta;


    float retraso;



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

    float *retrasoIndividual;

//    SI DESPUES DE REALIZAR UN CAMBIO DE VUELO O PILOTO HAY QUE SEGUIR CON EL ALGORITMO
//    QString *nomVueloAvionUsado;
//    QString *origenAvionUsado;
//    QString *destinoAvionUsado;
//    float *hInicioAvionUsado;
//    float *hFinAvionUsado;
//    int numAvionesUsados;

    Writing *writing;



    void algoritmoComun(QString vueloPadre, QString vueloHijo);
    void insertarListaAbierta(QString vuelo, int i, int posVueloAnterior);
    int borrarListaAbierta(int devolver);
    void nuevoEnListaCerrada(QString vuelo, QString vueloAnterior, int idCaminoPadre);
    void insertarListaCerrada(int id);
    int devolverCostF(int posicion);
    void insertarCostF(int posicion, int coste);
    void insertar3enLista(QString vuelo, int operacionAnterior, QString vueloAnterior);
    int buscarVuelo(QString vuelo,int operacionAnterior);
//    void sustituirAbierta(int id1,int id2);
//    void sustituirCerrada(int id1,int id2);
    void reordenAbierta(int id);
    void reordenCerrada(int id);
    int posicionCerrada(int id);
    int posicionAbierta(int id);
    void colocarAscendenteAbierta(int pos);
    void colocarAscendenteCerrada(int pos);
    void insertarRutaSeguida(int posVueloAnterior);
    void calcularRetraso(int posVueloAnterior, int posActual, int posAnterior);






};


#endif // REORDEN_H
