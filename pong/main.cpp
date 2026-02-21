#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <deque>
#include <cmath>

constexpr int TILE=13;
constexpr int MAX_ANGLE=3;

struct World{
    float _player1, _player2;

    std::vector<std::vector<int>> world={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int row=world.size();
    int col=world[0].size();

    void draw(sf::RenderWindow& window){
        sf::RectangleShape wall(sf::Vector2f(TILE, TILE));
        wall.setFillColor(sf::Color::Green);

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(world[i][j]==1){
                    //setPosition(columna, fila);
                    wall.setPosition({float(j*TILE),float(i*TILE)});
                    window.draw(wall);
                }
            }
        }
    }
};

struct Player1{
    int y=2;
    float start_x;
    float speed=1.f;
    int paddle_height=3;
    sf::RectangleShape player;

    int prev_x, prev_y;

    Player1(){
        player.setSize(sf::Vector2f(TILE, TILE)); //puede ser TILE-1.f, la caja universal menos 1, se vera una pequeña linea diferencial
        player.setPosition(sf::Vector2f(50.f, 50.f)); 
    } 

    virtual void init(World** _world){
        start_x=((*_world)->row/2)-(paddle_height/2);
        player.setFillColor(sf::Color::Red);
    }

    virtual void handleInput(World** _world){
        prev_x=start_x;
        prev_y=y;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) start_x-=speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) start_x+=speed;

        //LIMITES
        if(start_x<1) start_x=1;
        if(start_x+paddle_height>=(*_world)->row-1) start_x=((*_world)->row-1)-paddle_height;
    }

    virtual void draw(sf::RenderWindow& window, World** _world, float& alpha){
        float new_x=prev_x + (start_x - prev_x) * alpha;
        float new_y=prev_y + (y - prev_y) * alpha;

        for(int i=0; i<paddle_height; i++){
            player.setPosition({float(new_y*TILE), float((new_x+i)*TILE)});
            (*_world)->_player1=float((new_x+i)*TILE); //actualizacion de datos en _world
            window.draw(player);
        }
    }
};

/*FORMUAL GENERAL PARA MOVIMIENTO SUAVE
 float new_x=prev_x + (x-prev_x) * alpha;
 float new_y=prev_y + (y-prev_y) * alpha;
  */

struct Player2: Player1{
    void init(World** _world) override{
        y=(*_world)->col-3;
        start_x=((*_world)->row/2)-(paddle_height/2);
        player.setFillColor(sf::Color::Cyan);
    }

    void handleInput(World** _world) override{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) start_x--;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) start_x++;

        //LIMITES
        if(start_x<1) start_x=1;
        if(start_x+paddle_height>=(*_world)->row-1) start_x=((*_world)->row-1)-paddle_height;
    }

    void draw(sf::RenderWindow& window, World** _world, float& alpha) override{
        for(int i=0; i<paddle_height; i++){
            player.setPosition({float(y*TILE), float((start_x+i)*TILE)});
            (*_world)->_player2=float((start_x+i)*TILE);
            window.draw(player);
        }
    }
};

struct Ball{
    int prev_x, prev_y; //posicion anterior
    int x, y;
    int dx=1, dy=1;
    sf::CircleShape ball;
    std::vector<float> player1, player2;

    void init(World** _world){
        x=(*_world)->row/2; //posicion inicial
        y=(*_world)->col/2;

        ball.setRadius(5.f);
        ball.setFillColor(sf::Color::Blue);
        //ball.setOutlineThickness(10.f);
    }

    void recognition(World** _world){
        player1.clear();
        player2.clear();

        for(int i=0; i<3; i++){
            player1.push_back((*_world)->_player1+i);
            player2.push_back((*_world)->_player2+i);
        }
    }

    bool verify(float& coord, const std::vector<float>& player){
        return std::find(player.begin(), player.end(), coord) != player.end();
    }

    void update(World** _world){
        recognition(_world);

        //AVANZA DERECHA
        if(y+dy<1) dy=1;
        float x_dx=static_cast<float>(x+dx);
        if(y+dy==2 && verify(x_dx, player1)){
            dy=1;

            int center=static_cast<int>(std::round(player1[player1.size()/2]));
            dx=std::clamp((x+dx)-center, -1, 1);
            dx=std::clamp(dx, -MAX_ANGLE, MAX_ANGLE);
        }

        //AVANZA ABAJO
        if(y+dy>(*_world)->col-2) dy=-1;
        float x_dy=static_cast<float>(x+dy);
        if(y+dy==(*_world)->col-3 && verify(x_dy, player2)){
            dy=-1;

            int center=static_cast<int>(std::round(player2[player2.size()/2]));
            dx=std::clamp((x+dx)-center, -1, 1);
            dx=std::clamp(dx, -MAX_ANGLE, MAX_ANGLE);
        }

        //BAJA Y SUBE
        if(x+dx<1) dx=1;
        if(x+dx>(*_world)->row-2) dx=-1;

        prev_x=x;
        prev_y=y;

        x+=dx;
        y+=dy;
    }

    void draw(sf::RenderWindow& window, float& alpha){
        float new_x=prev_x + (x-prev_x) * alpha;
        float new_y=prev_y + (y-prev_y) * alpha;

        ball.setPosition(sf::Vector2f(new_y*TILE, new_x*TILE));
        window.draw(ball);
    }
};

void execute(){

    World* _world=new World;
    Player1* _player1=new Player1;
    Player2* _player2=new Player2;
    Ball* _ball=new Ball;

    _player1->init(&_world); //inicializa posicion seguro
    _player2->init(&_world);
    _ball->init(&_world);

    sf::RenderWindow window{
        sf::VideoMode({
            static_cast<unsigned>(_world->col*TILE),
            static_cast<unsigned>(_world->row*TILE)
            }), 
        "Pong"
    };

    //---------------------
    sf::Clock clock;
    float timer=0;
    float delay=0.07;
    //---------------------

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is <sf::Event::Closed>()) window.close();
        }
        //ZONA INPUT IBA AQUI, LO EH MOVIDO A ZONA CLOCK
        _player1->handleInput(&_world);
        _player2->handleInput(&_world);

        //---------------ZONA CLOCK---------------------------
        float t=clock.restart().asSeconds();
        timer+=t;

        if(timer>delay){
            _player1->handleInput(&_world);
            _player2->handleInput(&_world);
            _ball->update(&_world);
            timer-=delay;
        }

        float alpha=timer/delay;
        //---------------------------------------------------
        
        //ZONA DE GRAFICAS
        window.clear();

        _world->draw(window);
        _player1->draw(window, &_world, alpha);
        _player2->draw(window, &_world, alpha);
        _ball->draw(window, alpha);

        window.display(); 
    }
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
