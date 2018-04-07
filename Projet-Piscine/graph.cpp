#include "graph.h"
#include"Animal.h"
#include"Reservoir.h"
#include"Vegetal.h"
#include <sstream>
#include <fstream>
#include<stack>
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
VertexInterface::VertexInterface(int idx, int x, int y, int mini, int maxi, std::string thing_name,std::string pic_name, int pic_idx)
{
    m_idx = idx;


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
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_gravity_x(grman::GravityX::Right);
    m_box_label_idx.set_posy(70);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( patch::to_string(idx) );

    m_top_box.add_child(m_bouton1);
    m_bouton1.set_dim(50,12);
    m_bouton1.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_bouton1.set_bg_color(ROUGECLAIR);

    m_bouton1.add_child( m_msg );
    m_msg.set_message("delete");

    //nom animal
    m_top_box.add_child(m_nom_animal);
    m_nom_animal.set_frame(90,6, 0, 0 );

    m_nom_animal.add_child(m_nom_animal_label);
    m_nom_animal_label.set_message(thing_name);
    m_nom_animal_label.set_color(MARRONSOMBRE);



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
void Vertex::post_update(int *x)
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();

    if (m_interface->m_bouton1.clicked())
    {
        *x = m_interface->getidx();
    }
}
int VertexInterface::getidx()
{
    return m_idx;
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

    ///boite à boutons
    m_tool_box.add_child(m_boite_boutons);
    m_boite_boutons.set_dim(75, 175);
    m_boite_boutons.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_boite_boutons.set_bg_color(GRISSOMBRE);

    /// bouton1
    m_boite_boutons.add_child(m_bouton1);
    m_bouton1.set_frame(0,0,78,44);
    m_bouton1.set_bg_color(BLEU);

    m_bouton1.add_child(m_bouton1_label);
    m_bouton1_label.set_message("SAUVER");


    /// bouton 2
    m_boite_boutons.add_child(m_bouton2);
    m_bouton2.set_frame(0,45,78,44);
    m_bouton2.set_bg_color(ROUGESOMBRE);

    m_bouton2.add_child(m_bouton2_label);
    m_bouton2_label.set_message("CHANGER");

    /// bouton 3
    m_boite_boutons.add_child(m_bouton3);
    m_bouton3.set_frame(0,90,78,44);
    m_bouton3.set_bg_color(BLEU);

    m_bouton3.add_child(m_bouton3_label);
    m_bouton3_label.set_message("+ ARETE");


    /// bouton 4
    m_boite_boutons.add_child(m_bouton4);
    m_bouton4.set_frame(0,135,78,44);
    m_bouton4.set_bg_color(ROUGESOMBRE);

    m_bouton4.add_child(m_bouton4_label);
    m_bouton4_label.set_message("EXIT");
}



void Graph::recuperation(std::string nom1)
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
        std::string pic_name, thing_name;
        fichier >> v1;
        fichier >> v2;

        for(int i = 0 ; i < v1 ; i++)
        {
            fichier >> idx;
            fichier >> value;
            fichier >> x;
            fichier >>  y;
            fichier >> thing_name;
            fichier >>  pic_name;
            maxi = value + value*0.8;
            mini = 0;
            add_interfaced_vertex(idx, value, x, y, mini, maxi, thing_name, pic_name);
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
    else
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    int *x = new int;
    *x = -1;
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update(x);
    for (auto &elt : m_edges)
        elt.second.post_update();


    /// TOUCHES CLAVIER
    if (key[KEY_B])
    {
        sauvegarde(m_vertices);
    }

    /// BOUTONS

    if (m_interface->m_bouton1.clicked())
    {
        //sauvegarder
        sauvegarde(m_vertices);
    }
    if (m_interface->m_bouton2.clicked()) ///ne marche pas trop
    {
        //changer de réseau
        key[KEY_R]=true;

    }
    if (m_interface->m_bouton3.clicked())
    {
        // ajouter une arete
        add_edge();

    }
    if (m_interface->m_bouton4.clicked())
    {
        // exit
        key[KEY_R]=true;
        key[KEY_ESC]=true;

    }

    if (*x > -1 && *x < m_vertices.size())
    {
        enleversommet(*x);
    }

    delete x;
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, int mini, int maxi, std::string thing_name, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, mini, maxi, thing_name, pic_name, pic_idx);
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
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}


