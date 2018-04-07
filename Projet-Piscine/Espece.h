#ifndef ESPECE_H_INCLUDED
#define ESPECE_H_INCLUDED
#include<string>
#include"graph.h"

class Espece : public Vertex
{
protected:
    int m_nombre_individus; /// ou nombre de kilos d'individus (biomasse)
    int m_capacite_de_portage;
    float m_rythme_de_croissance;
    std::string m_nom;
public:
    Espece();
    ~Espece();

///GETTER
    int getnombre_individus();
    int getcapacite_de_portage();
    float getrythme_de_croissance();
    std::string getnom();

///SETTER
    void setnombre_individus(int nombre_individus);
    void setcapacite_de_portage(int capacite_de_portage);
    void setrythme_de_croissance(float rythme_de_croissance);
    void setnom(std::string nom);
///METHODS
    void refreshnombre_individus(); ///refresh N en fonction de K et r
    void def_capacite_de_portage(std::vector<float>vecteur_decoefficient, std::vector<int>vecteur_des_nbr_individus_predecesseurs); ///fonction qui va seulement faire l'opération pout le K
};                                                                                      ///elle ne va pas chercher elle_meme les N des predeceseurs, il faudra lassocier a une autre methode

#endif // ESPECE_H_INCLUDED
