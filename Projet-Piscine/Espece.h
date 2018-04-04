#ifndef ESPECE_H_INCLUDED
#define ESPECE_H_INCLUDED
#include<string>
#include"graph.h"

class Espece : public Vertex
{
private:
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

};

#endif // ESPECE_H_INCLUDED
