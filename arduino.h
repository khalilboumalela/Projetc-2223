#ifndef ARDUINO_H
#define ARDUINO_H


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlError>

class Arduino
{
public:     //méthodes de la classe Arduino
    Arduino();
    int connect_arduino(); // permet de connecter le PC à Arduino
    int close_arduino(); // permet de femer la connexion
    int write_to_arduino( QString ); // envoyer des données vers arduino
    int write_to_arduino2( QByteArray );
    QByteArray read_from_arduino();  //recevoir des données de la carte Arduino
    QSerialPort* getserial();   // accesseur
    QString getarduino_port_name();
    //Equip_ard
    void burn(   );
    QString chercher(int code);
     QByteArray getdata();
private:
QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de données, etc.)
//et des fonctions (envoi, lecture de réception,…) sur ce qu’est une voie série pour Arduino.
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_product_id=67;
QString arduino_port_name;
bool arduino_is_available;
QByteArray data;  // contenant les données lues à partir d'Arduino
QString serialbuffer;
};






#endif // ARDUINO_H
