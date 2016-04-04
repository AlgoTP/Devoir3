# include "TP3.h"

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
    vaisseaux->v.toString();
    vaisseaux = vaisseaux->next;
  }
}

void Graph::parcours(struct t_graph_dyn *g)
{
  struct list_som *list_som= g->lsom;
  struct list_adj *list_adj= list_som->succ;
  while(list_som)
  {
    while(list_adj)
    {
      list_adj = list_adj->next;
    }
    list_som = list_som->next;
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

Planete::Planete(const char *nom,float x1,float y1,const char *nation,unsigned long population, float prixCarburant)
{
  this->nom = nom;
  this->coord.x = x1;
  this->coord.y = y1;
  this->nation = nation;
  this->population = population;
  this->prixCarburant = prixCarburant;
}


void init_liste(struct t_graph_dyn *g, const char *filename)
{
  ifstream file_stream(filename);

  struct list_som *som = g->lsom;
  som = new struct list_som;
  struct list_adj *adj = som->succ;
  adj = new struct list_adj;
  char tmp[50];

  if(file_stream)
  {
    while(!file_stream.eof())
    {
      file_stream.getline(tmp, 50);
      char **tab = split(tmp);
      Planete *t = new Planete(tab[0],atoi(tab[1]),atoi(tab[2]),tab[3],atoi(tab[4]),atoi(tab[5]));
      adj->planete = t;
      adj->planete->nom = tab[0];
      adj->planete->coord.x = atoi(tab[1]);
      adj->planete->coord.y = atoi(tab[2]);
      adj->planete->population = atoi(tab[3]);
      adj->planete->nation = tab[4];
      adj->planete->prixCarburant = atoi(tab[5]);

      adj->next = new struct list_adj;
      som->next = new struct list_som;
      som->prec = adj;
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
}

int main()
{
  struct t_graph_dyn *b = new struct t_graph_dyn;
  init_liste(b,"test.txt");
  return 0;
}
