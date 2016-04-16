#include "TP3.h"

void init_list_adj(struct t_graph_dyn *g,const char *filename);
void parc_largeur(struct list_som *list);
Nation::Nation(const char *nom)
{
  this->nom = nom;
  tab_ennemis = NULL;
  nb_ennemis = 0;
}

void Vaisseau::toString()
{
  cout << name << " " << type << " " << cap_carburant << endl;
}

void Planete::toString()
{
  cout << this->nom << " " << this->coord.x << " " << this->coord.y
    << " " << this->population << " " << this->nation << " "
    << this->prixCarburant << endl;
}

void Plateau::toString()
{
  //TODO Pacours graphe
  while(this->vaisseaux)
  {
    vaisseaux->vaisseau->toString();
    vaisseaux = vaisseaux->next;
  }
}

void print_all_liste(t_graph_dyn *g)
{
  struct list_som *list_som= g->lsom;
  struct list_adj *list_adj= list_som->succ;
  while(list_som)
  {
    while(list_adj->next)
    {
      cout << list_adj->elt->planete->nom << "" << list_adj->elt->planete->coord.x << "" << list_adj->elt->planete->coord.y << "" <<
        list_adj->elt->planete->population << "" << list_adj->elt->planete->nation << "" << list_adj->elt->planete->prixCarburant << endl;
      list_adj = list_adj->next;
    }
    list_som = list_som->next;
  }
}

void print_all_vaisseau(struct list_vaisseau *vaisseau)
{
  while(vaisseau->next)
  {
    cout << vaisseau->vaisseau->name << "" << vaisseau->vaisseau->cap_carburant << endl;
    vaisseau=vaisseau->next;
  }
}

void Graph::parcours(struct t_graph_dyn *g)
{
  struct list_som *list_som= g->lsom;
  // struct list_adj *list_adj= list_som->succ;
  // struct queue *file;
  int acc = 0;
  g->lsom = list_som;
  while(list_som->next)
  {
    if(!list_som->planete)
      break;
    cout << acc++ << endl;
    list_som->planete->visited = false;
    list_som = list_som->next;
  }
  struct list_som *l = g->lsom;
  while(l)
  {

    if(!g->lsom->planete->visited)
      parc_largeur(l);
    l = l->next;
  }

}

bool search_path(struct list_som *list, Planete *p)
{
  while(list->planete != p)
    list = list->next;
  parc_largeur(list);
  return (list->planete->visited);
}

void parc_largeur(struct list_som *list)//, (void)(*func)(struct list_som))
{
  list->planete->visited = true;
  struct queue *file = new_queue();
  queue_push(file, list->succ);
  while(!queue_is_empty(file))
  {
    struct list_adj *la = queue_pop(file);
    la->elt->planete->toString();
    while(la->next)
    {
      if(!la->elt->planete->visited)
      {
        la->elt->planete->visited = true;
        queue_push(file, la);
      }
      la = la->next;
    }

  }
}

char** split(string s)
{
  char **tab = new char*[6];
  for(size_t p = 0; p < 6;p++)
  {
    (tab[p]) = new char[50];
  }

  size_t id = 0;
  size_t i = 0;
  for(size_t j = 0; j < strlen(s.c_str()) && s[j] != '\r' && s[j] != '\n' && s[j] != '\0'; j++)
  {
    if(s[j] == ' ')
    {
      tab[id][i] = 0;
      id++;
      i = 0;
    }
    else
    {
      tab[id][i] += s[j];
      i++;
    }
  }
  return tab;
}

char** splitForVaisseau(string s)
{
  char **tab = new char*[2];
  for(size_t p = 0; p < 2;p++)
  {
    (tab[p]) = new char[50];
  }

  size_t id = 0;
  size_t i = 0;
  for(size_t j = 0; j < strlen(s.c_str()) && s[j] != '\r' && s[j] != '\n' && s[j] != '\0'; j++)
  {
    if(s[j] == ' ')
    {
      tab[id][i] = 0;
      id++;
      i = 0;
    }
    else
    {
      tab[id][i] += s[j];
      i++;
    }
  }
  return tab;
}

Planete::Planete(const char *nom,float x1,float y1,const char *nation,unsigned long population, float prixCarburant)
{
  this->nom = nom;
  this->coord.x = x1;
  this->coord.y = y1;
  this->nation = nation;
  this->population = population;
  this->prixCarburant = prixCarburant;
}

Vaisseau::Vaisseau(const char *name,float cap_carburant)
{
  this->name = name;
  this->cap_carburant = cap_carburant;
}

void print_all_liste2(t_graph_dyn *g)
{
  int accu = 0;
  while(g->lsom->next)
  {
    while(g->lsom->succ)
    {
      cout << accu++ << endl;
      g->lsom->succ = g->lsom->succ->next;
    }
    cout << g->lsom->planete->nom << " " << g->lsom->planete->coord.x << " " << g->lsom->planete->coord.y << " " <<
      g->lsom->planete->population << " " << g->lsom->planete->nation << " " << g->lsom->planete->prixCarburant << endl;
    g->lsom= g->lsom->next;
  }
}

struct t_graph_dyn *init_liste2(struct t_graph_dyn *g,const char *filename)
{
  ifstream file_stream(filename);

  struct list_som *som = new struct list_som;
  struct list_adj *adj = new struct list_adj;
  g->lsom = som;
  g->lsom->succ = adj;
  char tmp[50];

