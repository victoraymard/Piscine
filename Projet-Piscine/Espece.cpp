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
///METHODS
void Espece::refreshnombre_individus()
{
    m_nombre_individus=m_nombre_individus+m_rythme_de_croissance*m_nombre_individus*(1-(m_nombre_individus/m_capacite_de_portage));
}
void Espece::def_capacite_de_portage(std::vector<float>vecteur_decoefficient, std::vector<int>vecteur_des_nbr_individus_predecesseurs)
{
    m_capacite_de_portage=0;
    if (vecteur_decoefficient.size()==m_in.size() && vecteur_des_nbr_individus_predecesseurs.size()==m_in.size())
    {
        for(unsigned int k=0; k<vecteur_decoefficient.size(); k++)
        {
            m_capacite_de_portage=m_capacite_de_portage+vecteur_decoefficient[k]*vecteur_des_nbr_individus_predecesseurs[k];
        }
    }
}
