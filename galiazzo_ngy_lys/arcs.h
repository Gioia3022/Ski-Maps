#ifndef ARCS_H_INCLUDED
#define ARCS_H_INCLUDED
#include "sommets.h"

//Représente une arete pondérée dans un graphe
class Arc
{
///les trajets sont a sens unique, une station de depart et une destination
private:
    Sommet* m_depart;       //Comme le graphe est oriente l'arete allant de debut a fin
    Sommet* m_destination; //n'est pas egale a l'arete allant de fin a debut
    int m_id; // identifiant de l'arc
    std::string m_nom; //nom de l'arc
    std::string m_type; //type de l'arc (TS, N, etc.)
    int m_spe; //specificité pour les options
    int m_t0; //temps de depart
    float m_temps; //temps en m*min^-1
    float m_duree; //poids
    int m_sec; //representation du poids en h::min::sec
    int m_min;
    int m_h;
    double m_interet;//pour le calcul des priorites une fois l'option choisie



public:
    Arc(int id, std::string nom, std::string type, Sommet* depart, Sommet* dest, int spe, int t0, float temps); //constructeur
    ~Arc(); //destructeur

    //accesseurs
    Sommet* getDepart();
    Sommet* getDest();
    float getDuree();
    int getSec();
    int getMin();
    int getH();
    int get_id();
    std::string get_nom();
    std::string get_type();
    double get_interet();
    int getSpe();

    void set_interet(double val);

    //methodes
    //affichage
    void affichageTxT();
    void afficherArc_info();
    void afficherArc();
};

#endif // ARCS_H_INCLUDED
