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
    std::vector<std::vector<int>> world={
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int row=world.size();
    int col=world[0].size();

    std::vector<std::vector<int>> figure_selected;

    void draw(sf::RenderWindow& window){
        sf::RectangleShape wall(sf::Vector2f(TILE, TILE));
        //wall.setFillColor(sf::Color::Blue);

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){ 
                if(world[i][j]==1){
                    wall.setFillColor(sf::Color::Blue);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==2){
                    wall.setFillColor(sf::Color::Red);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==3){
                    wall.setFillColor(sf::Color::Green);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==4){
                    wall.setFillColor(sf::Color::Yellow);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==5){;
                    wall.setFillColor(sf::Color::Magenta);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==6){
                    wall.setFillColor(sf::Color::White);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==7){
                    wall.setFillColor(sf::Color::Cyan);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }else if(world[i][j]==8){
                    wall.setFillColor(sf::Color::Blue);
                    wall.setPosition({float(j*TILE), float(i*TILE)});
                    window.draw(wall);
                }
            }
        }
    }
};

struct I_PIECE{ 
    int amount=2;

    std::vector<std::vector<int>> i_piece={
            {2},
            {2},
            {2},
            {2}
    };

    std::vector<std::vector<int>> i_piece_1={
        {2,2,2,2}
    };

    std::vector<std::vector<int>> extractVector(int& x){
        if(x==1) return i_piece;
        return i_piece_1;
    }
};

struct O_PIECE{
    int amount=1;

    std::vector<std::vector<int>> o_piece={
            {3,3},
            {3,3}
    };
};

struct T_PIECE{
    int amount=4;

    std::vector<std::vector<int>> t_piece={
            {4,4,4},
            {0,4,0}
        };

    std::vector<std::vector<int>> t_piece_1={
            {0,4},
            {4,4},
            {0,4}
        };

    std::vector<std::vector<int>> t_piece_2={
            {0,4,0},
            {4,4,4}
        };

    std::vector<std::vector<int>> t_piece_3={
            {4,0},
            {4,4},
            {4,0}
        };

    std::vector<std::vector<int>> extractVector(int& x){
        if(x==1) return t_piece;
        else if(x==2) return t_piece_1;
        else if(x==3) return t_piece_2;
        return t_piece_3;
    }
};

struct S_PIECE{
    int amount=2;

    std::vector<std::vector<int>> s_piece={
            {0,5,5},
            {5,5,0}
        };

    std::vector<std::vector<int>> s_piece_1={
            {5,0},
            {5,5},
            {0,5}
        };

    std::vector<std::vector<int>> extractVector(int& x){
        if(x==1) return s_piece;
        return s_piece_1;
    }
};

struct Z_PIECE{
    int amount=2;

    std::vector<std::vector<int>> z_piece={
            {6,6,0},
            {0,6,6}
        };

    std::vector<std::vector<int>> z_piece_1={
            {0,6},
            {6,6},
            {6,0}
        };

    std::vector<std::vector<int>> extractVector(int& x){
        if(x==1) return z_piece;
        return z_piece_1;
    }
};

struct L_PIECE{
    int amount=4;

    std::vector<std::vector<int>> l_piece={
            {7,0},
            {7,0},
            {7,7}
        };

    std::vector<std::vector<int>> l_piece_1={
            {7,7,7},
            {7,0,0}
        };

    std::vector<std::vector<int>> l_piece_2={
            {7,7},
            {0,7},
            {0,7}
        };

    std::vector<std::vector<int>> l_piece_3={
            {0,0,7},
            {7,7,7}
        };

    std::vector<std::vector<int>> extractVector(int& x){
        if(x==1) return l_piece;
        else if(x==2) return l_piece_1;
        else if(x==3) return l_piece_2;
        return l_piece_3;
    }
};

struct J_PIECE{
    int amount=4;

    std::vector<std::vector<int>> j_piece={
            {0,8},
            {0,8},
            {8,8}
        };

