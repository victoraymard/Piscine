///AYMARD                 Projet d'informatique                       TD02
///BALLAND                 Théorie des Graphes
///CARABIN                   ING2,semestre 2


/// graphe 1 : Réseau trophique des milieux marins de l'Antarctique
/// graphe 2 : Réseau trophique des dinosaures
/// graphe 3 : Les invasions barbars


///sources :
///http://www.ece.fr/~fercoq/allegro/
///https://openclassrooms.com/courses/lecture-et-ecriture-dans-les-fichiers-en-c++
///http://www.cplusplus.com/reference/map/map/


/// Guillaume Carabin : A travaillé en parallèle avec Hugo Dores et Jean-Baptiste Scelles pour certaines fonctions
///----------------------------------------------------------------------------------------------------------------------------------



/*!
*\file main.cpp
*\brief contrôle le programme
*\author Aymard, Balland, Carrabin
*\date 13.04.2018
*\version
*/



#include "grman/grman.h"
#include <iostream>
#include "graph.h"

void menu();
int main()
{

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    menu();

    grman::fermer_allegro();

    //! nettoyage du terminal
    system("cls");
    std::cout <<"Au revoir"<<std::endl;

    return 0;
}

/**
*\fn void menu()
*\brief interface et gestion du menu
*\return la fonction ne retourne rien.
*/
void menu()
{

    BITMAP* fond ;
    BITMAP* buffer ;
    fond = load_bitmap("menuuu.jpg", NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    blit(fond, buffer, 0,0,0,0,1000, 740);
    blit(buffer, screen, 0,0,0,0,1000, 740);

    grman::set_pictures_path("pics");
    bool x = false, secu = false;
    Graph g;
    std::string nom1 = "graphe1";
    std::string nom2 = "dino";
    std::string nom3 = "graphe2";
    std::string nom4 = "graphe1.jpg"; ///inserer le nom de l'image de fond
    std::string nom5 = "graphe2.jpg"; ///ici aussi
    std::string nom6 = "graphe3.jpg"; ///ici encore



    while ( !key[KEY_ESC] )
    {

        x= false;

        std::string nom = " ";
        secu=false;

        if(mouse_b&1 && 410 < mouse_x &&  mouse_x < 580 && 310< mouse_y && mouse_y < 370 )///graphe1
        {
            key[KEY_R] = false;
            key[KEY_M]=false;
            key[KEY_N]=false;

            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom1,nom4);
            }
            while (x == true)
            {
                g.update(nom1);
                grman::mettre_a_jour();

                if(key[KEY_R] )
                {
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();
                }

                if (key[KEY_M])
                {
                    key[KEY_M] = false;

                    g.k_connexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.recuperation(nom1,nom4);
                }
                if (key[KEY_N])
                {
                    key[KEY_N] = false;
                    g.forte_conexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.recuperation(nom1,nom4);
                }
                if (key[KEY_C])
                {
                    key[KEY_C] = false;
                    g.clear_map();
                    g.recuperation_bis(nom1);
                }
            }
        }
        else if(mouse_b&1 && 410 < mouse_x &&  mouse_x < 580 && 450< mouse_y && mouse_y < 490 )///graphe2
        {
            key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom2,nom5);
            }
            while (x == true)
            {
                g.update(nom2);
                grman::mettre_a_jour();

                if(key[KEY_R])
                {
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();
                }
                if (key[KEY_M])
                {
                    key[KEY_M] = false;

                    g.k_connexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.recuperation(nom2,nom5);
                }
                if (key[KEY_N])
                {
                    key[KEY_N] = false;
                    g.forte_conexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.recuperation(nom2,nom5);
                }
                if (key[KEY_C])
                {
                    key[KEY_C] = false;
                    g.clear_map();
                    g.recuperation_bis(nom2);
                }
            }
        }
        else if(mouse_b&1 && 410 < mouse_x &&  mouse_x < 580 && 570< mouse_y && mouse_y < 610 )///graphe3
        {
            key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom3,nom6);
            }
            while (x == true)
            {
                g.update(nom3);
                grman::mettre_a_jour();

                if(key[KEY_R])
                {
                    x= false;
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.clear_map();
                }
                if (key[KEY_M])
                {
                    key[KEY_M] = false;

                    g.k_connexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.recuperation(nom3,nom6);
                }
                if (key[KEY_N])
                {
                    key[KEY_N] = false;
                    g.forte_conexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,1000, 740);
                    blit(buffer, screen, 0,0,0,0,1000, 740);
                    g.recuperation(nom3,nom6);
                }
                if (key[KEY_C])
                {
                    key[KEY_C] = false;
                    g.clear_map();
                    g.recuperation_bis(nom3);
                }
            }
        }
    }
}
END_OF_MAIN();
