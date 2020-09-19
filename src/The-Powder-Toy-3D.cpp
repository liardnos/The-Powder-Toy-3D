#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

extern "C" {
    #include "../lib/my.h"
}


using namespace std;
using namespace sf;


int main()
{
    lld_t* lld = lld_init();

    lld_insert(lld, (int)(i64)lld->data, (void *)"hello ");
    lld_insert(lld, (int)(i64)lld->data, (void*)"how ");
    lld_insert(lld, (int)(i64)lld->data, (void*)"are ");
    lld_insert(lld, (int)(i64)lld->data, (void*)"you? ");

    while (lld->data) {
        char* str = (char*)lld_pop(lld, 0);
        cout << str;
    }

    //variable debug
    cout << "hello";
    //variable interface
    const int window_size_x = 1000;
    const int window_size_y = 600;

    //variable physique
    float const forcerebond_x = 0.9; //multiplicateur 0.9
    float const forcerebond_y = 0.9; //multiplicateur 0.9
    float const graviterGlobal = 0.01; //px**-2 per frame 0.01
    float const graviterlocal = 0.05; //multiplicateur 0.1
    float const antigraviterlocal = 0.001; //multiplicateur 0
    int const antigraviter_power = 1; //1
    float const frotement = 1; // multiplicateur de v 1
    float const frotement_entre_particule = 0.98; //0.98 //car� de la distance
    float const distanceMin = 1; //en px 1
    int const interaction_distance = 4; // window_size/taille_des_case = 1 //4
    int const taille_des_case = 15; //15
    const float distance_de_matien = 50; //50
    int physique_mode = 1;

    //forme
    //coordonn�e en haut et droite // en bas a gauche //de 0 a 100%
    float mur1_pos_x1 = 49; //45
    float mur1_pos_y1 = -20; //-20
    float mur1_pos_x2 = 51; //55
    float mur1_pos_y2 = -85; //97

    //simulation
    float delay = 120; //en FPS

    //variable shape
    int nb_shape = 10000; //100 / 200
    const int nb_shape2 = 10000;
    int const shape_size = 10; //10 px
    int const nb_shape_to_remove = 10000;
    int collisiont_count = 0;
    //autre
    string console_input = "";
    string console_list[10] = { "See : To see all var",
                                "VarName : to change a variable value"
    };
    int const console_var_nb = 15;
    string console_var_list_txt[console_var_nb] = { "",
    "forcerebond_x",
    "forcerebond_y",
    "graviterGlobal",
    "graviterlocal",
    "frotement",
    "frotement_entre_particule",
    "distanceMin",
    "interaction_distance",
    "distance_de_matien",
    "mur1_pos_x1",
    "mur1_pos_y1",
    "mur1_pos_x2",
    "mur1_pos_y2",
    "shape_size" };

    int const Help_len = 20;
    string const help1[Help_len] = { "Welcome to the Arcturus simulator",
                                        "--------------------------",
                                        "H : Help",
                                        "P : Pause",
                                        "I : Slow down simulation",
                                        "O : Speed up simulation",
                                        "C : console",
                                        "L : Log on/off",
                                        "E : End simulation",
                                        "M : place 1 or 25 shape",
                                        "--------------------------",
                                        "Arrows : Move object",
                                        "--------------------------",
                                        "F1 : Show speed",
                                        "F2 : Don\'t work",
                                        "F3 : Don\'t work",
                                        "F4 : LSD" };

    //ini
    //tableau 3d
    int grille[window_size_x / taille_des_case + interaction_distance][window_size_y / taille_des_case + interaction_distance][5];
    for (int n = 0; n != window_size_x / taille_des_case + interaction_distance + 1; n++)
    {
        for (int n2 = 0; n2 != window_size_y / taille_des_case + interaction_distance + 1; n2++)
        {
            for (int n3 = 0; n3 != 51; n3++)
            {
                grille[n][n2][n3] = -1;
            }
        }
    }


    mur1_pos_x1 *= window_size_x / 100;
    mur1_pos_x2 *= window_size_x / 100;
    mur1_pos_y1 *= window_size_y / 100;
    mur1_pos_y2 *= window_size_y / 100;
    int NumberOfFrame = 0;
    float v_xs[nb_shape2];
    float v_ys[nb_shape2];
    float pos_x[nb_shape2];
    float pos_y[nb_shape2];
    float v_xs2[nb_shape2];
    float v_ys2[nb_shape2];
    float pos_x2[nb_shape2];
    float pos_y2[nb_shape2];
    float mass_shape[nb_shape2];
    float complexity = 0;//pow(nb_shape,2);
    int pass = 0;
    int color_mode = 1;
    bool log_onoff = 0;
    int nb_interaction[nb_shape2];
    float distance_min_particule[nb_shape2];
    bool shape_place_1 = 0;

    sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y), "part sim");
    vector<CircleShape> shapes(nb_shape2, CircleShape(shape_size / 2));
    CircleShape G(3);
    G.setFillColor(sf::Color::Red);
    //texture mur du millieux
    RectangleShape Mur1_shape(sf::Vector2f(mur1_pos_x2 - mur1_pos_x1 - shape_size, mur1_pos_y2 - mur1_pos_y1 - shape_size));
    Mur1_shape.setFillColor(sf::Color::White);
    Mur1_shape.setPosition(mur1_pos_x1 + shape_size, mur1_pos_y1 + shape_size);

    nb_shape = 0;
    //initialisation shape
    for (int n = 0; n < nb_shape2; n++)
    {
        nb_interaction[n] = 0;
        pos_x2[n] = (window_size_x / 8);
        pos_y2[n] = (window_size_y / 16);
        v_xs2[n] = 0;
        v_ys2[n] = 0;
    }

    for (int n = 0; n < nb_shape2; n += 1)
    {
        shapes[n].setFillColor(Color(0, 0, 255));
        /*shapes[n+1].setFillColor(Color());
        shapes[n+2].setFillColor(Color::Green);
        shapes[n+3].setFillColor(Color::Cyan);
        shapes[n+4].setFillColor(Color::Magenta);
        shapes[n+5].setFillColor(Color::Yellow);*/
    }

    //help
    cout << "press H for help" << endl;
    while (window.isOpen())
    {

        //while (stop == 1)
        //{
        sf::Event event;
        bool stop = false;
        while (window.pollEvent(event) || stop == true)
        {
            if (stop == true)
            {
                sleep(milliseconds(100));
            }
            if (event.type == sf::Event::Closed)
                window.close();
            //stop
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && stop == true)
            {
                stop = false;
                sleep(milliseconds(100));
                cout << "play!" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && stop == false)
            {
                stop = true;
                sleep(milliseconds(100));
                cout << "stop!" << endl;
            }
            //color mode
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
            {
                color_mode = 1; //speed
                cout << "speed" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
            {
                color_mode = 2; //nb interaction marche pas
                cout << "pression" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
            {
                color_mode = 3; //distance Min
                cout << "Distance Min" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
            {
                color_mode = 4; //distance Min
                cout << "random" << endl;
            }
            //phyique
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {//UP jump
                for (int n = 0; n < nb_shape; n++)
                {
                    v_ys2[n] -= graviterGlobal * 100;
                }
                if (log_onoff == 1)
                    cout << "/\\" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {//Down jump
                for (int n = 0; n < nb_shape; n++)
                {
                    v_ys2[n] += graviterGlobal * 100;
                }
                if (log_onoff == 1)
                    cout << "\\/" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {//UP Left
                for (int n = 0; n < nb_shape; n++)
                {
                    v_xs2[n] -= graviterGlobal * 100;
                }
                if (log_onoff == 1)
                    cout << "<-" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {//UP Right
                for (int n = 0; n < nb_shape; n++)
                {
                    v_xs2[n] += graviterGlobal * 100;
                }
                if (log_onoff == 1)
                    cout << "->" << endl;
            }
            //simulation speed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                delay -= 10;
                if (delay < 0)
                    delay = 0;
                sleep(milliseconds(100));
                cout << "\"fps\" : " << delay << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                delay += 10;
                sleep(milliseconds(100));
                cout << "\"fps\" : " << delay << endl;
            }
            //help
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                for (int n = 0; n < Help_len; n++)
                    cout << help1[n] << endl;
                sleep(milliseconds(100));
            }
            //stop log
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                if (log_onoff == 0)
                {
                    log_onoff = 1;
                    cout << "log : on\n";
                }
                else
                {
                    log_onoff = 0;
                    cout << "log : off\n";
                }
                sleep(milliseconds(100));
            }

            //console
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                for (int n = 0; n < console_var_nb; n++)
                    cout << console_var_list_txt[n] << endl;
                cin >> console_input;
                for (int n = 0; n < console_var_nb; n++)
                    if (console_input == console_list[n])
                        cout << console_list[n] << " = nb" << n;

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                if (shape_place_1 == 1)
                {
                    shape_place_1 = 0;
                    cout << "shape/click = 25\n";
                }
                else
                {
                    shape_place_1 = 1;
                    cout << "shape/click = 1\n";
                }
                sleep(milliseconds(100));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                if (physique_mode == 1)
                {
                    physique_mode = 2;
                    cout << "Liquide\n";
                }
                else
                {
                    physique_mode = 1;
                    cout << "Solide\n";
                }
                sleep(milliseconds(100));
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (shape_place_1 == 0)
                        for (int n = -2; n <= 2; n++)
                        {
                            cout << "25 shape place" << endl;
                            for (int n2 = -2; n2 <= 2; n2++)
                            {
                                nb_shape += 1;
                                v_xs2[nb_shape - 1] = 0;
                                v_ys2[nb_shape - 1] = 0;
                                pos_x2[nb_shape - 1] = event.mouseButton.x + n * taille_des_case * interaction_distance;
                                pos_y2[nb_shape - 1] = event.mouseButton.y + n2 * taille_des_case * interaction_distance;

                            }
                        }
                    else
                    {
                        cout << "1 shape place" << endl;
                        nb_shape++;
                        v_xs2[nb_shape - 1] = 0;
                        v_ys2[nb_shape - 1] = 0;
                        pos_x2[nb_shape - 1] = event.mouseButton.x;
                        pos_y2[nb_shape - 1] = event.mouseButton.y;
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if (nb_shape >= 25 && shape_place_1 == 0)
                    {
                        nb_shape += -25;
                    }
                    else
                        if ((nb_shape >= 1 && shape_place_1 == 1))
                            nb_shape--;

                }
            }
            //stop = 0;
            //}
        }

        window.clear();
        //initialisation de la grille
        // =-1
        for (int n = 0; n != nb_shape; n++)
        {
            grille[int(pos_x[n] / taille_des_case)][int(pos_y[n] / taille_des_case)][0] = -1;
        }

        //tableau 1 = tableau 2
        for (int n = 0; n != nb_shape; n++)
        {
            v_xs[n] = v_xs2[n];
            v_ys[n] = v_ys2[n];
            pos_x[n] = pos_x2[n];
            pos_y[n] = pos_y2[n];
        }

        //initialisation de la grille2
        // =n
        for (int n = 0; n != nb_shape; n++)
        {
            int n2 = 0;
            while (grille[int(pos_x[n] / taille_des_case)][int(pos_y[n] / taille_des_case)][n2] != -1 && n2 < 48)
            {
                n2++;
            }
            //cout<<n<<"\nx: "<<pos_x[n]/shape_size<<"\ny :"<<pos_y[n]/shape_size<<endl;

            grille[int(pos_x[n] / taille_des_case)][int(pos_y[n] / taille_des_case)][n2] = n;
            grille[int(pos_x[n] / taille_des_case)][int(pos_y[n] / taille_des_case)][n2 + 1] = -1;
            //cout<<grille[int(pos_x[n]/shape_size)][int(pos_y[n]/shape_size)][n2]<<endl;
        }

        //affiche les forme
        float v[nb_shape2];
        float vmax = 0;
        float interaction_max = 0;
        float dmin = window_size_x;
        float dmax = 1;
        for (int n = 0; n < nb_shape; n++)
        {
            if (color_mode == 1)
            {
                v[n] = pow(pow(v_xs2[n], 2) + pow(v_ys2[n], 2), 0.5);
                if (v[n] > vmax)
                    vmax = v[n];
            }
            else
                if (color_mode == 2)
                {
                    if (interaction_max < nb_interaction[n])
                        interaction_max = nb_interaction[n];
                }
                else
                    if (color_mode == 3)
                    {
                        if (distance_min_particule[n] < dmin)
                            dmin = distance_min_particule[n];
                        if (distance_min_particule[n] > dmax)
                            dmax = distance_min_particule[n];

                    }
        }
        for (int n = 0; n != nb_shape; n++)
        {
            if (color_mode == 1)
            {
                float vv = v[n] / (vmax + 0.001) * 255;
                shapes[n].setFillColor(Color(vv, 0, 0 - vv));
            }
            else
                if (color_mode == 2)
                {
                    float vv = nb_interaction[n] / (interaction_max + 0.001) * 255;
                    shapes[n].setFillColor(Color(vv, 0, 255 - vv));
                    nb_interaction[n] = 0;
                }
                else
                    if (color_mode == 3)
                    {

                        float vv = (distance_min_particule[n] - dmin) / (dmax - dmin) * 255;
                        shapes[n].setFillColor(Color(255 - vv, 0, vv));
                        distance_min_particule[n] = window_size_x;
                    }
                    else
                        if (color_mode == 4)
                            shapes[n].setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
            shapes[n].setPosition(pos_x[n], pos_y[n]);
            window.draw(shapes[n]);
        }
        if (color_mode == 4)
            color_mode = 0;
        float Gpointx = 0;
        float Gpointy = 0;

        //afficher mur
        window.draw(Mur1_shape);

        //point G
        for (int n = 0; n != nb_shape; n++)
        {
            Gpointx += pos_x[n] / nb_shape;
            Gpointy += pos_y[n] / nb_shape;
        }
        G.setPosition(Gpointx, Gpointy);
        window.draw(G);

        window.display();


        int optigrav = 0;

        //calcul physic
        for (int n = 0; n < nb_shape; n++)
        {
            //n0 = middle
            pos_x2[0] = window_size_x / 2;
            v_xs2[0] = 0;
            v_ys2[0] = 0;

            //graviter Global
            v_ys2[n] += graviterGlobal;//*mass_shape[n]/255;

            /*//graviter local
            for(int n2 = 0; n2!=nb_shape;n2++)
            {
                float dx = pos_x[n2]-pos_x[n];
                float dy = pos_y[n2]-pos_y[n];
                float d = pow(pow(dx,2)+pow(dy,2),0.5)+distanceMin;
                float vx = (dx/d)/pow(d,3);
                float vy = (dy/d)/pow(d,3);
                v_ys2[n] += vy*graviterlocal;
                v_xs2[n] += vx*graviterlocal;

            }*/

            //"graviter^-1"
            int xgri = int(pos_x[n] / taille_des_case);
            int ygri = int(pos_y[n] / taille_des_case);


            //cout<<"gravsearch\n";
            for (int x = -interaction_distance; x <= interaction_distance; x++)
            {
                while (xgri + x < 0)
                {
                    x++;
                }
                for (int y = -interaction_distance; y <= interaction_distance; y++)
                {
                    while (ygri + y < 0)
                    {
                        y++;
                    }
                    int nbinter = 0;
                    int n2 = grille[int(xgri + x)][int(ygri + y)][int(nbinter)];
                    while (n2 != -1 && nbinter < 49 && n2 >= 0 && n2 <= nb_shape)
                    {
                        grille[xgri][ygri][0] = -1;
                        nbinter++;

                        float dx = pos_x[n2] - pos_x[n];
                        float dy = pos_y[n2] - pos_y[n];
                        float d = pow(pow(dx, 2) + pow(dy, 2), 0.5) + distanceMin + 1;
                        if (d < interaction_distance * taille_des_case && n != n2)
                        {
                            float vx = dx / d;
                            float vy = dy / d;

                            float v_relative_x = v_xs2[n2] - v_xs2[n];
                            float v_relative_y = v_ys2[n2] - v_ys2[n];
                            float v_relative = pow(pow(v_relative_x, 2) + pow(v_relative_y, 2), 0.5) + 0.1;
                            float v_relative_angle = acos(v_relative_x / v_relative);

                            {
                                if (physique_mode == 1)
                                {
                                    //interaction
                                    //frotement
                                    v_xs2[n] = v_xs2[n] * frotement_entre_particule + v_xs2[n2] * (1 - frotement_entre_particule);
                                    v_ys2[n] = v_ys2[n] * frotement_entre_particule + v_ys2[n2] * (1 - frotement_entre_particule);
                                    v_xs2[n2] = v_xs2[n2] * frotement_entre_particule + v_xs2[n] * (1 - frotement_entre_particule);
                                    v_ys2[n2] = v_ys2[n2] * frotement_entre_particule + v_ys2[n] * (1 - frotement_entre_particule);
                                    //grav circular
                                    v_xs2[n] += pow(d - distance_de_matien, antigraviter_power) * graviterlocal * vx;
                                    v_ys2[n] += pow(d - distance_de_matien, antigraviter_power) * graviterlocal * vy;
                                    v_xs2[n2] -= pow(d - distance_de_matien, antigraviter_power) * graviterlocal * vx;
                                    v_ys2[n2] -= pow(d - distance_de_matien, antigraviter_power) * graviterlocal * vy;
                                }
                                if (physique_mode == 2)
                                {
                                    v_xs2[n] -= 0.01 * pow(d, antigraviter_power) * graviterlocal * vx;
                                    v_ys2[n] -= 0.01 * pow(d, antigraviter_power) * graviterlocal * vy;
                                    v_xs2[n2] += 0.01 * pow(d, antigraviter_power) * graviterlocal * vx;
                                    v_ys2[n2] += 0.01 * pow(d, antigraviter_power) * graviterlocal * vy;

                                    v_xs2[n] = v_xs2[n] * frotement_entre_particule + v_xs2[n2] * (1 - frotement_entre_particule);
                                    v_ys2[n] = v_ys2[n] * frotement_entre_particule + v_ys2[n2] * (1 - frotement_entre_particule);
                                    v_xs2[n2] = v_xs2[n2] * frotement_entre_particule + v_xs2[n] * (1 - frotement_entre_particule);
                                    v_ys2[n2] = v_ys2[n2] * frotement_entre_particule + v_ys2[n] * (1 - frotement_entre_particule);
                                }
                            }

                            //F module
                            nb_interaction[n]++;
                            nb_interaction[n2]++;
                            if (d < distance_min_particule[n])
                            {
                                distance_min_particule[n] = d;
                            }
                            if (d < distance_min_particule[n2])
                            {
                                distance_min_particule[n2] = d;
                            }
                            complexity++;

                        }
                        n2 = grille[int(xgri + x)][int(ygri + y)][int(nbinter)];

                    }
                }
            }
            {
                if (pos_x2[n] < interaction_distance * taille_des_case)
                {
                    v_xs2[n] += antigraviterlocal / pow(pos_x2[n] + distanceMin, antigraviter_power);
                }
                if (pos_x2[n] > window_size_x - interaction_distance * taille_des_case)
                {
                    v_xs2[n] += -antigraviterlocal / pow(window_size_x - pos_x2[n] + distanceMin - shape_size, antigraviter_power);
                }
                if (pos_y2[n] < interaction_distance * taille_des_case)
                {
                    v_ys2[n] += antigraviterlocal / pow(pos_y2[n] + distanceMin, antigraviter_power);
                }
                if (pos_y2[n] > window_size_y - interaction_distance * taille_des_case)
                {
                    v_ys2[n] += -antigraviterlocal / pow(window_size_y - pos_y2[n] + distanceMin - shape_size, antigraviter_power);
                }
            }
            //optigrav++;
            //acc�l�ration
            pos_x2[n] += v_xs2[n];
            pos_y2[n] += v_ys2[n];

            //mur du millieux
            //x++
            if ((pos_x[n]<mur1_pos_x1 && pos_x2[n]>mur1_pos_x1) && pos_y2[n] > mur1_pos_y1 && pos_y2[n] < mur1_pos_y2)
            {
                v_xs2[n] *= -forcerebond_x;
                pos_x2[n] = mur1_pos_x1 - 1;
            }
            //x--
            if ((pos_x[n] > mur1_pos_x2 && pos_x2[n] < mur1_pos_x2) && pos_y2[n] > mur1_pos_y1 && pos_y2[n] < mur1_pos_y2)
            {
                v_xs2[n] *= -forcerebond_x;
                pos_x2[n] = mur1_pos_x2 + 1;
            }
            //y++ //
            if ((pos_x2[n] > mur1_pos_x1 && pos_x2[n] < mur1_pos_x2) && pos_y[n]<mur1_pos_y1 && pos_y2[n]>mur1_pos_y1)
            {
                v_ys2[n] *= -forcerebond_y;
                pos_y2[n] = mur1_pos_y1 - 1;
            }
            //y-- //
            if ((pos_x2[n] > mur1_pos_x1 && pos_x2[n] < mur1_pos_x2) && pos_y[n] > mur1_pos_y2 && pos_y2[n] < mur1_pos_y2)
            {
                v_ys2[n] *= -forcerebond_y;
                pos_y2[n] = mur1_pos_y2 + 1;
            }

            //collision entre les particule



            //rebond
            //y
            if (pos_y2[n]<0 || pos_y2[n]>window_size_y - shape_size)
            {
                //rebond de vitesse
                v_ys2[n] = v_ys2[n] * (-forcerebond_y);

                //rebond de position
                if (pos_y2[n] < 0)
                {
                    pos_y2[n] *= -1;

                    //collisiont_count++;
                    //if(nb_shape_to_remove = collisiont_count && nb_shape_to_remove != 0)
                    //{
                     //   nb_shape--;
                     //   collisiont_count = 0;
                    //}
                    //pos_y2[n] = 0;
                }
                else
                {
                    pos_y2[n] = (pos_y2[n] + shape_size - window_size_y) * -1 + window_size_y - shape_size;
                    //pos_y2[n] = window_size_y-shape_size;
                }


            }
            //x
            if (pos_x2[n]<0 || pos_x2[n]>window_size_x - shape_size)
            {
                //rebond de vitesse
                v_xs2[n] = v_xs2[n] * (-forcerebond_x);

                //rebond de position
                if (pos_x2[n] < 0)
                {
                    pos_x2[n] *= -1;
                    //pos_x2[n] = 0;
                }
                else
                {
                    pos_x2[n] = (pos_x2[n] + shape_size - window_size_x) * -1 + window_size_x - shape_size;
                    //pos_x2[n] = window_size_x-shape_size;
                }
            }

            //frotement
            v_xs2[n] *= frotement;
            v_ys2[n] *= frotement;
            //v_xs2[n] = pow(v_xs2[n],frotement/v_xs2[n]);
            //v_ys2[n] = pow(v_ys2[n],frotement/v_ys2[n]);

        }


        //antigraviterlocal += -50;
        //cout<<"enti: "<<frotement <<endl;
        //frotement = (1/float(pow(NumberOfFrame+1,0.5)));
        //if(nb_shape<nb_shape2)
        //{
        //   nb_shape = (int(NumberOfFrame)/5);
        //}

        sleep(milliseconds(1000 / delay));
        if (NumberOfFrame % 10 == 0 && log_onoff == 1)
        {

            cout << "complexity : " << complexity << endl;
            cout << "nb_shape : " << nb_shape << endl;

            // cout<<nbinter_max<<endl;
            cout << "--------------------\n" << NumberOfFrame << endl;
        }
        NumberOfFrame++;
        complexity = 0;
    }

    return 0;
}
