#ifndef RESERVOIR_H_INCLUDED
#define RESERVOIR_H_INCLUDED
#include"graph.h"

class Reservoir: public Vertex   ///Completement identique à class Espece pour linstant...
{
private:
    int m_nombre_individus;
    int m_capacite_de_portage;
    float m_rythme_de_croissance;
    std::string m_nom;
public:
    Reservoir();
    ~Reservoir();

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


#endif // RESERVOIR_H_INCLUDED
