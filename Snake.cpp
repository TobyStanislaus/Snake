#include <iostream>
#include <conio.h>
#include <vector>

const int width = 20;
const int height = 10;

class Snake{
    public :
    int x = 0;
    int y = 0;
    int length = 1;
    char direction = 'u';


    Snake(){};
      
    void move(){
        if (direction == 'u'){y+=1;}
        else if (direction == 'd'){y-=1;}
        else if (direction == 'l'){x-=1;}
        else if (direction == 'r'){x+=1;}
    }

    void update_position(){

    }
};





int main(){
    Snake snake;
    std::vector<std::vector<char>> field(height, std::vector<char>(width, ' '));


    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            // Up Down Left Right
            if (key == 'w'){snake.direction = 'u';}
            else if (key == 's'){snake.direction = 'd';}
            else if (key == 'a'){snake.direction = 'l';}
            else if (key == 'd'){snake.direction = 'r';}
        }

        // update game
        // draw screen
        // sleep
    }

}