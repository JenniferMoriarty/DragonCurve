#this code doesn't work yet
import pygame
import math
import cmath

pygame.init()  #sets up pygame
pygame.display.set_caption("dragon")  # sets the window title
screen = pygame.display.set_mode((800, 800))  # creates game screen
screen.fill((0,0,0)) #wipe screen black

def DrawDragonLine(level, direction, x1, y1, dx, dy):

    if level <= 0:
        #al_draw_line(x1, y1, x1 + dx, y1 + dy, al_map_rgb(5*dx+50, 10*dx, 50), 1);
        pygame.draw.line(screen, (255, 255, 255), (x1,y1), (x1+dx, y1+dx), 2)
        pygame.display.flip()

    else:
        #cut the length in half
        nx = dx / 2
        ny = dy / 2
        print("setting d2, level is ", level)
        #make a turn
        dx = -ny + nx;
        dy = nx + ny;


    if direction == 'r':
        #Turn to the right.
        DrawDragonLine(level - 1, 'r', x1, y1, dx, dy);
        x2 = x1 + dx;
        y2 = y1 + dy;
        DrawDragonLine(level - 1, 'l', x2, y2, dy, -dx);
        
    else:
        #Turn to the left.
        DrawDragonLine(level - 1, 'r', x1, y1, dy, -dx);
        x2 = x1 + dy;
        y2 = y1 - dx;
        DrawDragonLine(level - 1, 'l', x2, y2, dx, dy);
        
#end function definition--------------------------------------- 
print("hello")


#this controls our game loop
doexit = False;

while doexit == False:

    level = 10

    #mess with these!
    DrawDragonLine(level, 'r', 200,200,500,500);

 
    pygame.display.flip()
   
