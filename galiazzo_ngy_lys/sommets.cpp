#include "sommets.h"

//Constructeur
Sommet::Sommet(int id, std::string nom, double altitude)
{
    m_id = id;
    m_nom = nom;
    m_altitude = altitude;
}
//Destructeur
Sommet::~Sommet() {}

//Accesseurs
int Sommet::get_id()
{
    return m_id;
}
bool Sommet::get_couleur()
{
    return m_couleur;
}
void Sommet::set_couleur(bool col)
{
    m_couleur=col;
}

std::string Sommet::get_nom() const
{
    return m_nom;
}

double Sommet::get_altitude() const
{
    return m_altitude;
}

int Sommet::getNbrArc()
{
    return m_adj.size();
}

//methode d'affichage des informations du sommet
void Sommet::affichageTxT()
    {
            std::cout<<m_id<<"\t"<<m_nom<<"\t"<<m_altitude<<std::endl;
    }
