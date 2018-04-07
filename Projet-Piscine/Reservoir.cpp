#include"Reservoir.h"


Reservoir::Reservoir():m_biomasse(0),m_capacite_de_portage(0),m_rythme_de_croissance(0),m_nom("Reservoir_sans_nom")
{

}

Reservoir::~Reservoir()
{

}



///GETTERS
int Reservoir::getcapacite_de_portage()
{
    return m_capacite_de_portage;
}
int Reservoir::getbiomasse()
{
    return m_biomasse;
}
float Reservoir::getrythme_de_croissance()
{
    return m_rythme_de_croissance;
}
std::string Reservoir::getnom()
{
    return m_nom;
}
///SETTERS
void Reservoir::setcapacite_de_portage(int capacite_de_portage)
{
    m_capacite_de_portage=capacite_de_portage;
}
void Reservoir::setbiomasse(int biomasse)
{
    m_biomasse=biomasse;
}
void Reservoir::setrythme_de_croissance(float rythme_de_croissance)
{
    m_rythme_de_croissance=rythme_de_croissance;
}
void Reservoir::setnom(std::string nom)
{
    m_nom=nom;
}
///METHODS
void Reservoir::refreshnombre_individus()
{
    m_biomasse=m_biomasse+m_rythme_de_croissance*m_biomasse*(1-(m_biomasse/m_capacite_de_portage));
}
void Reservoir::def_capacite_de_portage(std::vector<float>vecteur_decoefficient, std::vector<int>vecteur_des_nbr_individus_predecesseurs)
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
