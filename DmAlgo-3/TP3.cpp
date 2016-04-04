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
      cout << list_adj->planete->nom << "" << list_adj->planete->coord.x << "" << list_adj->planete->coord.y << "" <<
      list_adj->planete->population << "" << list_adj->planete->nation << "" << list_adj->planete->prixCarburant << endl;
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

void init_liste(struct t_graph_dyn *g, const char *filename)
{
  ifstream file_stream(filename);

  struct list_som *som;
  som = new struct list_som;
  g->lsom = som;
  struct list_adj *adj;
  adj = new struct list_adj;
  som->succ = adj;
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
      adj->planete = t;
      adj->planete->nom = tab[0];
      adj->planete->coord.x = atoi(tab[1]);
      adj->planete->coord.y = atoi(tab[2]);
      adj->planete->population = atoi(tab[3]);
      adj->planete->nation = tab[4];
      adj->planete->prixCarburant = atoi(tab[5]);
      adj->planete->visited = false;
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

int main()
{
  struct t_graph_dyn *b = new struct t_graph_dyn;
  struct list_vaisseau *v = new struct list_vaisseau;
  init_liste(b,"test.txt");
  print_all_liste(b);
  init_vaisseau(v,"test2.txt");
  print_all_vaisseau(v);
  return 0;
}
