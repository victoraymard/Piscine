#include "graph.h"
#include"Animal.h"
#include"Reservoir.h"
#include"Vegetal.h"
#include <sstream>
#include <fstream>
namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, int mini, int maxi, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(mini, maxi);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( patch::to_string(idx) );
}

void Vertex::setarc_entrant(int numero_de_larc)
{
    m_in.push_back(numero_de_larc);
}
void Vertex::setarc_sortant(int numero_de_larc)
{
    m_out.push_back(numero_de_larc);
}

/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( patch::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( patch::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLEUCLAIR);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    std::ifstream fichier("graphes1.txt",std::ios::in);
    int nbarrette,nbsommet,nsommet,x,y, maxi;
    float nombre;
    std::string nom;
    if (fichier)
    {
        fichier>>nbsommet;
        fichier>>nbarrette;
        for(int i=0; i<nbsommet; i++)
        {
            fichier>>nsommet;
            fichier>>nombre;
            fichier>>x;
            fichier>>y;
            fichier>>nom;
            maxi = nombre + nombre*0.8;
            add_interfaced_vertex(nsommet,nombre,x,y, 0, maxi, nom);

        }
        fichier.close();

        std::ifstream fichier("grapha1.txt",std::ios::in);
        int indice, sommet1,sommet2;
        float poids;
        for(int i=0; i<nbarrette; i++)
        {

            fichier>>indice,fichier>>sommet1,fichier>>sommet2,fichier>>poids;
            add_interfaced_edge(indice,sommet1,sommet2,poids);

        }
        fichier.close();

    }



    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    /* add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
     add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
     add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
     add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
     add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
     add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
     add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
     add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);*/

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    /* add_interfaced_edge(0, 1, 2, 50.0);
     add_interfaced_edge(1, 0, 1, 50.0);
     add_interfaced_edge(2, 1, 3, 75.0);
     add_interfaced_edge(3, 4, 1, 25.0);
     add_interfaced_edge(4, 6, 3, 25.0);
     add_interfaced_edge(5, 7, 3, 25.0);
     add_interfaced_edge(6, 3, 4, 0.0);
     add_interfaced_edge(7, 2, 0, 100.0);
     add_interfaced_edge(8, 5, 2, 20.0);
     add_interfaced_edge(9, 3, 7, 80.0);*/
}
void Graph::recuperation(std::string nom1)///enlever le nom2
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 800, 600);

    std::string n = nom1 + ".txt" ;

    std::ifstream fichier(n);

    if(fichier)
    {
        int v1 = 0;
        int v2 = 0 ;
        int idx, x,y, maxi, mini, id_vert1, id_vert2;
        double value, weight;
        std::string pic_name;

        fichier >> v1;
        fichier >> v2;

        for(int i = 0 ; i < v1 ; i++)
        {
            fichier >> idx;
            fichier >> value;
            fichier >> x;
            fichier >>  y;
            fichier >>  pic_name;
            maxi = value + value*0.8;
            mini = 0;
            add_interfaced_vertex(idx, value, x, y, mini, maxi, pic_name);
        }

        for (int i = 0 ; i < v2 ; i++)
        {
            fichier >> idx;
            fichier >> id_vert1;
            fichier >> id_vert2;
            fichier >> weight;
            add_interfaced_edge(idx,id_vert1, id_vert2, weight);
        }
    }
    else std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();
    for (auto &elt : m_edges)
        elt.second.post_update();

    /*if (key[KEY_C])
    {
        savecoord1( m_vertices);
    }

    if (key[KEY_V])
    {
        savecoord2(m_vertices);
    }*/

    if (key[KEY_B])
    {
        sauvegarde(m_vertices);
    }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, int mini, int maxi, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, mini, maxi, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;
    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}


