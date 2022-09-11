
#include "interface.h"

interface::interface(Graphe* station_ski)
    {
        les_arcs=station_ski;
        m_profil_principal="";

    }

interface::~interface()
    {
        delete les_arcs;
    }
void interface::menu()
{
    int choix;
    int menu;
    std::ifstream profil_type(m_profil_principal);
    std::string type;
    profil_type >> m_type_profil;

    do
    {
        if(m_profil_principal!="")// profil principal = rien : on est connecté en tant que rien => aucune preference
        {
            std::cout<<std::endl;
            std::cout << "Vous etes connecete au profil : " << m_profil_principal <<std::endl;
            std::cout<< "\toption : ";
            this->afficher_preference();
        }

        std::cout<<std::endl;

        std::cout<<"1: Creez ou accedez a votre profil"<<std::endl<<"2: Informations sur le fichier"<<std::endl<<"3: Informations sur sommet/arc"<<std::endl<<"4: Obtenir tous les trajet possible depuis un sommet en BFS ou Dijkstra"<<std::endl;
        std::cout<< "5: Trajets le plus rapide entre deux sommet soit en terme de temps ou de stations"<<std::endl<<"6: Trajet avec options"<<std::endl << "7: Quitter" << std::endl;

        std::cin>>choix;
        std::cout<<std::endl;
        if(std::cin.fail())
        {
            system("cls");
            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;

            std::cin.clear();
            std::cin.seekg(0, std::ios::end);
            if(!std::cin.fail())
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
            }
            else
            {
                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
            }
        }
        else
        {
            switch (choix)
            {
            case 1:
            {
                this->edit_user();

                std::cout<<std::endl;
                std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                std::cin>>menu;
                if(std::cin.fail())
                {
                    system("cls");
                    std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                    std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
                    std::cout <<"6.Revenir au menu principal"<<std::endl;
                    std::cin.clear();
                    std::cin.seekg(0, std::ios::end);
                    if(!std::cin.fail())
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                    }
                    else
                    {
                        std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                    }
                }
                else
                {
                    if(menu==0)
                        exit(0);
                    else
                    {
                        system("cls");
                        this->menu();
                    }

                }
                break;
            }
            case 2:
            {
                les_arcs->afficher_info();

                std::cout<<std::endl;
                std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                std::cin>>menu;
                if(std::cin.fail())
                {
                    system("cls");
                    std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                    std::cin.clear();
                    std::cin.seekg(0, std::ios::end);
                    if(!std::cin.fail())
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                    }
                    else
                    {
                        std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                    }
                }
                else
                {
                    if(menu==0)
                        exit(0);
                    else
                    {
                        system("cls");
                        this->menu();
                    }
                }
                break;
            }
            case 3:
            {
                int choixArcSommet = 0;
                std::cout << "1.informations sur sommets" << std::endl << "2.informations sur arcs "<<std::endl;
                do
                {
                    std::cin >> choixArcSommet;
                    if(std::cin.fail())
                    {
                        system("cls");
                        std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                        std::cout << "1.informations sur sommets" << std::endl << "2.informations sur arcs "<<std::endl;
                        std::cin.clear();
                        std::cin.seekg(0, std::ios::end);
                        if(!std::cin.fail())
                        {
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                        }
                        else
                        {
                            std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                        }
                    }
                    else
                    {
                        switch (choixArcSommet)
                        {
                        case 1 :
                        {
                            int choixSommet = 0;
                            std::cout <<std::endl<< "Veuillez saisir le numero du sommet : ";
                            std::cin >> choixSommet;
                            std::cout<<std::endl;
                            les_arcs->afficher_info_sommet(choixSommet);
                            std::cout<<std::endl;
                            std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                            std::cin>>menu;
                            if(std::cin.fail())
                            {
                                system("cls");
                                std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                                std::cin.clear();
                                std::cin.seekg(0, std::ios::end);
                                if(!std::cin.fail())
                                {
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                                }
                                else
                                {
                                    std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                                }
                            }
                            else
                            {
                                if(menu==0)
                                    exit(0);
                                else
                                {
                                    system("cls");
                                    this->menu();
                                }
                            }
                            break;
                        }
                        case 2 :
                        {
                            int choixArc = 0;
                            std::cout<<std::endl<<"Quel arc precis voulez vous verifier? ";
                            std::cin >> choixArc;
                            les_arcs->afficher_info_Arc(choixArc);
                            std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                            std::cin>>menu;
                            if(std::cin.fail())
                            {
                                system("cls");
                                std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                                std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
                                std::cout <<"6.Revenir au menu principal"<<std::endl;
                                std::cin.clear();
                                std::cin.seekg(0, std::ios::end);
                                if(!std::cin.fail())
                                {
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                                }
                                else
                                {
                                    std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                                }
                            }
                            else
                            {
                                if(menu==0)
                                    exit(0);
                                else
                                {
                                    system("cls");
                                    this->menu();
                                }
                            }
                            break;
                        }
                        default :
                        {
                            std::cout<< std::endl << "Veuillez saisir un nombre valide merci" << std::endl;
                            break;
                        }
                        }
                    }
                }
                while (choixArcSommet < 1 || choixArcSommet > 2);
                std::cout<<std::endl;
                std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                std::cin>>menu;
                if(std::cin.fail())
                {
                    system("cls");
                    std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                    std::cin.clear();
                    std::cin.seekg(0, std::ios::end);
                    if(!std::cin.fail())
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                    }
                    else
                    {
                        std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                    }
                }
                else
                {
                    if(menu==0)
                        exit(0);
                    else
                    {
                        system("cls");
                        this->menu();
                    }
                }
                break;
            }
            case 4:
            {
                int id_station_depart;
                int choix_algo;
                std::cout<<"1.Obtenir tous les chemins les plus rapides (Djisktra)"<<std::endl;
                std::cout<<"2.Obtenir tous les chemins qui comporte le moins de trajet (BFS)"<<std::endl;
                std::cin>>choix_algo;
                if(choix_algo==1 || choix_algo==2)
                {

                    std::cout<<"choisissez une station de depart parmi les "<<les_arcs->get_ordre()<<" stations : ";
                    std::cin>>id_station_depart;
                    if(std::cin.fail())
                    {
                        system("cls");
                        std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                        std::cin.clear();
                        std::cin.seekg(0, std::ios::end);
                        if(!std::cin.fail())
                        {
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                        }
                        else
                        {
                            std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                        }
                    }
                    else
                    {

                        les_arcs->afficher_tous_les_chemins(id_station_depart,choix_algo);
                        std::cout<<std::endl;
                        std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                        std::cin>>menu;
                        if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                        else
                        {
                            if(menu==0)
                                exit(0);
                            else
                            {
                                system("cls");
                                this->menu();
                            }
                        }
                    }
                }
                else
                {
                    system("cls");
                    std::cout<< "Mauvaise saisie veuillez recomencer"<<std::endl;
                }
                break;
            }
            case 5:
            {
                int id_station_depart;
                int id_station_final;

                int option;
                if(m_profil_principal=="")
                    option=0;
                else
                    option=m_type_profil;
                std::cout<<std::endl;
                int choix_algo;
                std::cout<<"1.Obtenir tous les chemins les plus rapides (Djisktra)"<<std::endl;
                std::cout<<"2.Obtenir tous les chemins qui comporte le moins de trajet (BFS)"<<std::endl;
                std::cin>>choix_algo;
                if(choix_algo==1 || choix_algo==2)
                {
                    if(std::cin.fail())
                    {
                        system("cls");
                        std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                        std::cin.clear();
                        std::cin.seekg(0, std::ios::end);
                        if(!std::cin.fail())
                        {
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                        }
                        else
                        {
                            std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                        }
                    }
                    else
                    {
                        if(option)
                            std::cout<<"ATTENTION: Malgr"<<(char)0x82<<" vos otions, parfois il vous faudra faire preuve de courage ou de patience"<<std::endl<<"car parfois il n'y a qu'une issue possible et la technologie n'y pourra rien"<<std::endl;

                        std::cout<<std::endl;
                        std::cout<<"choisissez une station de depart parmi les "<<les_arcs->get_ordre()<<" stations"<<std::endl;
                        std::cin>>id_station_depart;
                        if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                        else
                        {
                            std::cout<<"choisissez une station d'arriver parmi les "<<les_arcs->get_ordre()-1<<" stations restantes"<<std::endl;
                            std::cin>>id_station_final;
                            if(std::cin.fail())
                            {
                                system("cls");
                                std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                                std::cin.clear();
                                std::cin.seekg(0, std::ios::end);
                                if(!std::cin.fail())
                                {
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                                }
                                else
                                {
                                    std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                                }
                            }
                            else
                            {
                                les_arcs->afficher_plus_court_chemin(id_station_depart,id_station_final,option, choix_algo);


                        std::cout<<std::endl;
                        std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                        std::cin>>menu;
                        if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                        else
                        {
                            if(menu==0)
                                exit(0);
                            else
                            {
                                system("cls");
                                this->menu();
                            }
                        }
                        }
                        }
                    }
                }
                else
                {
                    system("cls");
                    std::cout<< "Mauvaise saisie veuillez recomencer"<<std::endl;
                }
                break;
            }

            case 6 :
            {
                int id_station_depart;
                int id_station_final;
                int option;
                int choix_algo;
                std::cout<<"1.Obtenir tous les chemins les plus rapides (Djisktra)"<<std::endl;
                std::cout<<"2.Obtenir tous les chemins qui comporte le moins de trajet (BFS)"<<std::endl;
                std::cin>>choix_algo;
                if(choix_algo==1 || choix_algo==2)
                {
                std::cout<<std::endl;
                std::cout << "1.Plus de monte" << std::endl << "2.Plus de descente" << std::endl << "3.Debutant" << std::endl << "4.Expert" << std::endl << "5.Exotique" << std::endl << "6.Vertige" << std::endl << "7.Claustrophobe" << std::endl;
                std::cin>>option;
                while(option!=0 && option<8)
                {
                if(std::cin.fail())
                    {
                        system("cls");
                        std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                        std::cin.clear();
                        std::cin.seekg(0, std::ios::end);
                        if(!std::cin.fail())
                        {
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                        }
                        else
                        {
                            std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                        }
                    }
                    else
                    {

                std::cout<<"choisissez une station de depart parmi les "<<les_arcs->get_ordre()<<" stations"<<std::endl;
                std::cin>>id_station_depart;
                while(id_station_depart<38)

                {
                    if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                else
                {
                    std::cout<<"choisissez une station d'arriver parmi les "<<les_arcs->get_ordre()-1<<" stations restantes"<<std::endl;
                std::cin>>id_station_final;
                while(id_station_depart<37)
                {
                    if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                else
                {
                    les_arcs->afficher_plus_court_chemin(id_station_depart,id_station_final,option, choix_algo);
                std::cout<<std::endl;
                std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                std::cin>>menu;
                if(std::cin.fail())
                {
                    system("cls");
                    std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                    std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
                    std::cout <<"6.Revenir au menu principal"<<std::endl;
                    std::cin.clear();
                    std::cin.seekg(0, std::ios::end);
                    if(!std::cin.fail())
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                    }
                    else
                    {
                        std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                    }
                }
                else
                {
                    if(menu==0)
                        exit(0);
                    else
                    {
                        system("cls");
                        this->menu();
                    }
                }
                    }
                }
                }
                    }
                    }
                }
                }
                else
                {
                    system("cls");
                    std::cout<< "Mauvaise saisie veuillez recomencer"<<std::endl;
                    this->menu();
                }
                break;
            }

            case 7 :
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
    }
    while (choix != 6);
}
void interface::edit_user()
{
    int menu;
    int menu_edit;

    std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
    std::cout <<"6.Revenir au menu principal"<<std::endl;
    do
    {
        std::cin >> menu_edit;
        if(std::cin.fail())
        {
            system("cls");
            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
            std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
            std::cout <<"6.Revenir au menu principal"<<std::endl;
            std::cin.clear();
            std::cin.seekg(0, std::ios::end);
            if(!std::cin.fail())
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
            }
            else
            {
                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
            }
        }
        else
        {
            switch (menu_edit)
            {
            case 1 :
            {
                std::vector<std::string> vector_profil; // vector de string temporaire
                remplir_vector_profil(vector_profil); // on remplit ce vector a chaque fois => actualisation de la liste des profils

                std::string profil;
                std::cout << "Veuillez entrer le nom du profil : ";
                std::cin >> profil;

                bool test_existance_profil = false;

                for (auto const&elem : vector_profil) // on vérifie si le nom de profil existe dans la liste des profils
                {
                    if (elem == profil)
                    {
                        test_existance_profil = true; // si le profil existe m_profil_principal récupère le nom du profil
                        m_profil_principal = profil; // m_profil_principal peut ensuite avec le nom du profil, la preference du compte
                    }
                }

                if (test_existance_profil == true)
                {
                    std::cout << "Connexion" << std::endl;
                }
                else
                {
                    std::cout << "Profil non trouve" << std::endl;
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
                    std::cout << "Veuillez saisir votre nom : ";
                    std::cin >> profil;

                    bool test_profil_non_doublon = false; // booléen verif si pas doublon profil

                    std::vector<std::string> vector_profil; // recuperation des noms dans le vector temporaire
                    remplir_vector_profil(vector_profil);

                    for (auto const& elem : vector_profil) // on vérifie si le nouveau nom de profil existe
                    {
                        if (elem == profil)
                        {
                            test_profil_non_doublon = true;
                        }
                    }

                    if (test_profil_non_doublon == true) // empeche la creation de profil doublon
                    {
                        system("cls");
                        std::cout << "profil deja existant" << std::endl;
                        this->edit_user();
                    }
                    else
                    {
                        vector_profil.push_back(profil); // si le profil est un nouveau profil : on l'ajoute au vecteur temporaire

                        std::ofstream lpp;
                        lpp.open("liste_profil.txt", std::ios::out);

                        for (auto const& elem : vector_profil) // et on réécrit le fichier.txt avec tous les noms des profils : actualisation du fichier.txt
                        {
                            lpp << elem << std::endl;
                        }

                        std::cout << "1.Plus de monte" << std::endl << "2.Plus de descente" << std::endl << "3.Debutant" << std::endl << "4.Expert" << std::endl << "5.Exotique" << std::endl << "6.Vertige" << std::endl << "7.Claustrophobe" << std::endl;
                        int type;

                        std::cout << "veuillez entrer votre preference : ";
                        std::cin >> type; // on recupere la preference du nouveau profil
                        if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                            std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
                            std::cout <<"6.Quitter"<<std::endl;
                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                        else
                        {
                            std::ofstream creation;
                            creation.open(profil); // creation un fichier avec ecrit la preference : pour connaitre la preference de chaque profil on recupere ce fichier
                            if (creation)
                            {
                                creation << type << std::endl;
                            }
                            else
                            {
                                std::cerr << "ERREUR : CREATION PROFIL SELECTION PREFERENCE" << std::endl;
                            }

                            std::cout << "profil ajoute" << std::endl;

                            lpp.close();
                            system("cls");
                            this->menu();
                            return;
                        }
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
                    std::vector<std::string> vector_profil; // vector temporaire
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
                    bool test_profil_actuel = false;

                    std::vector<std::string>::iterator it;

                    if (m_profil_principal == profil) // on verifie si le profil actuel est le profil a supprimer
                    {
                        test_profil_actuel = true;
                    }

                    if (test_profil_actuel == true) // impossible de supprimer le profil si on est deja connecté : une deconnexion est nécessaire
                    {
                        std::cout << "veuillez vous deconnecter avant de supprimer votre compte" << std::endl;
                    }
                    else
                    {
                        for (it = vector_profil.begin(); it < vector_profil.end(); it++)
                        {
                            if (*it == profil) // on verifie ensuite que le profil à supprimer existe bien
                            {
                                test_existance_profil = true;
                                vector_profil.erase(it);
                                remove(profil.c_str()); // on supprime le fichier au nom du profil également
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
                std::ifstream p(m_profil_principal);
                if (p)
                {
                    int interet;
                    p >> interet;
                    std::cout<<std::endl;
                    std::cout << "Votre preference actuelle : ";

                    switch (interet)
                    {
                    case 1 :
                    {
                        std::cout << "Plus de monte ( aka: flemard )" << std::endl;
                        break;
                    }
                    case 2 :
                    {
                        std::cout << "Plus de descente( aka: super sportif )" << std::endl;
                        break;
                    }
                    case 3 :
                    {
                        std::cout << "Debutant" << std::endl;
                        break;
                    }
                    case 4 :
                    {
                        std::cout << "Expert" << std::endl;
                        break;
                    }
                    case 5 :
                    {
                        std::cout << "Exotique please" << std::endl;
                        break;
                    }
                    case 6 :
                    {
                        std::cout << "Je soufre le vertige" << std::endl;
                        break;
                    }
                    case 7 :
                    {
                        std::cout << "Je suis claustrophobe" << std::endl;
                        break;
                    }
                    }

                    std::cout << "1.Plus de monte" << std::endl << "2.Plus de descente" << std::endl << "3.Debutant" << std::endl << "4.Expert" << std::endl << "5.Exotique" << std::endl << "6.Vertige" << std::endl << "7.Claustrophobe" << std::endl;
                    int modif_interet = 0;
                    std::cout << "veuillez entrer votre nouvelle preference : ";

                    do
                    {
                        std::cin >> modif_interet;
                        if(std::cin.fail())
                        {
                            system("cls");
                            std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;

                            std::cin.clear();
                            std::cin.seekg(0, std::ios::end);
                            if(!std::cin.fail())
                            {
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                            }
                            else
                            {
                                std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                            }
                        }
                        else
                        {
                            switch (modif_interet)
                            {
                            case 1 :
                            {
                                modif_interet = 1;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            case 2 :
                            {
                                modif_interet = 2;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            case 3 :
                            {
                                modif_interet = 3;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            case 4 :
                            {
                                modif_interet = 4;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            case 5 :
                            {
                                modif_interet = 5;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            case 6 :
                            {
                                modif_interet = 6;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            case 7 :
                            {
                                modif_interet = 7;

                                std::ofstream fich;
                                fich.open (m_profil_principal, std::ios::out);

                                fich << modif_interet;

                                std::cout << "preference modifiee" << std::endl;

                                break;
                            }

                            default :
                            {
                                std::cout << "veuillez saisir un nombre valide" << std::endl;

                                break;
                            }
                            }
                        }
                    }
                    while (modif_interet < 1 || modif_interet > 7);
                }
                else
                {
                    std::cerr << "ERREUR : OUVERTURE PROFIL" << std::endl;
                }

                return;

                break;
            }

            case 5 :
            {
                m_profil_principal="";
                std::cout<<std::endl;
                std::cout<<"Pour sortir tapez 0, pour revenir au menu inserer un nombre quelconque : ";
                std::cin>>menu;
                if(std::cin.fail())
                {
                    system("cls");
                    std::cerr << "Saisie incorrecte : veuillez recommencer." << std::endl;
                    std::cout << "1.Se connecter " << std::endl << "2.s'inscrire" << std::endl << "3.supprimer profil" << std::endl << "4.changer preference" << std::endl << "5.se deconnecter" << std::endl;
                    std::cout <<"6.Revenir au menu principal"<<std::endl;
                    std::cin.clear();
                    std::cin.seekg(0, std::ios::end);
                    if(!std::cin.fail())
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a déjà un état valide donc inutile de faire appel à clear()
                    }
                    else
                    {
                        std::cin.clear(); // Le flux est dasn un état invalide donc on le remet en état valide
                    }
                }
                else
                {
                    if(menu==0)
                        exit(0);
                    else
                    {
                        system("cls");
                        this->menu();
                    }
                }
            }

            case 6 :
            {
                system("cls");
                this->menu();
                break;
            }

            default :
            {
                std::cout << "Veuillez saisir un nombre valide" << std::endl;

                break;
            }
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


void interface::afficher_preference()
{
    switch(m_type_profil)
    {
    case 1:
        std::cout<<"Plus de monte"<<std::endl;
        break;

    case 2:
        std::cout<<"Plus de descente"<<std::endl;
        break;

    case 3:
        std::cout<<"Debutant"<<std::endl;
        break;

    case 4:
        std::cout<<"Expert"<<std::endl;
        break;

    case 5:
        std::cout<<"Exotique"<<std::endl;
        break;

    case 6:
        std::cout<<"Vertige"<<std::endl;
        break;

    case 7:
        std::cout<<"Claustrophobe"<<std::endl;
        break;

    default:

        break;

    }
}
