#include "arcs.h"

//Constructeur
Arc::Arc(int id, std::string nom, std::string type, Sommet* depart, Sommet* dest, int spe, int t0, float temps)
{
    m_id = id;
    m_nom = nom;
    m_type = type;
    m_depart = depart;
    m_destination = dest;
    m_spe=spe;
    m_t0=t0;
    m_temps=temps;

    //calcul du temps a partir des informations donnees dans le sujet
    //pour les descentes
    if(m_type=="V"||m_type=="B"||m_type=="R"||m_type=="N"||m_type=="KL"||m_type=="SURF")
        m_duree=m_t0+(m_temps/100)*((m_depart->get_altitude())-(m_destination->get_altitude()));
    //pour les montées et les bus
    else
        m_duree=m_t0+(m_temps/100)*((m_destination->get_altitude())-(m_depart->get_altitude()));

    //calcul des durees en heures, minutes et secondes
    for(int i=0; i<100; i++)
    {
        int minTemp=(int)m_duree;

        if(minTemp>=60)
            {
                m_h++;
                m_min=(minTemp-60);
                 m_sec=(m_duree-minTemp)*60;
            }
        if(minTemp>=120)
            {
                m_h=2;
                m_min=(minTemp-120);
                 m_sec=(m_duree-minTemp)*60;
            }
        if(minTemp>=180)
            {
                m_h=3;
                m_min=(minTemp-120);
                 m_sec=(m_duree-minTemp)*60;
            }
        if(minTemp<60)
        {
            m_h=0;
            m_min=(int)m_duree;
             m_sec=(m_duree-minTemp)*60;
        }

    }
}

//Destructeur
Arc::~Arc()
{
    delete m_depart;
    delete m_destination;
}

//Accesseur
//getteurs
Sommet* Arc::getDepart()
    {
        return m_depart;
    }

Sommet* Arc::getDest()
    {
        return m_destination;
    }
float Arc::getDuree()
    {
        return m_duree;
    }
int Arc::getH()
    {
        return m_h;
    }
int Arc::getMin()
    {
        return m_min;
    }
int Arc::getSec()
    {
        return m_sec;
    }
int Arc::get_id()
    {
        return m_id;
    }
std::string Arc::get_nom()
    {
        return m_nom;
    }
std::string Arc::get_type()
    {
        return m_type;
    }
double Arc::get_interet()
 {
     return m_interet;
 }

 int Arc::getSpe()
 {
     return m_spe;
 }

 //setteur
 void Arc::set_interet(double val)
 {
     m_interet=val;
 }

 //Methodes d'affichage
 //informations sur l'arc
void Arc::affichageTxT()
    {
            std::cout<<m_id<<"\t"<<m_nom<<"\t"<<m_type<<"\t"<<(m_depart->get_id())<<"\t"<<(m_destination->get_id())<<"\t"<<m_spe<<"\t"<<m_t0<<"\t"<<m_temps<<std::endl;
    }

void Arc::afficherArc_info()
    {
        std::cout << "[ " << m_id << " ]" <<"\t"<<"nom : " << m_nom <<std::endl<<"\t"<< "duree du trajet de : "<< m_h<< " h "<< m_min<< " min et " << m_sec << " sec ";
        if (m_type == "V" || m_type == "B" || m_type == "R" || m_type == "N" || m_type == "KL" || m_type == "SURF")
        {
            std::cout <<std::endl<<"\t"<< "C'est une piste : " << m_type << std::endl;
            std::cout <<std::endl;
        }
        if (m_type == "TPH" || m_type == "TC" || m_type == "TSD" || m_type == "TS" || m_type == "TK")
        {
            std::cout <<std::endl<<"\t"<< "C'est une remonte mecanique : " << m_type << std::endl;
            std::cout <<std::endl;
        }
        if (m_type == "BUS")
        {
            std::cout << std::endl<<"\t"<<"C'est un trajet bus" << std::endl;
            std::cout <<std::endl;
        }
    }

//affichage des info sur le chemin
void Arc::afficherArc()
    {
        std::cout<<"\t|\t\t  |"<<std::endl;
        std::cout<<"\t|    "<<m_h <<" "<<m_min<<"' "<<m_sec <<"''\t  |  -> "<<m_type<<std::endl;
        std::cout<<"\t|\t\t  |"<<std::endl;
        std::cout<<"\tv\t\t  v"<<std::endl;
        std::cout<<"      [ "<<m_destination->get_id()<<" ]\t\t[ "<<m_destination->get_nom() <<" ]"<<std::endl;
    }
