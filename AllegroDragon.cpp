#include <stdio.h>
#include <allegro5/allegro.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

void DrawDragonLine(int level, char direction, float x1, float y1, float dx, float dy);

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *square = NULL;
   int level;

   //these two variables hold the x and y positions of the square
   //initalize these variables to where you want your square to start
   float square_x = 50;
   float square_y = 50;

   //here's our key states. they're all starting as "false" because nothing has been pressed yet.
   //the first slot represents "up", then "down", "left" and "right"
   bool key[4] = { false, false, false, false };

   //don't redraw until an event happens
   bool redraw = true;

   //this controls our game loop
   bool doexit = false;
 
al_init();
 
//get the keyboard ready to use
al_install_keyboard();
al_init_primitives_addon();

timer = al_create_timer(.02);
 
display = al_create_display(800,600);
 
square = al_create_bitmap(5,5);
 
al_set_target_bitmap(square);
 
al_clear_to_color(al_map_rgb(255, 255, 255));
 
al_set_target_bitmap(al_get_backbuffer(display));
 
event_queue = al_create_event_queue();
 
al_register_event_source(event_queue, al_get_display_event_source(display));
 
al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
//tell the event queue that it should take keyboard events, too
al_register_event_source(event_queue, al_get_keyboard_event_source());
 
al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   //so the game loop is set to act on "ticks" of the timer OR keyboard presses
   //OR the mouse closing the display
   while(!doexit)
   {
cout<<"please enter level:"<<endl;
cin>>level;
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
 //////////////////////////////////////////////////////////////////////////////////////////////////
 //here's the movement algorithm

      if(ev.type == ALLEGRO_EVENT_TIMER) {
 //if the up button is pressed AND we're still below the top wall,
 //move the box "up" by 4 pixels
         if(key[0] && square_y >= 0) {
            square_y -= 4.0;
         }
//if the down button is pressed AND we're still above the bottom wall
//move the box "down" by 4 pixels
         if(key[1] && square_y <= 480-32) {
            square_y += 4.0;
         }
//if the left button is pressed AND we're still right of the left wall
//move the box left by 4 pixels
         if(key[2] && square_x >= 0) {
            square_x -= 4.0;
         }
 
//if the left button is pressed AND we're still left of the right wall
//move the box right by 4 pixels
         if(key[3] && square_x <= 640 - 32) {
            square_x += 4.0;
         }
 
//redraw at every tick of the timer
         redraw = true;
      }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }

 //////////////////////////////////////////////////////////////////////////////////////////////////////
 //here's the algorithm that turns key presses into events
 //a "key down" event is when a key is pushed
 //while a "key up" event is when a key is released

 //has something been pressed on the keyboard?
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {

 //"keycode" holds all the different keys on the keyboard
         switch(ev.keyboard.keycode) {

//if the up key has been pressed
            case ALLEGRO_KEY_UP:
               key[0] = true;
               break;
 
  //if the down key has been pressed
            case ALLEGRO_KEY_DOWN:
               key[1] = true;
               break;
 
  //if the left key has been pressed
            case ALLEGRO_KEY_LEFT:
               key[2] = true;
               break;
//if the right key has been pressed
            case ALLEGRO_KEY_RIGHT:
               key[3] = true;
               break;
         }
      }
 //has something been released on the keyboard?
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[0] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[1] = false;
               break;
 
            case ALLEGRO_KEY_LEFT:
               key[2] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[3] = false;
               break;
 
//kill the program if someone presses escape
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
 
 //if the clock ticked but no other events happened, don't bother redrawing
    //  if(redraw && al_is_event_queue_empty(event_queue)) {
      //   redraw = false;
 
//paint black over the old screen, so the old square dissapears
         //al_clear_to_color(al_map_rgb(0,0,0));
 
//the algorithm above just changes the x and y coordinates
//here's where the bitmap is actually drawn somewhere else
        // al_draw_bitmap(square, square_x, square_y, 0);

         //mess with these!
      DrawDragonLine(level, 'r', 200.0,200.0,220.0,200.0);
        //drawSnow(level,20.0,280.0,280.0,280.0);
       // drawSnow(level,280.0,280.0,150.0,20.0);
        //drawSnow(level,150.0,20.0,20.0,280.0);
 
         al_flip_display();
     // }
   }
 
   al_destroy_bitmap(square);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}
 // Recursively draw the dragon curve between the two points.
void DrawDragonLine(int level, char direction, float x1, float y1, float dx, float dy)
{

   if (level <= 0)
    {

            al_draw_line(x1, y1, x1 + dx, y1 + dy, al_map_rgb(5*dx+50, 10*dx, 50), 1);


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
