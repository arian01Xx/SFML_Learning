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
    int player1_rows[3]={0};
    int player2_rows[3]={0};

    int score1=0, score2=0;

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

        for(int i=0; i<paddle_height; i++){
            (*_world)->player1_rows[i]=static_cast<int>(start_x)+i;
        }
    }

    virtual void handleInput(World** _world){
        prev_x=static_cast<int>(start_x);
        prev_y=y;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) start_x-=speed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) start_x+=speed;

        //LIMITES
        if(start_x<1) start_x=1;
        if(start_x+paddle_height>=(*_world)->row-1) start_x=((*_world)->row-1)-paddle_height;

        for(int i=0; i<paddle_height; i++){
            (*_world)->player1_rows[i]=static_cast<int>(start_x)+i;
        }
    }

    virtual void draw(sf::RenderWindow& window, World** _world, float& alpha){
        float new_x=prev_x + (start_x - prev_x) * alpha;
        float new_y=prev_y + (y - prev_y) * alpha;

        for(int i=0; i<paddle_height; i++){
            player.setPosition({float(new_y*TILE), float((new_x+i)*TILE)});
           //(*_world)->_player1=float((new_x+i)*TILE); //actualizacion de datos en _world
            window.draw(player);
        }
    }
};

struct Player2: Player1{
    void init(World** _world) override{
        y=(*_world)->col-3;
        start_x=((*_world)->row/2)-(paddle_height/2);
        player.setFillColor(sf::Color::Cyan);

        for(int i=0; i<paddle_height; i++){
            (*_world)->player2_rows[i]=static_cast<int>(start_x)+i;
        }
    }

    void handleInput(World** _world) override{
        prev_x=static_cast<int>(start_x);
        prev_y=y;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) start_x--;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) start_x++;

        //LIMITES
        if(start_x<1) start_x=1;
        if(start_x+paddle_height>=(*_world)->row-1) start_x=((*_world)->row-1)-paddle_height;
        
        for(int i=0; i<paddle_height; i++){
            (*_world)->player2_rows[i]=static_cast<int>(start_x)+i;
        }
    }

    void draw(sf::RenderWindow& window, World** _world, float& alpha) override{
        float new_x=prev_x + (start_x - prev_x) * alpha;
        float new_y=prev_y + (y - prev_y) * alpha;

        for(int i=0; i<paddle_height; i++){
            player.setPosition({float(new_y*TILE), float((new_x+i)*TILE)});
            //(*_world)->_player2=float((new_x+i)*TILE);
            window.draw(player);
        }
    }
};

struct Ball{
    int prev_x, prev_y; //posicion anterior
    int x, y;
    int dx=1, dy=1;
    sf::CircleShape ball;
    std::vector<int> player1, player2;

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
            player1.push_back((*_world)->player1_rows[i]);
            player2.push_back((*_world)->player2_rows[i]);
        }
    }

    bool verify(int& coord, const std::vector<int>& player){
        return std::find(player.begin(), player.end(), coord) != player.end();
    }

    void update(World** _world){
        recognition(_world);

        //PREDICCION FUTURA
        int nx=x+dx;
        int ny=y+dy;

        //AVANZA IZQUIERDA (player1)
        if(dy<0 && ny<=2 && verify(nx, player1)){
            dy=1;

            int center=player1[player1.size()/2];
            dx=std::clamp(nx-center, -MAX_ANGLE, MAX_ANGLE);

            if(dy<0){
                (*_world)->score2++; 
            }
        }

        //AVANZA DERECHA (player2) 
        if(dy>0 && ny>=(*_world)->col-3 && verify(nx, player2)){
            dy=-1;

            int center=player2[player2.size()/2]; 
            dx=std::clamp(nx-center, -MAX_ANGLE, MAX_ANGLE);

            if(dy>=(*_world)->col-1){
                (*_world)->score1++; 
            }
        }

        //ZONA DE IDENTIFICACION DE META
        if(dy<0 && ny<1) (*_world)->score2++;
        if(dy>0 && ny>(*_world)->col-2) (*_world)->score1++;

        //TECHO/SUELO
        if(nx<1) dx=1;
        if(nx>(*_world)->row-2) dx=-1;

        if(ny<1) dy=1;
        if(ny > (*_world)->col-2) dy=-1; 

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

namespace Score{
    struct FirstScore{
        virtual void Run(sf::RenderWindow& window, sf::Text& text, World*& _world){
            text.setString(std::to_string(_world->score1));
            text.setPosition(
                    sf::Vector2f(20*TILE,5*TILE)
            );

            window.draw(text);
        }
    };

    struct SecondScore: FirstScore{
        void Run(sf::RenderWindow& window, sf::Text& text, World*& _world) override{
            text.setString(std::to_string(_world->score2));
            text.setPosition(
                    sf::Vector2f(40*TILE, 5*TILE)
            );

            window.draw(text);
        }
    };
} 

void execute(){

    World* _world=new World;
    Player1* _player1=new Player1;
    Player2* _player2=new Player2;
    Ball* _ball=new Ball;

    Score::FirstScore* firstScore=new Score::FirstScore;
    Score::SecondScore* secondScore=new Score::SecondScore;

    bool game=true;

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

    //-----------------------------------------------
    sf::Clock clock;
    float timer=0;
    float delay=0.07;
    //-----------------------------------------------
    
    //-----------NUMEROS DE PUNTAJE------------------
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) std::cerr<<"No se pudo cargar la fuente\n";

    sf::Text text(font, "", 70);
    text.setFillColor(sf::Color::White);
    //-----------------------------------------------

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is <sf::Event::Closed>()) window.close();
        } 

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
        firstScore->Run(window, text, _world);
        secondScore->Run(window, text, _world);
        _ball->draw(window, alpha); 

        window.display(); 
    } 
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
