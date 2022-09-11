#ifndef SOMMETS_H_INCLUDED
#define SOMMETS_H_INCLUDED
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include<stack>
#include <map>
#include<bits/stdc++.h>
#include <iterator>

class Sommet
{
private:
    /// Données spécifiques du sommet
    int m_id;// Indice numérique pour l'affichage
    std::string m_nom; // nom de la station
    double m_altitude; // altitude de la station
    bool m_couleur; //si on est deja passe par la ou pas
    std::vector<Sommet> m_adj;

public:
    Sommet(int id, std::string nom, double altitude); //constructeur
    ~Sommet(); //destructeur

    //accesseurs
    int get_id();
    bool get_couleur();
    std::string get_nom() const;
    double get_altitude()const;
    int getNbrArc();
    std::vector<Sommet> getAdj();

    void set_couleur(bool col);

    //methode
    //affichage
    void affichageTxT();
};

#endif // SOMMETS_H_INCLUDED