void Graph::sauvegarde(std::map<int, Vertex> m_vertices)
{
    std::string buff;
    std::ofstream fichier("graphe1.txt",std::ios::out|std::ios::trunc);

    fichier << m_vertices.size()<<std::endl;
    fichier << m_edges.size()  << std::endl;


    for(unsigned int i=0; i<m_vertices.size(); i++)fichier<<i<<" "<<m_vertices[i].m_value<<" "
                                                                                   << m_vertices[i].m_interface->m_top_box.get_posx()
                                                                                   <<" "<<m_vertices[i].m_interface->m_top_box.get_posy()
                                                                                   << " "<<m_vertices[i].m_interface->m_img.m_pic_name<<std::endl;

    for(unsigned int i=0; i<m_edges.size(); i++)fichier<< i << " "<< m_edges[i].m_from<< " " << m_edges[i].m_to
                                                                                    << " " << m_edges[i].m_weight <<std::endl;
    fichier.close();
}


void Graph::remplissagemap(std::string& path)  /// remplissage de la map de sommet à partir dun fichier du type reseau trophique1.txt
{                                              /// il faut absolument mettre | dans chaque ligne entre les arcs entrants et sortants sinon on a une boucle infini
    std::vector<Vertex> vecteur_de_sommet_transitoire;
    std::string buffer;
    std::vector<std::string> info;
    std::ifstream file(path, std::ios::in);

    if(file)
    {
        getline(file, buffer, '-');
        for(int i = 0; getline(file, buffer, '-'); i++)
        {
            if(buffer.find("\n") <= buffer.size())
            {

                    if(info[0]=="A")
                    {
                        int value1=atoi(info[2].c_str()),value2=atoi(info[3].c_str()),value3=atoi(info[4].c_str());
                        Animal animal;
                        animal.setnom(info[1]);
                        animal.setnombre_individus(value1);
                        animal.setcapacite_de_portage(value2);
                        animal.setrythme_de_croissance(value3);
                        int k=5;
                        while(info[k]!="|")
                        {
                            int value=atoi(info[k].c_str());
                            animal.setarc_entrant(value);
                            k=k+1;
                        }
                        for(unsigned int i=k; i<info.size();i++)
                                {
                                    int val=atoi(info[i].c_str());
                                    animal.setarc_sortant(val);
                                }
                     vecteur_de_sommet_transitoire.push_back(animal);
                    }
                   if(info[0]=="V")
                    {
                        int value1=atoi(info[2].c_str()),value2=atoi(info[3].c_str()),value3=atoi(info[4].c_str());
                        Vegetal vegetal;
                        vegetal.setnom(info[1]);
                        vegetal.setnombre_individus(value1);
                        vegetal.setcapacite_de_portage(value2);
                        vegetal.setrythme_de_croissance(value3);
                        unsigned int i=5;
                        while(info[i]!="|")
                        {
                            int value=atoi(info[i].c_str());
                            vegetal.setarc_entrant(value);
                            i=i+1;
                        }
                        for(unsigned int p=i; i<info.size();i++)
                                {
                                    int val=atoi(info[p].c_str());
                                    vegetal.setarc_sortant(val);
                                }
                     vecteur_de_sommet_transitoire.push_back(vegetal);
                    }
                    if(info[0]=="R")
                    {
                        int value1=atoi(info[2].c_str()),value2=atoi(info[3].c_str()),value3=atoi(info[4].c_str());
                        Reservoir reservoir;
                        reservoir.setnom(info[1]);
                        reservoir.setbiomasse(value1);
                        reservoir.setcapacite_de_portage(value2);
                        reservoir.setrythme_de_croissance(value3);
                        int j=5;
                        while(info[j]!="|")
                        {
                            int value=atoi(info[j].c_str());
                            reservoir.setarc_entrant(value);
                            j=j+1;
                        }
                        for(unsigned int i=j; i<info.size();i++)
                                {
                                    int val=atoi(info[i].c_str());
                                    reservoir.setarc_sortant(val);
                                }
                     vecteur_de_sommet_transitoire.push_back(reservoir);
                    }


            }
        }
    }
    else{std::cout<<"Probleme ouverture fichier"<<std::endl;
    }

    for(unsigned int y=0; y<vecteur_de_sommet_transitoire.size();y++)
    {
      m_vertices[y]=vecteur_de_sommet_transitoire[y];
    }
}
