#ifndef INTERFACE_H
#define INTERFACE_H
#include "graphe.h"

//classe pour la sauvegarde  des informaations du skieur
class interface
{
    public:
        interface(Graphe* station_ski); //constructeur
        ~interface(); //destructeur

        //methodes
        void menu();
        void edit_user();
        void remplir_vector_profil(std::vector<std::string> &vector_profil);
        void afficher_preference();

    private:
        std::string m_profil_principal; //nom skieur
        Graphe* les_arcs;
        int m_type_profil=0; //option du skieur
};

#endif // INTERFACE_H
