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



    return 0;
}

void menu()
{
    while ( !key[KEY_ESC] )
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




        if(mouse_b&1 && 246 < mouse_x &&  mouse_x < 452 && 215< mouse_y && mouse_y < 260 )
        {
            x = true;
            if( secu == false)
            {
                secu = true;
                std::string nom = "graphe1";
                std::string nom1 = "graphe1bis";
                g.recuperation(nom, nom1);
            }

            while (x == true)
            {


                g.update();
                grman::mettre_a_jour();


                if(key[KEY_R])
                {
                    x= false;
                    blit(fond, buffer, 0,0,0,0,800, 600);
                    blit(buffer, screen, 0,0,0,0,800, 600);
                }

            }


        }
    }
}
END_OF_MAIN();
