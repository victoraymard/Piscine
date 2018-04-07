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

    /// Un exemple de graphe
//    Graph g;
//     std::string nom = "txt1";
//    std::string nom1 = "txt2";
//    g.recuperation(nom, nom1);

    menu();
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
//    while ( !key[KEY_ESC] )
//    {
//        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
//        g.update();
//
//        /// Mise à jour générale (clavier/souris/buffer etc...)
//        grman::mettre_a_jour();
//    }

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
        std::string nom2 = "graphe1bis";
        std::string nom3 = "graphe2";


while ( !key[KEY_ESC] )
    {
/*if( secu == false)
            {
                secu = true;
                std::string nom1 = "graphe1";
                g.recuperation(nom1);
            }


        if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 215< mouse_y && mouse_y < 260 )
        {
            x = true;*/


      ///---------------------------------------------------------------------

     x= false;

    std::string nom = " ";
        secu=false;

        if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 215< mouse_y && mouse_y < 260 )///graphe1
        {
            key[KEY_R] = false;


            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom1);

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

            }
        }
            else if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 350< mouse_y && mouse_y < 380 )///graphe2
        {
              key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom2);

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

            }
        }
           else if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 440< mouse_y && mouse_y < 500 )///graphe3
        {
              key[KEY_R] = false;
            x = true;
            if( secu == false)
            {
                secu = true;
                g.recuperation(nom3);
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

            }
        }
///-------------------------------------------------------------



        }
    }
END_OF_MAIN();
