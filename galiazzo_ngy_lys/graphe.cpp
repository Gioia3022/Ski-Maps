#include "graphe.h"

//Constructeur
Graphe::Graphe(std::string nomFichier)
{
    //Ouverture du fichier
    std::ifstream ifs{nomFichier};
    //Verification que le fichier s'ouvre correctement
    if (ifs.fail())
    {
        throw std::runtime_error("Impossible d'ouvrir en lecture" + nomFichier);
    }
    //récupere le nombre de noeuds
    ifs >> m_ordre;
    if (ifs.fail())
    {
        throw std::runtime_error("Probleme lecture ordre graphe");
    }
    for (int i = 0; i < m_ordre; i++)
    {
        int tempId=0;
        std::string tempNom;
        double tempAltitude=0;

        ifs >> tempId >> tempNom >> tempAltitude;
        // Sauve les informations des sommets dans le vecteur de somments
        m_stations.push_back(new Sommet(tempId, tempNom, tempAltitude)); //Allocation de memoire
    }
    //recupere le nombre d'arcs
    ifs >> m_taille;
    for (int i = 0; i< m_taille; i++)
    {
        int tempId=0;
        std::string tempNom;
        std::string tempType;
        int tempIdDepart;
        int tempIdDest;
        int tempSpe;
        int tempT0;
        float tempTemps;

        ifs >> tempId >> tempNom >> tempType >> tempIdDepart >> tempIdDest >> tempSpe >> tempT0 >> tempTemps;
        // Sauve les informations des arcs dans le vecteur d'arcs
        m_routes.push_back(new Arc(tempId, tempNom, tempType, get_station(tempIdDepart), get_station(tempIdDest), tempSpe, tempT0, tempTemps));
    }
}

//Destructeur
Graphe::~Graphe() {}

//Accesseurs
//getteurs
Sommet* Graphe::get_station(int id)
{
    for(auto s:m_stations)
    {
        if(s->get_id()==id)
        {
            return s;
        }
    }
        return nullptr;
}
Arc* Graphe::get_une_route(int id_dep,int id_dest)
{
    for(auto elem:m_routes)
    {
        if(elem->getDest()->get_id()==id_dest&&elem->getDepart()->get_id()==id_dep)
        {
            return elem;
        }
    }
    return nullptr;
}
int Graphe::get_ordre()
{
    return m_ordre;
}