void Graph::sauvegarde(std::map<int, Vertex> m_vertices)
{
    std::string buff;

    std::string nomFichier = "";
    std::cout <<"quel est le nom du fichier ?\n";
    std::cin >> nomFichier;
    std::ofstream fichier(nomFichier+".txt",std::ios::out|std::ios::trunc);

    std::map<int, Vertex>::iterator it;
    std::map<int, Edge>::iterator it1;

    fichier << m_vertices.size()<<std::endl;
    fichier << m_edges.size()  << std::endl;


    for(it = m_vertices.begin(); it != m_vertices.end(); it++)
        fichier<<it->first<<" "<<m_vertices[it->first].m_value<<" "
               << m_vertices[it->first].m_interface->m_top_box.get_posx()
               <<" "<<m_vertices[it->first].m_interface->m_top_box.get_posy()
               << " "<<m_vertices[it->first].m_interface->m_img.m_pic_name<<  std::endl;

    for(it1 = m_edges.begin(); it1 != m_edges.end(); it1++)
        fichier<< it1->first << " "<< m_edges[it1->first].m_from<< " " << m_edges[it1->first].m_to
               << " " << m_edges[it1->first].m_weight <<std::endl;
    fichier.close();
}


void Graph::remplissagemap(std::string path)  /// remplissage de la map de sommet à partir dun fichier du type reseau trophique1.txt
{
    /// il faut absolument mettre | dans chaque ligne entre les arcs entrants et sortants sinon on a une boucle infini
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
                    int value1=atoi(info[2].c_str()),value2=atoi(info[3].c_str());
                    float value3=strtof(info[4].c_str(),0);
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
                    for(unsigned int i=k; i<info.size(); i++)
                    {
                        int val=atoi(info[i].c_str());
                        animal.setarc_sortant(val);
                    }
                    vecteur_de_sommet_transitoire.push_back(animal);
                }
                if(info[0]=="V")
                {
                    int value1=atoi(info[2].c_str()),value2=atoi(info[3].c_str());
                    float value3=strtof(info[4].c_str(),0);
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
                    for(unsigned int p=i; i<info.size(); i++)
                    {
                        int val=atoi(info[p].c_str());
                        vegetal.setarc_sortant(val);
                    }
                    vecteur_de_sommet_transitoire.push_back(vegetal);
                }
                if(info[0]=="R")
                {
                    int value1=atoi(info[2].c_str()),value2=atoi(info[3].c_str());
                    float value3=strtof(info[4].c_str(),0);
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
                    for(unsigned int i=j; i<info.size(); i++)
                    {
                        int val=atoi(info[i].c_str());
                        reservoir.setarc_sortant(val);
                    }
                    vecteur_de_sommet_transitoire.push_back(reservoir);
                }
                info.erase(info.begin(), info.end());
                i = 0;

            }
            else
            {
                info.push_back(buffer);
            }
        }
        file.close();
    }
    else
    {
        std::cout<<"Probleme ouverture fichier"<<std::endl;
    }

    for(unsigned int y=0; y<vecteur_de_sommet_transitoire.size(); y++)
    {
        m_vertices[y]=vecteur_de_sommet_transitoire[y];
    }
}

void Graph::test_remove_edge(int eidx)
{
    /// référence vers le Edge à enlever
    /// on parcourt la map jusqu'à l'endroit de l'indice rentré en paramètre de la fonction
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " de poid " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << "AVANT : size entrant de " << remed.m_from << " : " << m_vertices[remed.m_from].m_in.size() << " : size sortant de " << remed.m_from << " : " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << "AVANT : size entrant de " << remed.m_to << " : " << m_vertices[remed.m_to].m_in.size() << " : size sortant de " << remed.m_to << " : " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << "AVANT : taille des edges a la fin : " << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        // EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        // m_interface->m_main_box.add_child(ei->m_top_edge); */
        // m_edges[idx] = Edge(weight, ei); */
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << "APRES : size entrant de " << remed.m_from << " : " << m_vertices[remed.m_from].m_in.size() << " : size sortant de " << remed.m_from << " : " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << "APRES : size entrant de " << remed.m_to << " : " << m_vertices[remed.m_to].m_in.size() << " : size sortant de " << remed.m_to << " : " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << "APRES : taille des edges a la fin : " << m_edges.size() << std::endl;

}


