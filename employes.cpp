#include "employes.h"

employes::employes()
{

}

employes::employes(QString nom,QString prenom,int cin,QString sexe,int tel,QString fonction,float salaire=0)
{
    this->nom=nom;
    this->prenom=prenom;
    this->cin=cin;
    this->sexe=sexe;
    this->tel=tel;
    this->fonction=fonction;
    this->salaire=salaire;
}
