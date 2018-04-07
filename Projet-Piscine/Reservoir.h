#ifndef RESERVOIR_H_INCLUDED
#define RESERVOIR_H_INCLUDED
#include"graph.h"

class Reservoir: public Vertex   ///Completement identique à class Espece pour linstant...
{
private:
    int m_biomasse;
    int m_capacite_de_portage;
    float m_rythme_de_croissance;
    std::string m_nom;
public:
    Reservoir();
    ~Reservoir();

///GETTER
    int getbiomasse();
    int getcapacite_de_portage();
    float getrythme_de_croissance();
    std::string getnom();

///SETTER
    void setbiomasse(int biomasse);
    void setcapacite_de_portage(int capacite_de_portage);
    void setrythme_de_croissance(float rythme_de_croissance);
    void setnom(std::string nom);
///METHODS
    void refreshnombre_individus(); ///refresh N en fonction de K et r
    void def_capacite_de_portage(std::vector<float>vecteur_decoefficient, std::vector<int>vecteur_des_nbr_individus_predecesseurs); ///fonction qui va seulement faire l'opération pout le K
};                                                                                      ///elle ne va pas chercher elle_meme les N des predeceseurs, il faudra lassocier a une autre methode



#endif // RESERVOIR_H_INCLUDED