//Methodes
//Algorithme Dijkstra
void Graphe::dijkstra(Sommet* station_so,Sommet *destinatation,int option)
{
    for (auto elem: m_stations)
    {
        elem->set_couleur(false); //et initialisation de la marque de passage a blanc

    }

    int predecesseur[1000];
    for(int i=0; i<1000; i++)
    {
        predecesseur[i]=1000;
    }

    predecesseur[station_so->get_id()]=666;
    double distance_So_S;
    double distance_S_voisin_de_S;
    double distance_So_voisin_de_S;

    //cette map nous permet de connaitre la distance entre chaque sommet et le sommet So (sommet de départ)
    std::map<Sommet*,double> distances_par_rapport_a_so;

    //celle-ci nous permet de connaitre la distance entre un sommet et son predecesseur
    std::map<int,double> distances_s_predecesseur;

    typedef std::pair<Sommet*, double> pd;

    //surcharge de l'opérateur pour comparer des paires qui contiennet un sommet S et la distance S->So
    struct myComp
    {
        constexpr bool operator()(
            std::pair<Sommet*, double> const& a,
            std::pair<Sommet*, double> const& b)
        const noexcept
        {
            return a.second > b.second;
        }
    };

    std::priority_queue<pd, std::vector<pd>, myComp> pq;
    for (auto elem : m_stations)//initialisation
    {
        if(elem!=station_so)
        {
            distances_par_rapport_a_so.insert(std::make_pair(elem,100000.0));//les stations sont a une distance infini de So
            distances_s_predecesseur.insert(std::make_pair(elem->get_id(),100000.0));//les stations sont par défaut à une distance infini de leur predecesseur
        }
        else
        {
            distances_s_predecesseur.insert(std::make_pair(elem->get_id(),0));
            distances_par_rapport_a_so.insert(std::make_pair(elem,0));//la station So est à une distance de 0 d'elle même
        }
    }
    pq.push(std::make_pair(station_so,0));//on enfile le sommet So dans la queue

    /** DEBUT BOUCLE **/
    while(destinatation->get_couleur()!=true)
    {
        //selection de la station la plus proche car le premier element est le plus proche grâce à la priority queue
        Sommet* station_s=pq.top().first;
        pq.pop();
        station_s->set_couleur(true);//on marque le sommet S le plus proche
        for(auto &une_route:m_routes)
        {
            if(une_route->getDepart()==station_s)//chaque route partant de la station S nous mène vers ses voisins
            {
                Sommet* voisin_de_s=une_route->getDest();
                distance_So_S=distances_par_rapport_a_so.find(station_s)->second;
                distance_So_voisin_de_S=distances_par_rapport_a_so.find(voisin_de_s)->second;
                if(option==0)
                    distance_S_voisin_de_S=une_route->getDuree();//lorsque l'on à pas d'option seul la duree compte
                if(option!=0)
                    distance_S_voisin_de_S=(une_route->get_interet()+une_route->getDuree());//sinon l'interet compte aussi
                if(distance_So_voisin_de_S > distance_So_S + distance_S_voisin_de_S)//si le chemin So->S->S' est plus court que So->S'
                {
                    if(distance_So_voisin_de_S==100000.0)
                        distances_par_rapport_a_so.find(voisin_de_s)->second=0;//on actualise la distance entre So et S'
                    distances_par_rapport_a_so.find(voisin_de_s)->second= distance_So_S + distance_S_voisin_de_S ;
                    pq.push(std::make_pair(voisin_de_s,distance_So_S + distance_S_voisin_de_S));//on enfile le voisin avec sa nouvelle
                    //distance par rapport à So
                    predecesseur[voisin_de_s->get_id()]=station_s->get_id();//predecesseur[S']= S
                    if(distances_s_predecesseur.find(voisin_de_s->get_id())->second==100000.0)
                        distances_s_predecesseur.find(voisin_de_s->get_id())->second=0;
                    distances_s_predecesseur.find(voisin_de_s->get_id())->second=distance_S_voisin_de_S;//on note aussi la distance entre S' et S son prédecesseur
                }
            }
        }
    }
    /** FIN DE LA BOUCLE **/


    int id_destination=destinatation->get_id();
    std::vector<Arc*> pcc;//ce vecteur contiendra les chemins :S_final <= pred[S_final] ; pred[S_final] <= pred[pred[S_final]]; etc...

    //c <= b; b <= a  equivaut à c <= pred[c]; pred[c] <= pred[pred[c]]
    do
    {
        for(auto elem:m_routes)
        {
            if(elem->getDest()->get_id()==id_destination&&elem->getDepart()->get_id()==predecesseur[id_destination]&&distances_s_predecesseur.find(id_destination)->second==(elem->getDuree()+elem->get_interet()))
                pcc.push_back(elem);
            /*pour chaque route ,si la route par du predecesseur du sommet s et qu'elle arrive
            au sommet s et que la duree de cette route est égale à la durée de la route entre s et son predecesseur
            alors la route fait partie du plus cours chemin sinon c'est une autre route qui lie les deux meme sommets mais plus longue*/
        }
        id_destination=predecesseur[id_destination];//le sommet courant s devient le prédécesseur de s
    }
    while(predecesseur[id_destination]!=666);

    this->afficher_chemin(pcc);
    distances_par_rapport_a_so.clear();//on nettoie tous
    distances_s_predecesseur.clear();
    pcc.clear();
    for(unsigned int i=0; i<pq.size(); i++)
    {
        pq.pop();
    }
}

void Graphe::afficher_chemin(std::vector<Arc*> &pcc)
{
    double distance_totale=0; //on initialise le poids a 0
    for(std::vector<Arc*>::reverse_iterator i=pcc.rbegin(); i!=pcc.rend(); i++)//on parcours le vecteur de la fin jusqu'au début
    {
        (*i)->afficherArc();
        distance_totale+=(*i)->getDuree();//la distance totale c'est la somme des distances de chaque trajet du plus court chemin
    }

    int minTemp=(int)distance_totale;
    int tot_heure;
    int tot_minute;
    int tot_secondes;
    if(distance_totale>=60)
    {
        tot_heure=1;
        tot_minute=(minTemp-60);
        tot_secondes=(distance_totale-minTemp)*60;
    }
    if(distance_totale>=120)
    {
        tot_heure=2;
        tot_minute=(minTemp-120);
        tot_secondes=(distance_totale-minTemp)*60;
    }
    if(minTemp>=180)
    {
        tot_heure=3;
        tot_minute=(minTemp-180);
        tot_secondes=(distance_totale-minTemp)*60;
    }
    if(distance_totale<60)
    {
        tot_heure=0;
        tot_minute=(int)distance_totale;
        tot_secondes=(distance_totale-minTemp)*60;
    }


    std::cout<<std::endl;
    std::cout<<" Temps de trajet total: "<< tot_heure<<"h "<<tot_minute<<"min "<<tot_secondes<< "s"<<std::endl;
}

