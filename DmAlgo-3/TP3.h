#ifndef TP2_H
#define TP2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

class Nation
{
  protected:
    const char *nom;
    const char **tab_ennemis;
    size_t nb_ennemis;
  public:
    Nation(const char *nom = "lal");

};

class Graph
{
    private:
        struct t_graph_dyn *graph;
    public:
        Graph();
        static void parcours(struct t_graph_dyn *g);
        static void build(struct t_graph_dyn *graph, const char *filename);
        static bool find_path(struct list_som *s1, struct list_som *s2,int v_type);

};

struct Coord
{
    float x,y;
};

double getDistance(Coord a, Coord b)
{
    return(sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)));
}

class Vaisseau
{
  public:
    const char *name;
    float cap_carburant;
    int type;
    Vaisseau(const char *name,float capacity);
    ~Vaisseau();
    void toString();
};

struct list_vaisseau
{
    struct list_vaisseau *next;
    Vaisseau *vaisseau;
};

class Planete : Nation
{
  public:
    bool visited;
    Coord coord;
    unsigned long  population;
    float prixCarburant;
    const char *nation;
    const char *nom;
    Planete(const char *nom,float x1,float y1,const char*nation, unsigned long population,float prixCarburant);
    void toString();
    ~Planete();
};

class Plateau
{
    private:
        struct t_graph_dyn *plateau;
        struct list_vaisseau *vaisseaux;
    public:
        Plateau();
        void toString();
        static void load_vaisseaux(struct list_vaisseau *l, char *filename);
};

struct list_adj
{
    struct list_adj *next;
    double cout;
    double distance; // TODO var distance entre 2 pts à deplacer
    Planete *planete;
};

struct list_som
{
    struct list_som *next;
    struct list_adj *succ;
    struct list_adj *prec;
    //Planete planete;TODO add planete constructor
};

struct t_graph_dyn
{
    size_t ordre;
    struct list_som *lsom;
};
#endif
