#include "convertirhora.h"

QString ConvertirHora::aString(float time){

    int horaInt = (int)time;
    float minutosfloat = (time-horaInt) * 100;
//    60/10=3/5. CONVERSION DE DECIMAL A HEXADECIMAL(MINUTOS)
    int minutosInt=minutosfloat*3/5;

    QString horaString=QString::number(horaInt);
    if (horaString=="0")
        horaString="00";

    QString minutosString=QString::number(minutosInt);
//      SI TIENE SOLO UNA CIFRA
    switch (minutosInt) {
        case 0:
            minutosString="00";
        break;
        case 1:
            minutosString="01";
        break;
        case 2:
            minutosString="02";
        break;
        case 3:
            minutosString="03";
        break;
        case 4:
            minutosString="04";
        break;
        case 5:
            minutosString="05";
        break;
        case 6:
            minutosString="06";
        break;
        case 7:
            minutosString="07";
        break;
        case 8:
            minutosString="08";
        break;
        case 9:
            minutosString="09";
        break;
    }

    QString devolver = horaString + ":" + minutosString;

    return devolver;
}

float ConvertirHora::aFloat(QString *hora)
{
    float a = hora->split(":")[0].toFloat();
    float b = (hora->split(":")[1].toFloat() /100); /*100 conversion, 100 es decimal y 60 es minutos*/

//    10/60=5/3
    b=b*5/3;

    return (b + a);
}