void Graphe::bfs(Sommet* So,Sommet* destination)
{
    int predecesseur[1000];
    for(int i=0; i<1000; i++)
    {
        predecesseur[i]=1000;
    }
    predecesseur[So->get_id()]=666;

    std::queue<Sommet*> q; //on cree la file
    for(auto elem:m_stations)
    {
        elem->set_couleur(false); //on marque tout les sommets a blanc
    }
    q.push(So);
    while(!q.empty())
    {
        Sommet* sommet_courant=q.front();
        q.pop();
        sommet_courant->set_couleur(true);
        for(auto route_partant_du_sommet_courant:m_routes) //pour tous les arcs
        {
            if(route_partant_du_sommet_courant->getDepart()==sommet_courant&&route_partant_du_sommet_courant->getDest()->get_couleur()==false)
            {
                q.push(route_partant_du_sommet_courant->getDest());
                route_partant_du_sommet_courant->getDest()->set_couleur(true); //on marque le sommet
                predecesseur[route_partant_du_sommet_courant->getDest()->get_id()]=sommet_courant->get_id();//le predecesseur du sommet en question est le sommet marque noir
            }
        }
    }

    std::vector<Arc*> pcc;//on crée un vector qui contiendra chaque trajet du bfs pour l'affichage comme pour djisktra
    int id_dest=destination->get_id();

        do
        {
            pcc.push_back(this->get_une_route(predecesseur[id_dest],id_dest));
            id_dest=predecesseur[id_dest];

        }
        while(predecesseur[id_dest]!=666);
        this->afficher_chemin(pcc);
        pcc.clear();

}

void Graphe::afficherSommet()
{
    for (auto const& elem : m_stations)
    {
        std::cout << "numero station : " << elem->get_id() << " nom du sommet : " << elem->get_nom() << " altitude : " << elem->get_altitude() << std::endl;
    }
}

void Graphe::calculer_interet_des_trajets(int option)
{
    this->reset();//on pose la specialisationa 0

    if(option==1)//plus de monté
    {
        for(auto elem:m_routes)
        {
            //si c'est une piste N,R, B, V, SURF ou KL elle va devenir moins interessante
            if(elem->getSpe()==3 || elem->getSpe()==4 || elem->getSpe()==5)
                elem->set_interet(10000.0);
            else
                elem->set_interet(0.0);
        }
    }
    if(option==2)//plus de déscente
    {
        for(auto elem:m_routes)
        {
            if(elem->getSpe()==1 || elem->getSpe()==2)
                elem->set_interet(10000.0);
            else
                elem->set_interet(0.0);
        }
    }
    if(option==3)//débutant, évite les pistes noir,rouges, le snowpark, et la piste de Kilometre lancé
    {
        for(auto elem:m_routes)//un interet élevé représente un poids supplémentaire, c'est comme si le trajet prenait plus de temps si quand il ne nous plait pas
        {
            if(elem->getSpe()==3 || elem->getSpe()==5)
                elem->set_interet(10000.0);
            else
                elem->set_interet(0.0);
        }
    }
    if(option==4)//expert , cherche a éviter les pistes vertes et bleu
    {
        for(auto elem:m_routes)
        {
            if(elem->getSpe()==4)
                elem->set_interet(10000.0);
            else
                elem->set_interet(0.0);
        }
    }
    if(option==5)//plus de piste, le moins de transport possible
    {
        for(auto elem:m_routes)
        {
            if(elem->getSpe()==5)
                elem->set_interet(0.0);
            else
                elem->set_interet(10000.0);
        }
    }
    if(option==6)//vertige , peur bleue des remonté sauf le téléski
    {
        for(auto elem:m_routes)
        {
            if(elem->get_type()=="TPH" ||elem->get_type()=="TS" || elem->get_type()=="BUS" ||  elem->getSpe()==2)
                elem->set_interet(10000.0);
            else
                elem->set_interet(0.0);
        }
    }
    if(option==7)//si claustrophobe peur bleue des remonté sauf le telephériques
    {
        for(auto elem:m_routes)
        {
            if(elem->get_type()=="TC" ||elem->getSpe()==1)
                elem->set_interet(10000.0);
            else
                elem->set_interet(0.0);
        }
    }
}

