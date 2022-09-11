#ifndef INTERFACE_H
#define INTERFACE_H
#include "graphe.h"

class interface
{
    public:
        interface(Graphe* station_ski);
        ~interface();
        void menu();
        void edit_user();
        void remplir_vector_profil(std::vector<std::string> &vector_profil);




    private:
        std::string m_profil_principal;
        Graphe* les_arcs;
        int m_type_profil=0;


};

#endif // INTERFACE_H
