# include "TP3.h"

Nation::Nation(const char *nom)
{
    this->nom = nom;
    tab_ennemis = NULL;
    nb_ennemis = 0;
}

Vaisseau::toString()
{
    cout << name << " " << type << " " << cap_carburant << endl;
}

Planete::toString()
{
    cout << this->nom << " " << this->coord.x << " " << this->coord.y
         << " " << this->population << " " << this->nation << " "
         << this->prixCarburant << endl;
}

Plateau::toString()
{
    //TODO Pacours graphe
    while(this->vaisseaux)
    {
        vaisseaux->toString();
        vaisseaux = vaisseaux->next;
    }
}

Graph::parcours(struct t_graph_dyn *g)
{
    
}


int main()
{
    return 0;
}