    std::vector<std::vector<int>> j_piece_1={
            {8,0,0},
            {8,8,8}
        };

    std::vector<std::vector<int>> j_piece_2={
            {8,8},
            {8,0},
            {8,0}
        };

    std::vector<std::vector<int>> j_piece_3={
            {8,8,8},
            {0,0,8}
        };

    std::vector<std::vector<int>> extractVector(int& x){
        if(x==1) return j_piece;
        else if(x==2) return j_piece_1;
        else if(x==3) return j_piece_2;
        return j_piece_3;
    }
};

struct User{
    int x;
    int amount;
    int _x=1, _y=15; 
    int prev_x=_x, prev_y=_y; //ESTADOS ANTERIORES
    int rotation_state=1;
    bool bottom_change=true;
    bool rotatePressed=true;

    enum Figure{
        I_piece, O_piece, T_piece, S_piece, Z_piece,
        L_piece, J_piece
    };
    Figure figure;

    void selection_figure(I_PIECE*& _i_piece, O_PIECE*& _o_piece, 
                         T_PIECE*& _t_piece, S_PIECE*& _s_piece, 
                         Z_PIECE*& _z_piece, L_PIECE*& _l_piece, 
                         J_PIECE*& _j_piece, World*& _world){
        x=_world->row-2; //desde la fila dos hacia abajo

        if(bottom_change){
            _x=1; //ESTADOS INICIALES
            _y=15;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1,7);

            int dieRoll=distrib(gen);

            switch(dieRoll){
                case 1:
                    _world->figure_selected=_i_piece->i_piece; 
                    figure=I_piece;
                    amount=_i_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
                case 2:
                    _world->figure_selected=_o_piece->o_piece; 
                    figure=O_piece;
                    amount=_o_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
                case 3:
                    _world->figure_selected=_t_piece->t_piece;
                    figure=T_piece;
                    amount=_t_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
                case 4:
                    _world->figure_selected=_s_piece->s_piece; 
                    figure=S_piece;
                    amount=_s_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
                case 5:
                    _world->figure_selected=_z_piece->z_piece;
                    figure=Z_piece;
                    amount=_z_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
                case 6:
                    _world->figure_selected=_l_piece->l_piece; 
                    figure=L_piece;
                    amount=_l_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
                case 7:
                    _world->figure_selected=_j_piece->j_piece; 
                    figure=J_piece;
                    amount=_j_piece->amount;
                    rotation_state=1;
                    bottom_change=false;
                    break;
            }
        } 
    }

    void handleInput(I_PIECE*& _i_piece, O_PIECE*& _o_piece, 
                    T_PIECE*& _t_piece, S_PIECE*& _s_piece, 
                    Z_PIECE*& _z_piece, L_PIECE*& _l_piece, 
                    J_PIECE*& _j_piece, World*& _world){

            if(_world->figure_selected.empty()) return;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) move_left(_world);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) move_right(_world);

            bool currentK=sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K);

            if(currentK && !rotatePressed){ 
                change_figure(_i_piece, _o_piece, _t_piece, _s_piece, _z_piece, _l_piece,
                _j_piece, _world);
            }

            rotatePressed=currentK;
    } 

    void change_figure(
            I_PIECE* _i_piece, O_PIECE*& _o_piece, 
            T_PIECE*& _t_piece, S_PIECE*& _s_piece, 
            Z_PIECE*& _z_piece, L_PIECE*& _l_piece, 
            J_PIECE*& _j_piece,
            World*& _world){

        if(figure==O_piece) return;
        
        auto backup=_world->figure_selected;
        int old_state=rotation_state;

        rotation_state++;
        if(rotation_state>amount) rotation_state=1;

        if(figure==I_piece) _world->figure_selected=_i_piece->extractVector(rotation_state);
        //else if(figure==O_piece) return; //porque solo tiene uno, asi que no pase nada
        else if(figure==T_piece) _world->figure_selected=_t_piece->extractVector(rotation_state);
        else if(figure==S_piece) _world->figure_selected=_s_piece->extractVector(rotation_state);
        else if(figure==Z_piece) _world->figure_selected=_z_piece->extractVector(rotation_state);
        else if(figure==L_piece) _world->figure_selected=_l_piece->extractVector(rotation_state);
        else if(figure==J_piece) _world->figure_selected=_j_piece->extractVector(rotation_state);

        //ROTACION INVALIDA
        if(!canMove(_x, _y, _world)){
            _world->figure_selected=backup;
            rotation_state=old_state;
        }
    }

    void move_left(World*& _world){
        if(canMove(_x, _y-1, _world)){
            prev_y=_y;
            _y--;
        }
    }

    void move_right(World*& _world){
        if(canMove(_x, _y+1, _world)){
            prev_y=_y;
            _y++;
        }
    }

    bool canMove(int testX, int testY, World* _world){ //MOTOR DE COLISIONES UNIVERSAL
        for(int i=0; i<_world->figure_selected.size(); i++){
            for(int j=0; j<_world->figure_selected[i].size(); j++){
                
                if(_world->figure_selected[i][j]==0) continue;

                int wx=testX+i;
                int wy=testY+j;

                if(wx<0 || wx>=_world->row) return false;
                if(wy<0 || wy>=_world->col) return false;

                if(_world->world[wx][wy]!=0) return false;
            }
        }

        return true;
    }

    void inspection(World*& _world){
        bool hit=false;

        for(int i=0; i<_world->figure_selected.size(); i++){
            for(int j=0; j<_world->figure_selected[i].size(); j++){

                if(_world->figure_selected[i][j]!=0){
                    //solo estoy inspeccionando abajo, no laterales, por eso las 
                    //figuras se traspasan
                    
                    //REGLA DE ORO DEL TETRIS:
                    //PREDICE -> VERIFICA -> APLICA
                    
                    int nx=_x+i+1;
                    int ny=_y+j;

                    //TOCAR PISO O TOCAR OTRA PIEZA
                    if(nx>=_world->row) hit=true;
                    else if(ny>=0 && ny<_world->col && _world->world[nx][ny]!=0) hit=true;
                }
            }
        }
        
        if(hit){
            bottom_change=true;

            for(int i=0; i<_world->figure_selected.size(); i++){
                for(int j=0; j<_world->figure_selected[i].size(); j++){
                    
                    //SOLIDIFICA EN EL MAPA ORIGINAL
                    if(_world->figure_selected[i][j]!=0){
                        if(_x+i>=0 && _x+i<_world->row &&
                           _y+j>=0 && _y+j<_world->col) _world->world[_x+i][_y+j]=_world->figure_selected[i][j];
                    }
                }
            }
            _world->figure_selected.clear();
            clearLines(_world);
        }
    }

    void clearLines(World*& w){
        for(int i=w->row-2; i>=1; i--){
            bool full=true;

            for(int j=1; j<w->col-1; j++){
                if(w->world[i][j]==0){
                    full=false;
                    break;
                }
            }

            if(full){
                //BAJA T ODO
                for(int x=i; x>0; x--){
                    w->world[x]=w->world[x-1];
                }

                //FILA NUEVA ARRIBA
                //w->world[0]=std::vector<int>(w->col, 0);
                std::vector<int> newRow(w->col, 0);
                newRow[0]=1;
                newRow[w->col-1]=1;
                w->world[1]=newRow;

                //VOLVER A REVISAR LA MISMA FILA
                i++;
            }
        }
    }

    void draw(sf::RenderWindow& window, World*& _world, float& alpha){
        sf::RectangleShape figure;
        figure.setSize(sf::Vector2f(TILE-1, TILE-1));
        //figure.setFillColor(sf::Color::Red);

        float interPx=prev_x + (_x-prev_x) * alpha;
        float interPy=prev_y + (_y-prev_y) * alpha;

        for(int i=0; i<_world->figure_selected.size(); i++){
            for(int j=0; j<_world->figure_selected[i].size(); j++){
                if(_world->figure_selected[i][j]!=0){

                    float drawX=interPx+i;
                    float drawY=interPy+j;

                    if(drawX>=0 && drawX < _world->row && 
                       drawY>=0 && drawY < _world->col){

                        if(_world->figure_selected[i][j]==2){
                            figure.setFillColor(sf::Color::Red);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }else if(_world->figure_selected[i][j]==3){
                            figure.setFillColor(sf::Color::Green);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }else if(_world->figure_selected[i][j]==4){
                            figure.setFillColor(sf::Color::Yellow);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }else if(_world->figure_selected[i][j]==5){;
                            figure.setFillColor(sf::Color::Magenta);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }else if(_world->figure_selected[i][j]==6){
                            figure.setFillColor(sf::Color::White);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }else if(_world->figure_selected[i][j]==7){
                            figure.setFillColor(sf::Color::Cyan);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }else if(_world->figure_selected[i][j]==8){
                            figure.setFillColor(sf::Color::Blue);
                            figure.setPosition({drawY*TILE, drawX*TILE});
                            window.draw(figure);
                        }
                    }
                }
            }
        }
    }

    //if(si llega al final del mapa) solidificar();
    //if(linea completa) eliminar linea y añadir linea();
};

