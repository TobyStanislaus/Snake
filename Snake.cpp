#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>

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
using Field = std::vector<std::vector<char>>;


class Snake{
    public :
    int x = 0;
    int y = 0;
    int length = 1;
    char direction = 'd';


    Snake(){};
      
    void move(){
        if (direction == 'u'){y-=1;}
        else if (direction == 'd'){y+=1;}
        else if (direction == 'l'){x-=1;}
        else if (direction == 'r'){x+=1;}
    }

    bool check_and_update_position(Field& field){
        if (x<0||y<0||x>=field[0].size()||y>=field.size()){return false;}
        if ((field[y][x] == '0')){return false;}
        field[y][x] = '0';
        return true;
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
    bool survived;
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
        snake.move();
        survived = snake.check_and_update_position(field);

        if (!survived){
            std::cout<<"You Lost!";
            break;
        }

        display_field(field);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

}