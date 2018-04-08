
///AYMARD                 Projet d'informatique                       TD02
///BALLAND                 Théorie des Graphes
///CARABIN                   ING2,semestre 2


/// graphe 1 : Réseau trophique des milieux marins de l'Antarctique
/// graphe 2 : ...
/// graphe 3 : ...


///sources :
///http://www.ece.fr/~fercoq/allegro/
///https://openclassrooms.com/courses/lecture-et-ecriture-dans-les-fichiers-en-c++
///http://www.cplusplus.com/reference/map/map/


/// Guillaume Carabin : Travail en parallèle avec Hugo Dores et Jean-Baptiste Scelles pour certaines fonctions





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

    //nettoyage du terminal
    system("cls");
    std::cout <<"Au revoir"<<std::endl;

    return 0;
}


void menu()
{

    BITMAP* fond ;
    BITMAP* buffer ;
    fond = load_bitmap("menu.jpg", NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    blit(fond, buffer, 0,0,0,0,800, 600);
    blit(buffer, screen, 0,0,0,0,800, 600);

    grman::set_pictures_path("pics");
    bool x = false, secu = false;
    Graph g;
    std::string nom1 = "graphe1";
    std::string nom2 = "fortementconnexetest";
    std::string nom3 = "graphe2";
    std::string nom4 = "menu.jpg"; ///inserer le nom de l'image de fond
    std::string nom5 = "menu.jpg"; ///ici aussi
    std::string nom6 = "graphe3.jpg"; ///ici encore



    while ( !key[KEY_ESC] )
    {
        ///---------------------------------------------------------------------

        x= false;

        std::string nom = " ";
        secu=false;

        if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 215< mouse_y && mouse_y < 260 )///graphe1
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
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.clear_map();
                }

                if (key[KEY_M])
                {
                    key[KEY_M] = false;

                    g.k_connexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.recuperation(nom1,nom4);
                }
                if (key[KEY_N])
                {
                    key[KEY_N] = false;
                    g.forte_conexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.recuperation(nom1,nom4);
                }
                 if (key[KEY_C])
                {
                    key[KEY_C] = false;
                    g.clear_map();
                    g.recuperation_bis();
                }
            }
        }
        else if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 350< mouse_y && mouse_y < 380 )///graphe2
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
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.clear_map();
                }
                if (key[KEY_M])
                {
                    key[KEY_M] = false;

                    g.k_connexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.recuperation(nom2,nom5);
                }
                if (key[KEY_N])
                {
                    key[KEY_N] = false;
                    g.forte_conexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.recuperation(nom2,nom5);
                }
                if (key[KEY_C])
                {
                    key[KEY_C] = false;
                    g.clear_map();
                    g.recuperation_bis();
                }
            }
        }
        else if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 440< mouse_y && mouse_y < 500 )///graphe3
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
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.clear_map();
                }
                if (key[KEY_M])
                {
                    key[KEY_M] = false;

                    g.k_connexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.recuperation(nom3,nom6);
                }
                if (key[KEY_N])
                {
                    key[KEY_N] = false;
                    g.forte_conexite();

                    g.clear_map();
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                    g.recuperation(nom3,nom6);
                }
                if (key[KEY_C])
                {
                    key[KEY_C] = false;
                    g.clear_map();
                    g.recuperation_bis();
                }
            }
///-------------------------------------------------------------
        }
    }
}
END_OF_MAIN();