void Graphe::reset() //set a 0 de l'interet
{
    for (auto elem:m_routes)
        elem->set_interet(0);
}

void Graphe::afficher_info() //appel des fonctions d'affichage
{
     std::cout<<m_ordre<<std::endl;
            for(auto& elem : m_stations)
            {
                elem->affichageTxT();
            }
            std::cout<<std::endl;
            std::cout<<m_taille<<std::endl;
            for(auto& elem : m_routes)
            {
                elem->affichageTxT();
            }
}

void Graphe::afficher_info_sommet(int& choixSommet) //affichage des info concernat un sommet choisi
{
      std::cout << "Voici tous les trajets partant du sommet [ " <<choixSommet<< " ]"<< std::endl;
                    std::cout<<std::endl;
                    for (auto& elem : m_routes)
                    {
                        if ((elem->getDepart())->get_id() == choixSommet)
                        {
                            elem->afficherArc_info();
                        }
                    }
                    std::cout<< std::endl << "Voici tous les trajets arrivant du sommet [ "<<choixSommet<< " ]" << std::endl;
                    for (auto& elem : m_routes)
                    {
                        if ((elem->getDest())->get_id() == choixSommet)
                        {
                            elem->afficherArc_info();
                        }
                    }
}

void Graphe::afficher_info_Arc(int &choixArc)//affichage des info concernat un arc choisi
{
    std::cout <<std::endl<< "Pour l'arc [ "<< choixArc<< " ] :" << std::endl;
                    for (auto elem : m_routes)
                    {
                        if (elem->get_id() == choixArc)
                        {
                            std::cout << "Sommet de depart : " << (elem->getDepart())->get_nom() << std::endl;
                            std::cout << "Sommet d'arrive : " << (elem->getDest())->get_nom() << std::endl;
                            std::cout << "Temps de trajettemps : " << (elem->getMin())<< " min et "<< (elem->getSec())<< " sec" <<std::endl;
                        }
                    }
}

void Graphe::afficher_tous_les_chemins(int &id_station_depart,int &choix_algo) //affichage de l'ensemble des chemins
{
    if((id_station_depart!=6) && (id_station_depart!=28) && (id_station_depart!=29)) //ces trois sommets n'ont pas de successeurs
            {
                for(int i=1; i<m_ordre+1; i++)
                {
                    if(i!=id_station_depart)
                    {
                        std::cout<<std::endl;
                        std::cout<<"_______________TRAJET "<<i<<"_________________"<<std::endl;
                        std::cout<<std::endl;
                        std::cout<<"  [ identifiant ]    [ nom station ]"<<std::endl;
                        std::cout<<"\t[ temps de trajet ]"<<std::endl;
                        std::cout<<std::endl;
                        std::cout<<"\t       [ "<<id_station_depart<<" ]"<<std::endl;
                        if(choix_algo==1)
                            this->dijkstra(this->get_station(id_station_depart),this->get_station(i),0); //appel de la fonction dijkstra
                        if(choix_algo==2)
                            this->bfs(this->get_station(id_station_depart),this->get_station(i)); //appel de la fonction BFS
                    }
                }
            }
            else
            {
                std::cout<< "Il n'as pas de successeurs. "<<std::endl;
            }
}

void Graphe::afficher_plus_court_chemin(int &id_station_depart,int &id_station_final,int &option, int &choix_algo) //affichage du chemin plus cours (avec ou sans options)
{
        this->calculer_interet_des_trajets(option);

            std::cout<<std::endl;
            std::cout<<"\t       [ "<<id_station_depart<<" ]"<<std::endl;
            if((id_station_depart!=6) && (id_station_depart!=28) && (id_station_depart!=29))
                {
                    if(choix_algo==1)
                            this->dijkstra(this->get_station(id_station_depart),this->get_station(id_station_final),option); //appel de la fonction dijkstra
                        if(choix_algo==2)
                            this->bfs(this->get_station(id_station_depart),this->get_station(id_station_final)); //appel de la fonction BFS
                }
            else
                std::cout<< "Il n'as pas de successeurs. "<<std::endl;
            std::cout<<std::endl;
            this->reset();

    }
