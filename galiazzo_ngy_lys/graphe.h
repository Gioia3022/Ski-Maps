#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "arcs.h"

// Représente un graphe oriente et pondere
class Graphe
{
private:
    /// Le réseau est constitué d'une collection de stations et de routes
    std::vector<Sommet*> m_stations; // Vecteur de sommets
    std::vector<Arc*> m_routes; // Vecteur d'aretes
    int m_ordre; //nbr de sommets
    int m_taille; //nombre d'aretes

public:
    Graphe(std::string nomFichier); //constructeur du graphe
    ~Graphe(); //destructeur du graphe

    //accesseurs
///retrouver une station grâce à son Id
    Sommet* get_station(int id);
    Sommet* get_sommet() const;
    int get_ordre();
///retrouver une route grâce à ses extrémités
    Arc* get_une_route(int id_dep,int id_dest);

    //methodes
///ALGO DIJKSTRA
    void dijkstra(Sommet* station_so,Sommet *destinatation,int option);
    void menu(std::string &profil_principal);
    void calculer_interet_des_trajets(int option);
    void afficherSommet();
    void reset();
    void afficher_chemin(std::vector<Arc*> &pcc);

///ALGO BFS
    void bfs(Sommet* So,Sommet* destination);

///AFFICHAGE
    void afficher_info();
    void afficher_info_sommet(int &choixSommet);
     void afficher_info_Arc(int &choixArc);
    void afficher_plus_court_chemin(int &id_station_depart,int &id_station_final,int &option, int& choix_algo);
    void afficher_tous_les_chemins(int &id_station_depart,int &choix_algo);
};

#endif // GRAPHE_H_INCLUDED