  if(file_stream)
  {
    while(!file_stream.eof())
    {
      file_stream.getline(tmp,50);
      if(tmp[0] == ' ' || tmp[0] == '\n' || tmp[0] == '\0')
        break;
      char **tab = split(tmp);
      Planete *t = new Planete(tab[0],atoi(tab[1]),atoi(tab[2]),tab[3],atoi(tab[4]),atoi(tab[5]));
      g->lsom->planete = t;
      g->lsom->planete->nom = tab[0];
      g->lsom->planete->coord.x = atoi(tab[1]);
      g->lsom->planete->coord.y = atoi(tab[2]);
      g->lsom->planete->population = atoi(tab[3]);
      g->lsom->planete->nation = tab[4];
      g->lsom->planete->prixCarburant = atoi(tab[5]);
      g->lsom->planete->visited = false;

      g->lsom->next = new struct list_som;
      g->lsom->next->prec = g->lsom;
      g->lsom = g->lsom->next;
    }
  }
  /*while(g->lsom->next)
    {
    cout << g->lsom->planete->nom << endl;
    g->lsom = g->lsom->next;
    }
    while(g->lsom->prec)
    {
    g->lsom = g->lsom->prec;
    cout << accu++ << endl;
    }*/
  init_list_adj(g,filename);
  print_all_liste2(g);
}

void init_list_adj(struct t_graph_dyn *g,const char *filename)
{
  ifstream file_stream(filename);
  struct list_som *som = new struct list_som;
  struct list_adj *adj = new struct list_adj;
  som = g->lsom;
  adj = g->lsom->succ;
  char tmp[50];

  if(file_stream)
  {
    while(!file_stream.eof())
    {
      file_stream.getline(tmp,50);
      if(tmp[0] == ' ' || tmp[0] == '\n' || tmp[0] == '\0')
        break;
      if(!g->lsom->next)
      {
        adj->elt = g->lsom->prec;
        while(!file_stream.eof())
        {
          file_stream.getline(tmp,50);
          if(tmp[0] == ' ' || tmp[0] == '\n' || tmp[0] == '\0')
            break;
          adj->next = new struct list_adj;
          som = som->prec;
          adj->elt = som->prec;
        }
      }
      adj->elt = g->lsom->next;
      adj->next = new struct list_adj;
      g->lsom = g->lsom->next;
    }
  }
}


struct t_graph_dyn* init_liste(struct t_graph_dyn *g, const char *filename)
{
  ifstream file_stream(filename);

  struct list_som *som;
  som = new struct list_som;
  g->lsom = som;
  struct list_adj *adj;
  adj = new struct list_adj;
  adj->elt = (struct list_som *)malloc(sizeof(struct list_som));
  struct list_adj *p = adj;
  g->lsom->succ = p;
  char tmp[50];

  if(file_stream)
  {
    while(!file_stream.eof())
    {
      file_stream.getline(tmp, 50);
      if(tmp[0] == ' ' || tmp[0] == '\n' || tmp[0] == '\0')
        break;
      char **tab = split(tmp);
      Planete *t = new Planete(tab[0],atoi(tab[1]),atoi(tab[2]),tab[3],atoi(tab[4]),atoi(tab[5]));
      adj->elt->planete = t;
      adj->elt->planete->nom = tab[0];
      adj->elt->planete->coord.x = atoi(tab[1]);
      adj->elt->planete->coord.y = atoi(tab[2]);
      adj->elt->planete->population = atoi(tab[3]);
      adj->elt->planete->nation = tab[4];
      adj->elt->planete->prixCarburant = atoi(tab[5]);
      adj->elt->planete->visited = false;
      adj->next = new struct list_adj;
      adj->next->elt = new struct list_som;//(struct list_som*)malloc(sizeof(struct list_som));
      som->planete = t;
      som->next = new struct list_som;
      //som->prec = adj;
      adj = adj->next;
      som = som->next;
      som->succ = adj;
      g->ordre = g->ordre +1;
    }
  }
  else
  {
    cerr << "Error opening " << file_stream << endl;
  }
  return g;
}

void init_vaisseau(struct list_vaisseau *list_v,const char *filename)
{
  ifstream file_stream(filename);
  char tmp[50];
  if(file_stream)
  {
    while(!file_stream.eof())
    {
      file_stream.getline(tmp, 50);
      if(tmp[0] == '\0')
        break;
      char **tab = splitForVaisseau(tmp);
      Vaisseau *vaisseau = new Vaisseau(tab[0],atoi(tab[1]));
      list_v->vaisseau = vaisseau;
      list_v->vaisseau->name = tab[0];
      list_v->vaisseau->cap_carburant = atoi(tab[1]);
      list_v->next = new struct list_vaisseau;
      list_v = list_v->next;
    }
  }
}

void test()
{
  struct t_graph_dyn *b = new struct t_graph_dyn;
  struct list_vaisseau *v = new struct list_vaisseau;
  b = init_liste(b,"test.txt");
  print_all_liste(b);
  init_vaisseau(v,"test2.txt");
  print_all_vaisseau(v);
  Graph::parcours(b);
}

int main()
{
  //test();
  struct t_graph_dyn *b = new struct t_graph_dyn;
  init_liste2(b,"test.txt");
  cout << "wtf ?? " << endl;
  print_all_liste2(b);
  return 0;
}
