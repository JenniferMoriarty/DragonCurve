#include <stdio.h>
#include <allegro5/allegro.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

//function declarations
void DrawDragonLine(int level, char direction, float x1, float y1, float dx, float dy);

int main(int argc, char** argv)
{
    //allegro variables
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* square = NULL;

    //game variables
    bool redraw = true;
    int level;
    bool doexit = false;

    //initalize allegro stuff
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    timer = al_create_timer(.02);
    display = al_create_display(800, 600);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    while (!doexit) //GAME LOOP-----------------------------------------
    {
        cout << "please enter level:" << endl;
        cin >> level;
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        

        DrawDragonLine(level, 'r', 200.0, 200.0, 220.0, 200.0); //recursive call


        al_flip_display();

    }//end game loop--------------------------------------------------------


    //free up memory before quitting
    al_destroy_bitmap(square);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

//FUNCTION DEFINITION
// Recursively draw the dragon curve between the two points.
void DrawDragonLine(int level, char direction, float x1, float y1, float dx, float dy)
{

    if (level <= 0)
    {
        al_draw_line(x1, y1, x1 + dx, y1 + dy, al_map_rgb(5 * dx + 50, 10 * dx, 50), 1);
    }
    else
    {
        //cut the length in half
        float nx = (float)(dx / 2);
        float ny = (float)(dy / 2);

        //make a turn
        float dx2 = -ny + nx;
        float dy2 = nx + ny;


        if (direction == 'r')
        {
            // Turn to the right.
            DrawDragonLine(level - 1, 'r', x1, y1, dx2, dy2);
            float x2 = x1 + dx2;
            float y2 = y1 + dy2;
            DrawDragonLine(level - 1, 'l', x2, y2, dy2, -dx2);
        }
        else
        {
            // Turn to the left.
            DrawDragonLine(level - 1, 'r', x1, y1, dy2, -dx2);
            float x2 = x1 + dy2;
            float y2 = y1 - dx2;
            DrawDragonLine(level - 1, 'l', x2, y2, dx2, dy2);
        }
    }
}