void execute(){
    World* _world=new World;
    User* _user=new User;

    I_PIECE* _i_piece=new I_PIECE; 
    O_PIECE* _o_piece=new O_PIECE;
    T_PIECE* _t_piece=new T_PIECE; 
    S_PIECE* _s_piece=new S_PIECE; 
    Z_PIECE* _z_piece=new Z_PIECE; 
    L_PIECE* _l_piece=new L_PIECE;
    J_PIECE* _j_piece=new J_PIECE;

    bool game=true;

    sf::RenderWindow window{
        sf::VideoMode({
            static_cast<unsigned>(_world->row*TILE),
            static_cast<unsigned>(_world->col*TILE)
            }), 
        "TETRIS SFML!"
    };

    //---------------ZONA CLOCK----------------
    sf::Clock clock;
    float timer=0;
    float delay=0.07;
    //-----------------------------------------

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
        }
        //ZONA PARA OBTENER NUEVA FIGURA
        _user->selection_figure( //tal vez esto lo ponga aqui para que el cambio no sea tan rapido
                _i_piece, _o_piece, _t_piece, _s_piece,
                _z_piece, _l_piece, _j_piece, _world
        );
        //_user->inspection(_world);

        _user->prev_x=_user->_x;
        _user->prev_y=_user->_y;
        //--------------ZONA CLOCK/INPUT-------------------------
        float t=clock.restart().asSeconds();
        timer+=t;

        if(timer>delay){ 
            //_user->inspection(_world);
            //if(!_world->figure_selected.empty()) _user->_x++;
            if(_user->canMove(_user->_x+1, _user->_y, _world)) _user->_x++;
            else _user->inspection(_world);
            
            _user->handleInput(_i_piece, _o_piece, _t_piece, _s_piece, _z_piece, _l_piece, _j_piece, _world);
            timer-=delay;
        }

        float alpha=timer/delay;

        //-------------------------------------------------------
        
        //ZONA DE GRAFICAS
        window.clear();

        _user->draw(window, _world, alpha);
        _world->draw(window); //esto dibuja el mural azul alrededor

        window.display();
    }
}

int main(){
    execute();

    // sale del loop principal
    delete _world;
    delete _user;
    delete _i_piece;
    delete _o_piece;
    delete _t_piece;
    delete _s_piece;
    delete _z_piece;
    delete _l_piece;
    delete _j_piece;

    return 0;
}

//g++ -o m1 main1.cpp -lsfml-graphics -lsfml-window -lsfml-system