void Graph::enleversommet(int vidx)
{
    Vertex &remver = m_vertices.at(vidx);

    int i = remver.m_in.size()-1;
    while (!remver.m_in.empty())
    {
        test_remove_edge(remver.m_in[i]);
        i--;
    }

    int j = remver.m_out.size()-1;
    while (!remver.m_out.empty())
    {
        test_remove_edge(remver.m_out[j]);
        j--;
    }

    if (m_interface && remver.m_interface)
    {
        m_interface->m_main_box.remove_child( remver.m_interface->m_top_box );
        m_vertices.erase(vidx);

    }
}



void Graph::add_edge()
{
    int n =0, sommet1, sommet2;
    float poids;
    bool indiceTrouve = false;

    do
    {
        if(m_edges.count(n))
            n++;//si la marque est déjà attribuée
        else
            indiceTrouve = true;
    }
    while(!indiceTrouve);

    do
    {
        std::cout<<"choisir le sommet de depart"<<std::endl;
        std::cin>>sommet1;

        std::cout<<"choisir le sommet d'arrivee"<<std::endl;
        std::cin>>sommet2;
    }
    while(sommet1 == sommet2);

    do
    {
        std::cout<<"entrez le poids"<<std::endl;
        std::cin>>poids;
    }
    while(poids<0);

    add_interfaced_edge(n, sommet1, sommet2,  poids);
}

void Graph::clear_map()
{
    m_vertices.clear();
    m_edges.clear();
}





















/***********************************************************

           FONCTIONS EN DEVELOPPEMENT

***********************************************************/





void Graph::k_connexite()
{

    std::map<int,Vertex>map_de_transition=m_vertices;
//    std::vector<int> vect_reference=BFS(map_de_transition);
    for(std::map<int,Vertex>::iterator it=map_de_transition.begin(); it!=map_de_transition.end(); it++)
    {
        map_de_transition.erase(it->first);
        // std::vector<int> vect=BFS(map_de_transition);
        // algo de tri pour faire en sorte que les 2 soient rangés pareil
        //on ajoute le sommet effacé dans le premoer
        // on regarde sils sont egaux
        //if vect_reference==vect
        //on stock : it->first
        // on incrémente un compteur
        // else
        // on affiche it-> first
        //"il suffit d'enlever le sommet it -> first pour que le graphe ne soit plus connexe"
        ///BFS SUR LA NOUVELLE MAP DE TRANSITION
        /// SI ON TROUVE LA MEME COMPOSANTE CONNEXE (EXCEPTE LE SOMMET QUON A ERASE)
        /// ON CONTINUE
        /// ON LE STOCK
        /// ON ERASE UN AUTRE SOMMET DE MAP DE TRANSITION
        ///SINON ON NOTE LE SOMMET QUON A ERASE : ON LE STOCK ON
        ///

    }

}

