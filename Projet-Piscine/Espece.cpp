#include"Espece.h"


Espece::Espece():m_nombre_individus(0),m_capacite_de_portage(0),m_rythme_de_croissance(0),m_nom("Espece_sans_nom")
{

}


Espece::~Espece()
{

}

///GETTERS
int Espece::getcapacite_de_portage()
{
    return m_capacite_de_portage;
}
int Espece::getnombre_individus()
{
    return m_nombre_individus;
}
float Espece::getrythme_de_croissance()
{
    return m_rythme_de_croissance;
}
std::string Espece::getnom()
{
    return m_nom;
}
///SETTERS
void Espece::setcapacite_de_portage(int capacite_de_portage)
{
    m_capacite_de_portage=capacite_de_portage;
}
void Espece::setnombre_individus(int nombre_individus)
{
    m_nombre_individus=nombre_individus;
}
void Espece::setrythme_de_croissance(float rythme_de_croissance)
{
    m_rythme_de_croissance=rythme_de_croissance;
}
void Espece::setnom(std::string nom)
{
    m_nom=nom;
}
