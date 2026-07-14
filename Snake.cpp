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

std::random_device rd;
std::mt19937 gen(rd());



void initialise_pos_positions(Body& possible_positions){
    for (int i=0;i<width;i++){
        for (int j=0; j<height; j++){
            possible_positions.push_back(Point(i,j));
        }
    }
}



struct Snake{
    int x = 0;
    int y = 0;
    Body body;
    char direction = 'd';
    Body possible_positions;

    Snake(){
        initialise_pos_positions(possible_positions);

        body.insert(body.begin(), Point{0,0});

        possible_positions.erase(
        std::remove(possible_positions.begin(),
                    possible_positions.end(),
                    Point{0, 0}),
        possible_positions.end());

    };
      
    bool move(Field& field){
        if (direction == 'u'){y-=1;}
        else if (direction == 'd'){y+=1;}
        else if (direction == 'l'){x-=1;}
        else if (direction == 'r'){x+=1;}

        Point newpoint{x, y};
        if (check_move(field, newpoint)==false){return false;}

        body.insert(body.begin(), newpoint);


        possible_positions.erase(
            std::remove(possible_positions.begin(),
                        possible_positions.end(),
                        Point{x, y}),
            possible_positions.end());

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


    void place_snake(Field& field){
        for (const auto& part : body){
            field[part.y][part.x] = '0';
        }
    }


    bool check_fruit(Point fruit){
        if ((x==fruit.x)&&(y==fruit.y)){return true;}
        return false;
    }


    void spawn_fruit(Point& fruit){
        std::uniform_int_distribution<> dist(0, possible_positions.size()-1);
        int random_number = dist(gen);
        fruit = possible_positions[random_number];
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

    snake.spawn_fruit(fruit);

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            // Up Down Left Right
            if (key == 'w'&&snake.direction!='d'){snake.direction = 'u';}
            else if (key == 's'&&snake.direction!='u'){snake.direction = 'd';}
            else if (key == 'a'&&snake.direction!='r'){snake.direction = 'l';}
            else if (key == 'd'&&snake.direction!='l'){snake.direction = 'r';}
        }

        survived = snake.move(field);
        snake.place_snake(field);


        if (snake.check_fruit(fruit)){
            snake.spawn_fruit(fruit);
            field[fruit.y][fruit.x] = 'A';
        }else{          
        remove_part = snake.body.back();
        field[remove_part.y][remove_part.x] = ' ';
        snake.body.pop_back();

        snake.possible_positions.push_back(remove_part);
        }


        if (field[fruit.y][fruit.x] != '0'){
            field[fruit.y][fruit.x] = 'A';
        }
        display_field(field);

        if (!survived){
            std::cout<<"You Lost!";
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

}