void Graph::kosaraju()
{
    //for (auto &elt : m_vertices)m
///initialisation
    for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on initialise les marques à false
    {
        it->second.m_marque= false;
    }
    std::stack<int> tabSommet;

    /*auto premierSommet = m_vertices.begin();
    bfs(premierSommet)*/


///premiere boucle
//on prend un sommet random
    for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on initialise les marques à false
    {
        it->second.m_marque= false;
    }

    bool algoTermine=false;
    bool nouveauSommet = false;
    std::stack<int> pile;
    std::stack<int> stack2;
    auto it = m_vertices.begin();
    int s = it->first;

    pile.push(s);//on commence par le premier sommet

    std::cout<<"kosoraju\n";
    while(!algoTermine)//tous les sommets ne sont pas marqués
    {

        while(!pile.empty())
        {
            s = pile.top();
            std::cout <<s<<" ";
            stack2.push(s);
            pile.pop();

            // boucle pour les sommets adjacents

            for (auto it = m_edges.begin(); it!=m_edges.end(); ++it)//on initialise les marques à false
            {
                //si le sommet  est voisin et n'est pas marqué , on le marque et on l'enpile
                if (it->second.m_from == s)//si il pointe vers un autre sommet
                {
                    //on vérifie que le sommet n'est pas marqé
                    if(m_vertices[it->second.m_to].m_marque==false)
                    {
                        //on marque le sommet
                        m_vertices[it->second.m_to].m_marque= true;
                        //on le push
                        pile.push(it->second.m_to);
                    }
                }
            }
        }

        //on se place sur une autre composante connexe, on change de sommet
        nouveauSommet=false;
        for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on parcourt  lles sommets
        {
            if ((it->second.m_marque==false)&& nouveauSommet ==false)
            {
                //on marque le sommet, on le push,  on met le booléen à vrai
                it->second.m_marque = true;
                pile.push(it->first);
                nouveauSommet = true;
            }
        }

        //boucle de vérification si tous les sommts sont marqués
        algoTermine = true;
        for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on parcourt  lles sommets
        {
            if (it->second.m_marque==false)
                algoTermine=false;
        }
    }
    std::cout<<std::endl<<std::endl<<"affichage stack2 \n";
    for(unsigned int i = 0; i< stack2.size(); i++)
    {
        std::cout << stack2.top()<< " ";
        stack2.pop();
    }
}

void Graph::bfs()
{

    for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on initialise les marques à false
    {
        it->second.m_marque= false;
    }

    bool algoTermine=false;
    bool nouveauSommet = false;
    std::stack<int> pile;
    auto it = m_vertices.begin();
    int s = it->first;

    pile.push(s);//on commence par le premier sommet
    while(!algoTermine)//tous les sommets ne sont pas marqués
    {

        while(!pile.empty())
        {
            s = pile.top();
            std::cout <<s<<" ";
            pile.pop();

            // boucle pour les sommets adjacents

            for (auto it = m_edges.begin(); it!=m_edges.end(); ++it)//on initialise les marques à false
            {
                //si le sommet  est voisin et n'est pas marqué , on le marque et on l'enpile
                if (it->second.m_from == s)//si il pointe vers un autre sommet
                {
                    //on vérifie que le sommet n'est pas marqé
                    if(m_vertices[it->second.m_to].m_marque==false)
                    {
                        //on marque le sommet
                        m_vertices[it->second.m_to].m_marque= true;
                        //on le push
                        pile.push(it->second.m_to);
                    }
                }
            }
        }

        //on se place sur une autre composante connexe, on change de sommet
        nouveauSommet=false;
        for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on parcourt  lles sommets
        {
            if ((it->second.m_marque==false)&& nouveauSommet ==false)
            {
                //on marque le sommet, on le push,  on met le booléen à vrai
                it->second.m_marque = true;
                pile.push(it->first);
                nouveauSommet = true;
            }
        }

        //boucle de vérification si tous les sommts sont marqués
        algoTermine = true;
        for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)//on parcourt  lles sommets
        {
            if (it->second.m_marque==false)
                algoTermine=false;
        }
    }
}


void Graph::composante_fortement_connexe()
{
    std::vector<int> tabPremierPassage;
    std::vector<int>tabSecondPassage;
    std::vector<int>composanteFortementConnexe;
    std::vector<bool>tabMarque;

    //initialisation de tabmarque
    for(unsigned int i = 0; i <m_vertices.size(); i++)
    {
        tabMarque.push_back(false);
        tabPremierPassage.push_back(-1);
        tabSecondPassage.push_back(-1);
        composanteFortementConnexe.push_back(-1);
    }
  //  tabPremierPassage[s]=1;
   // tabSecondPassage[s]=1;

}


