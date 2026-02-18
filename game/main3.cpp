#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <deque>
#include <cmath>

constexpr int TILE=13;

struct Platform{
    int x_apple, y_apple;
    int x_snake, y_snake;
    int _score=0;

    std::vector<std::vector<int>> platform={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    std::vector<std::vector<int>> copy_plat=platform;

    int row=platform.size();
    int col=platform[0].size();

    void print(sf::RenderWindow& window){

        sf::RectangleShape wall(sf::Vector2f(TILE, TILE));
        wall.setFillColor(sf::Color::Green);

        for(int x=0;x<platform.size();x++){
            for(int y=0;y<platform[0].size();y++){
                if(copy_plat[x][y]==1){
                    wall.setPosition({float(y*TILE),float(x*TILE)});
                    window.draw(wall);
                }
            }
        }
    }
};

int Rand(char object, Platform& platform){
    //STATIC PARA QUE SE INICIALIZE UNA SOLA VEZ!!!!!!
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    if(object=='A'){
        std::uniform_int_distribution<int> dist(1, platform.row-2);
        return dist(rng);
    }else if(object=='S'){
        std::uniform_int_distribution<int> dist(1, platform.col-2);
        return dist(rng);
    }

    //caso invàlido
    return -1;
}

struct Apple{
    int x, y;
    sf::RectangleShape apple;

    Apple(){
        apple.setSize(sf::Vector2f(TILE-3.f, TILE-3.f));
        apple.setFillColor(sf::Color::Blue);
    }

    void init(Platform& _plat, const std::deque<std::pair<int,int>>& snake){
        while(true){
            x=1+rand()%(_plat.col-2);
            y=1+rand()%(_plat.row-2);

            bool collide=false;

            for(auto& s: snake){
                if(s.first==x && s.second==y){
                    collide=true;
                    break;
                }
            }

            if(!collide) break;
        }
    }

    void draw(sf::RenderWindow& win){
        apple.setPosition(sf::Vector2f(x*TILE, y*TILE));
        win.draw(apple);
    }
};

struct Snake{ 
    sf::RectangleShape player;
    std::deque<std::pair<int,int>> body;
    std::deque<std::pair<float,float>> prevBody;
    int score=0;

    enum Dir{ LEFT, DOWN, RIGHT, UP }; 

    Dir dir=RIGHT; //se empieza llendo a la derecha
    
    Snake(){
        player.setSize(sf::Vector2f(TILE-2.f, TILE-2.f));
        player.setPosition(sf::Vector2f(50.f, 50.f));
        player.setFillColor(sf::Color::Red);
    }

    void init(){
        body.clear();
        body.push_front({10,10}); //tile inicial
        dir=RIGHT;
        score=0; 
    }

    void handleInput(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && dir!=RIGHT) dir=LEFT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && dir!=UP) dir=DOWN;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && dir!=LEFT) dir=RIGHT;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && dir!=DOWN) dir=UP;
    }

    bool update(Platform& _platform, Apple& _apple, bool& game){
        prevBody.clear();
        for(auto& p: body){
            prevBody.push_back({float(p.first), float(p.second)});
        }

        int dx=0, dy=0;

        if(dir==LEFT) dx=-1;
        if(dir==RIGHT) dx=1;
        if(dir==UP) dy=-1;
        if(dir==DOWN) dy=1;

        auto [hx, hy]=body.front();

        int nx=hx+dx;
        int ny=hy+dy;

        //paredes
        if(nx<=0 || nx>=_platform.col-1 || ny<=0 || ny>=_platform.row-1) return false;

        //choque consigo mismo
        for(auto& s: body){
            if(s.first==nx && s.second==ny) return false;
        }

        body.push_front({nx, ny});
        
        bool ate=(nx==_apple.x && ny==_apple.y);

        if(!ate) body.pop_back();
        else{
            score++;
            _platform._score=score;
            _apple.init(_platform, body);
        }

        return true;
    }

    std::deque<std::pair<int,int>> returnBody(){
        return body;
    }

    void draw(sf::RenderWindow& window, float alpha){
        for(size_t i=0; i<body.size(); ++i){
            float currX=body[i].first;
            float currY=body[i].second;

            float prevX=currX;
            float prevY=currY;

            if(i<prevBody.size()){
                prevX=prevBody[i].first;
                prevY=prevBody[i].second;
            }

            float x=prevX + (currX-prevX) * alpha;
            float y=prevY + (currY-prevY) * alpha;

            player.setPosition(sf::Vector2f(x*TILE, y*TILE));
            window.draw(player);
        }
    }

    int Score(){ return score; }
};

void execute(){

    Platform _platform;
    Snake _snake;
    Apple _apple;
    bool game=true;

     sf::RenderWindow window(
             sf::VideoMode({
                 static_cast<unsigned>(_platform.col*TILE), 
                 static_cast<unsigned>(_platform.row*TILE)
                 }), 
             "SFML works!"
    ); 

    _snake.init();
    _apple.init(_platform, _snake.returnBody());

    //------------------------------------------------------
    //--------------LETRERO DE PERDISTE---------------------
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) std::cerr<<"No se pudo cargar la fuente\n";
    
    sf::Text text(font, "", 70);
    text.setFillColor(sf::Color::White);
    //------------------------------------------------------

    sf::Clock clock;
    float timer=0;

    //delay es el paso fijo de la simulacion, el tick del universo
    float delay=0.07; //si quieres mayor rapidez tienes que reducir delay

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) window.close();
        }

        _snake.handleInput();
        //--------------------------------------------
        //----------ZONA CLOCK------------------------
        float t=clock.restart().asSeconds(); //el latido universal del programa
        timer+=t; //tiempo acumulado, cuanto tiempo a pasado desde el ultimo tick logico

        if(game){
            if(timer>delay){ //si acumula suficiente tiempo arranca la logica
                game=_snake.update(_platform, _apple, game); //actualiza mapa
                timer-=delay; //resta el timer para empezar todo de nuevo
            }
        }else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
                _snake.init();
                _apple.init(_platform, _snake.returnBody());
                game=true;
                timer=0;
            }
        }

        float alpha=timer/delay; 
        //---------------------------------------------

        window.clear(); //fondo negro 

        _platform.print(window);
        _apple.draw(window);
        _snake.draw(window, alpha); //dibuja por donde va

        if(!game){
            text.setString("PERDISTE\nScore: " + std::to_string(_snake.Score()));
            text.setPosition(
                    sf::Vector2f((_platform.col*TILE)/4,
                    (_platform.row*TILE)/3)
            );
            window.draw(text);
        }

        window.display(); //finalizar el frame actual
    }
}

//INPUT -> UPDATE -> RENDER

int main(){ 
    execute();
    return 0;
}

//g++ -o m2 main2.cpp -lsfml-graphics -lsfml-window -lsfml-system
