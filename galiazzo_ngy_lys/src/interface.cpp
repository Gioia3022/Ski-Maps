#include "interface.h"

interface::interface(Graphe* station_ski)
{
    les_arcs=station_ski;
    m_profil_principal=""

}

interface::~interface()
{
    delete les_arcs;
}
void interface::menu()
{
    int choix;

    do
    {
        if(m_profil_principal!="")//
            std::cout << "votre profil : " << m_profil_principal << " preference :"<<"//vaudrait mieux qu'il y ait marquer l option plutot que le num de l option=>";
        else
            std::cout<<"Vous n'etes pas conneceter"<<std::endl;

        std::ifstream profil_type(m_profil_principal);
        std::string type;
        profil_type >> m_type_profil;
        std::cout << m_type_profil;

        std::cout<<std::endl;
        std::cout<<"1: Informations sur le fichier"<<std::endl<<"2: Informations sur sommet/arc"<<std::endl<<"3: Obtenir tous les trajet possible depuis un sommet"<<std::endl;
        std::cout<< "4: Trajets le plus rapide entre deux sommet"<<std::endl<<"5: Profil"<<std::endl << "6: Quitter" << std::endl;

        std::cin>>choix;
        std::cout<<std::endl;
        switch (choix)
        {
        case 1:
        {
           les_arcs->afficher_info();
            this->menu();
            break;
        }
        case 2:
        {
            int choixArcSommet = 0;
            std::cout << "1.informations sur sommets" << std::endl << "2.informations sur arcs "<<std::endl;
            do
            {
                std::cin >> choixArcSommet;
                switch (choixArcSommet)
                {
                case 1 :
                {
                    int choixSommet = 0;
                    std::cout <<std::endl<< "Veuillez saisir le numero du sommet : ";
                    std::cin >> choixSommet;
                    std::cout<<std::endl;
                  les_arcs->afficher_info_sommet(choixSommet);
                    this->menu();
                    break;
                }
                case 2 :
                {
                    int choixArc = 0;
                    std::cout<<std::endl<<"Quel arc precis voulez vous verifier? ";
                    std::cin >> choixArc;
                    les_arcs->afficher_info_Arc(choixArc);
                    this->menu();
                    break;
                }
                default :
                {
                    std::cout<< std::endl << "Veuillez saisir un nombre valide merci" << std::endl;
                    break;
                }
                }
            }
            while (choixArcSommet < 1 || choixArcSommet > 2);
            this->menu();
            break;
        }
        case 3:
        {
            int id_station_depart;
            int choix_algo;
            std::cout<<"1.Obtenir tous les chemins les plus rapides (Djisktra)"<<std::endl;
            std::cout<<"2.Obtenir tous les chemins qui comporte le moins de trajet (BFS)"<<std::endl;
            std::cin>>choix_algo;
            std::cout<<"choisissez une station de depart parmi les "<<m_ordre<<" stations : ";
            std::cin>>id_station_depart;
            les_arcs->afficher_tous_les_chemins(id_station_depart,choix_algo);
            this->menu();
            break;
        }
        case 4:
        {
            int id_station_depart;
            int id_station_final;

            std::cout<<"profil:"<<m_type_profil<<std::endl;

            int option;
            if(m_profil_principal=="")
                option=0;
            if(m_profil_principal!="")
                option=m_type_profil;
            std::cout<<std::endl;
            if(option)
                std::cout<<"ATTENTION: Parfois il vous faudra faire preuve de courage ou de patience"<<std::endl<<"car parfois il n'y a qu'une issue possible et la technologie n'y pourra rien"<<std::endl;

            this->calculer_interet_des_trajets(option);
            std::cout<<std::endl;
            std::cout<<"choisissez une station de depart parmi les "<<m_ordre<<" stations"<<std::endl;
            std::cin>>id_station_depart;
            std::cout<<"choisissez une station d'arriver parmi les "<<m_ordre-1<<" stations restantes"<<std::endl;
            std::cin>>id_station_final;
            std::cout<<std::endl;
            std::cout<<"\t       [ "<<id_station_depart<<" ]"<<std::endl;
            if((id_station_depart!=6) && (id_station_depart!=28) && (id_station_depart!=29))
                this->dijkstra(this->get_station(id_station_depart),this->get_station(id_station_final),option);
            else
                std::cout<< "Il n'as pas de successeurs. "<<std::endl;
            std::cout<<std::endl;
            this->reset();


            this->menu();
            break;
        }

        case 5 :
        {

            edit(profil_principal);
            this->menu();
            break;
        }

        case 6 :
        {
            exit(0);

            break;
        }


        default :
        {
            std::cout << "Veuillez saisir un nombre valide" << std::endl;
        }
        }
    }
    while (choix != 2);
}
    void interface::edit_user()
    {
        system("cls");

    int menu_edit;

    std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
    std::cout <<"6.Quitter"<<std::endl;
    do
    {
        std::cin >> menu_edit;

        switch (menu_edit)
        {
        case 1 :
        {
            std::vector<std::string> vector_profil;
            remplir_vector_profil(vector_profil);

            for (auto const& elem : vector_profil)
            {

                std::cout << elem << std::endl;
            }

            std::string profil;
            std::cout << "veuillez entrer le nom du profil : ";
            std::cin >> profil;

            bool test_existance_profil = false;

            for (auto const&elem : vector_profil)
            {
                if (elem == profil)
                {
                    test_existance_profil = true;
                    m_profil_principal = profil;
                }
            }

            if (test_existance_profil == true)
            {
                std::cout << "connexion" << std::endl;
            }
            else
            {
                std::cout << "profil non trouve" << std::endl;
            }

            return;

            break;
        }

        case 2 :
        {
            std::ifstream lp("liste_profil.txt");
            if (lp)
            {
                std::string profil;
                std::cout << "veuillez saisir votre nom : ";
                std::cin >> profil;

                bool test_profil_non_doublon = false; // booléen verif si pas doublon profil

                std::vector<std::string> vector_profil;
                remplir_vector_profil(vector_profil);

                for (auto const& elem : vector_profil)
                {
                    std::cout << elem << std::endl;
                }

                for (auto const& elem : vector_profil)
                {
                    if (elem == profil)
                    {
                        test_profil_non_doublon = true;
                    }
                }

                if (test_profil_non_doublon == true)
                {
                    std::cout << "profil deja existant" << std::endl;
                }
                else
                {
                    vector_profil.push_back(profil);

                    std::ofstream lpp;
                    lpp.open("liste_profil.txt", std::ios::out);

                    for (auto const& elem : vector_profil)
                    {
                        lpp << elem << std::endl;
                    }

                    std::cout << "1.plus de monte" << std::endl << "2.plus de descente" << std::endl << "3.debutant" << std::endl << "4.expert" << std::endl << "5.plus de piste" << std::endl << "6.vertige" << std::endl << "7.claustrophobe" << std::endl;

                    int type;
                    std::cout << "veuillez entrer votre preference : ";
                    std::cin >> type;

                    std::ofstream creation;
                    creation.open(profil);
                    if (creation)
                    {
                        creation << type << std::endl;
                    }
                    else
                    {
                        std::cerr << "ERREUR : CREATION PROFIL SELECTION PREFERENCE" << std::endl;
                    }

                    std::cout << "profil ajouté" << std::endl;

                    lpp.close();

                    this->menu();

                    return;
                }
            }
            else
            {
                std::cerr << "ERREUR OUVERTURE LISTE PROFIL" << std::endl;
            }


            break;
        }

        case 3 :
        {
            std::ifstream lp("liste_profil.txt");
            if (lp)
            {
                std::vector<std::string> vector_profil;
                remplir_vector_profil(vector_profil);

                for (auto const& elem : vector_profil)
                {
                    if(elem!="")
                        std::cout << elem << std::endl;
                }

                std::string profil;
                std::cout << "veuillez saisir le nom du profil a supprimer : ";
                std::cin >> profil;

                bool test_existance_profil = false;

                std::vector<std::string>::iterator it;

                for (it = vector_profil.begin(); it < vector_profil.end(); it++)
                {
                    if (*it == profil)
                    {
                        test_existance_profil = true;
                        vector_profil.erase(it);
                        remove(profil.c_str());
                    }
                }

                if (test_existance_profil == true)
                {
                    std::ofstream lpp;
                    lpp.open("liste_profil.txt", std::ios::out);

                    for (auto const& elem : vector_profil)
                    {
                        lpp << elem << std::endl;
                    }

                    std::cout << "profil supprime" << std::endl;
                }
                else
                {
                    std::cout << "profil non existant" << std::endl;
                }

                lp.close();
            }
            else
            {
                std::cerr << "ERREUR OUVERTURE LISTE PROFIL" << std::endl;
            }

            return;

            break;
        }

        case 4 :
        {
            std::ifstream p(profil_principal);
            if (p)
            {
                std::string interet;
                p >> interet;

                std::cout << interet << std::endl;
            }
            else
            {
                std::cerr << "ERREUR : OUVERTURE PROFIL" << std::endl;
            }

            return;

            break;
        }

        case 6 :
        {
            return;

            break;
        }
        case 5 :
        {
            m_profil_principal="";
            this->menu(profil_principal);
        }

        default :
        {
            std::cout << "Veuillez saisir un nombre valide" << std::endl;

            break;
        }
        }
    }
    while (menu_edit != 6);
}


void interface::remplir_vector_profil(std::vector<std::string> &vector_profil)
{
    std::ifstream lp("liste_profil.txt");
    if (lp)
    {
        do
        {
            std::string identifiant;
            getline(lp, identifiant);
            vector_profil.push_back(identifiant);
        }
        while(!lp.eof());

        lp.close();
    }
    else
    {
        std::cerr << "ERREUR : ouverture liste profil pour remplir vector temporaire" << std::endl;
    }
}
