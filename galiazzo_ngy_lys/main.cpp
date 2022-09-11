#include "graphe.h"
#include "interface.h"
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

int main()
{
    try
    {
        //appel du constructeur
        Graphe* g=new Graphe("data_arcs.txt");
        //affichage
        interface inter(g);
        //appel du menu
        inter.menu();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }
    return 0;
}
