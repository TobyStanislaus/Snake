#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include <random>
#include <string>
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

std::random_device rd;
std::mt19937 gen(rd());

struct Point {
    int x;
    int y;
    Point() = default;
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
    int y = 2;
    Body body;
    char direction = 'd';
    std::vector<int> possi_width;
    std::vector<int> possi_height;


    Snake(){
        possi_width.resize(width);
        possi_height.resize(height);

        std::iota(possi_width.begin(), possi_width.end(), 0);
        std::iota(possi_height.begin(), possi_height.end(), 0);

        body.insert(body.begin(), Point{0,0});
        body.insert(body.begin(), Point{0,1});
        body.insert(body.begin(), Point{0,2});
    };
      
    bool move(Field& field){
        if (direction == 'u'){y-=1;}
        else if (direction == 'd'){y+=1;}
        else if (direction == 'l'){x-=1;}
        else if (direction == 'r'){x+=1;}
        Point newpoint{x, y};
        if (!check_move(field, newpoint)){return false;}
        body.insert(body.begin(), newpoint);
        
        possi_width.erase(
            std::remove(possi_width.begin(), possi_width.end(), x),
            possi_width.end()
        );

        possi_height.erase(
            std::remove(possi_height.begin(), possi_height.end(), y),
            possi_height.end()
        );

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


    bool check_fruit(Point fruit){
        if ((x==fruit.x)&&(y==fruit.y)){return true;}
        return false;
    }


    void spawn_fruit(Field& field, Point& fruit){
        std::uniform_int_distribution<> w_dist(0, possi_width.size() - 1);
        fruit.x = possi_width[w_dist(gen)];

        std::uniform_int_distribution<> h_dist(0, possi_height.size() - 1);
        fruit.y = possi_height[h_dist(gen)];
    }
};


std::string create_line(int amount){
    std::string line = "";
    for (int i=0;i<amount;i++){
        line=line+"──";
    }
    return line;
}


void display_field(Field field){
    clearScreen();
    std::cout<< create_line(field[0].size()+1) <<std::endl;
    for (const auto&row : field){
        std::cout << "|";
        for (const auto&square : row){
            std::cout<< square << ' ';
        }
        std::cout<<"|\n";
    }
    std::cout<< create_line(field[0].size()+1) <<std::endl;
}


int main(){
    Snake snake;

    bool survived = true;
    Field newfield;
    Field field(height, std::vector<char>(width, ' '));
    Point remove_part{};
    Point fruit{};

    snake.spawn_fruit(field, fruit);

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


        if (snake.check_fruit(fruit)){
            snake.spawn_fruit(field, fruit);
            newfield[fruit.y][fruit.x] = 'A';
        }else{          
        remove_part = snake.body.back();
        snake.body.pop_back();

        snake.possi_width.push_back(remove_part.x);
        snake.possi_height.push_back(remove_part.y);
        }


        if (!(newfield[fruit.y][fruit.x] == '0')){
            newfield[fruit.y][fruit.x] = 'A';
        }
        display_field(newfield);

        if (!survived){
            std::cout<<"You Lost!";
            break;
        }

       

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

}