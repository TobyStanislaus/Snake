#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include <algorithm>

void clearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}


const int width = 20;
const int height = 10;


struct Point {
    int x;
    int y;
    Point(int x_a, int y_a){
        x= x_a;
        y= y_a;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};


using Field = std::vector<std::vector<char>>;
using Body = std::vector<Point>;


struct Snake{
    int x = 0;
    int y = 0;
    Body body;
    char direction = 'd';

    Snake(){};
      
    bool move(Field& field){
        if (direction == 'u'){y-=1;}
        else if (direction == 'd'){y+=1;}
        else if (direction == 'l'){x-=1;}
        else if (direction == 'r'){x+=1;}
        Point newpoint{x, y};
        if (!check_move(field, newpoint)){return false;}
        body.insert(body.begin(), newpoint);
        return true;
    }

    bool check_move(Field& field, Point newpoint){
        // checking bounds
        if ((x<0)||(y<0)||(x>=field[0].size())||(y>=field.size())){
            return false;
        }
        // checking its not crossed over itself
        if (!(std::find(body.begin(), body.end(), newpoint) == body.end())){
            return false;
        }
        return true;
    }


    Field place_snake(Field field){
        int temp_x;
        int temp_y;
        for (const auto& part : body){
            temp_x = part.x;
            temp_y = part.y;
            field[temp_y][temp_x] = '0';
        }
        return field;
    }

};


void display_field(Field field){
    clearScreen();
    for (const auto&row : field){
        for (const auto&square : row){
            std::cout<< square << ' ';
        }
        std::cout<<"\n";
    }
}


int main(){
    Snake snake;

    bool survived = true;
    Field newfield;
    Field field(height, std::vector<char>(width, ' '));


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

        survived = snake.move(field);
        newfield = snake.place_snake(field);

        display_field(newfield);
        if (!survived){
            std::cout<<"You Lost!";
            break;
        }

       

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}