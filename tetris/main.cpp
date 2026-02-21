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
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int row=world.size();
    int col=world[0].size();

    std::vector<std::vector<int>> figure_selected;

    void draw(sf::RenderWindow& window){
        sf::RectangleShape wall(sf::Vector2f(TILE, TILE));
        wall.setFillColor(sf::Color::Blue);

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(world[i][j]==1){
                    wall.setPosition({float(j*TILE), 
                                      float(i*TILE)});
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
    int rotation_state=1;
    bool bottom_change=true;

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
            _x=1;
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
                    break;
                case 2:
                    _world->figure_selected=_o_piece->o_piece; 
                    figure=O_piece;
                    amount=_o_piece->amount;
                    rotation_state=1;
                    break;
                case 3:
                    _world->figure_selected=_t_piece->t_piece;
                    figure=T_piece;
                    amount=_t_piece->amount;
                    rotation_state=1;
                    break;
                case 4:
                    _world->figure_selected=_s_piece->s_piece; 
                    figure=S_piece;
                    amount=_s_piece->amount;
                    rotation_state=1;
                    break;
                case 5:
                    _world->figure_selected=_z_piece->z_piece;
                    figure=Z_piece;
                    amount=_z_piece->amount;
                    rotation_state=1;
                    break;
                case 6:
                    _world->figure_selected=_l_piece->l_piece; 
                    figure=L_piece;
                    amount=_l_piece->amount;
                    rotation_state=1;
                    break;
                case 7:
                    _world->figure_selected=_j_piece->j_piece; 
                    figure=J_piece;
                    amount=_j_piece->amount;
                    rotation_state=1;
                    break;
            }
        } 
    }

    void handleInput(I_PIECE*& _i_piece, O_PIECE*& _o_piece, 
                    T_PIECE*& _t_piece, S_PIECE*& _s_piece, 
                    Z_PIECE*& _z_piece, L_PIECE*& _l_piece, 
                    J_PIECE*& _j_piece, World*& _world){

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) move_left(_world);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) move_right(_world);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) 
                    change_figure(_i_piece, _o_piece, _t_piece, _s_piece, _z_piece, _l_piece,
                    _j_piece, _world);
    } 

    void change_figure(
            I_PIECE* _i_piece, O_PIECE*& _o_piece, 
            T_PIECE*& _t_piece, S_PIECE*& _s_piece, 
            Z_PIECE*& _z_piece, L_PIECE*& _l_piece, 
            J_PIECE*& _j_piece,
            World*& _world){
        rotation_state++;
        if(rotation_state>amount) rotation_state=1;

        if(figure==I_piece) _world->figure_selected=_i_piece->extractVector(rotation_state);
        else if(figure==O_piece) return; //porque solo tiene uno, asi que no pase nada
        else if(figure==T_piece) _world->figure_selected=_t_piece->extractVector(rotation_state);
        else if(figure==S_piece) _world->figure_selected=_s_piece->extractVector(rotation_state);
        else if(figure==Z_piece) _world->figure_selected=_z_piece->extractVector(rotation_state);
        else if(figure==L_piece) _world->figure_selected=_l_piece->extractVector(rotation_state);
        else if(figure==J_piece) _world->figure_selected=_j_piece->extractVector(rotation_state);
    }

    void move_left(World*& _world){
        if(_y<=1) return;

        for(int i=0; i<_world->figure_selected.size(); i++){
            for(int j=0; j<_world->figure_selected[i].size(); j++){
                if(_world->figure_selected[i][j]==2 || _world->figure_selected[i][j]==3 ||
                   _world->figure_selected[i][j]==4 || _world->figure_selected[i][j]==5 ||
                   _world->figure_selected[i][j]==6 || _world->figure_selected[i][j]==7 ||
                   _world->figure_selected[i][j]==8){
                    if(_world->world[_x+i][_y+j-1]==1 || _world->world[_x+i][_y+j-1]==2 ||
                       _world->world[_x+i][_y+j-1]==3 || _world->world[_x+i][_y+j-1]==4 ||
                       _world->world[_x+i][_y+j-1]==5 || _world->world[_x+i][_y+j-1]==6 ||
                       _world->world[_x+i][_y+j-1]==7 || _world->world[_x+i][_y+j-1]==8) return;
                }
            }
        }

        //ESE SUB IF PUEDE IR NORMALMENTE DENTRO DEL PRIMER IF MADRE!!!!!!!!!!!!!!!!

        _y--;
    }

    void move_right(World*& _world){
        int width=_world->figure_selected[0].size();

        if(_y+width>=_world->world[0].size()-1) return;

        for(int i=0; i<_world->figure_selected.size(); i++){
            for(int j=0; j<_world->figure_selected[i].size(); j++){
                if(_world->figure_selected[i][j]==2 || _world->figure_selected[i][j]==3 ||
                   _world->figure_selected[i][j]==4 || _world->figure_selected[i][j]==5 ||
                   _world->figure_selected[i][j]==6 || _world->figure_selected[i][j]==7 ||
                   _world->figure_selected[i][j]==8){
                    if(_world->world[_x+i][_y+j+1]==1 || _world->world[_x+i][_y+j+1]==2 ||
                       _world->world[_x+i][_y+j+1]==3 || _world->world[_x+i][_y+j+1]==4 ||
                       _world->world[_x+i][_y+j+1]==5 || _world->world[_x+i][_y+j+1]==6 ||
                       _world->world[_x+i][_y+j+1]==7 || _world->world[_x+i][_y+j+1]==8) return; 
                }
            }
        }

        //ESE SUB IF PUEDE IR NORMALMENTE DENTRO DEL PRIMER IF MADRE!!!!!!!!!!!!!!!!

        _y++;
    }

    void draw(sf::RenderWindow& window, World*& _world){

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

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
        }
        //ZONA PARA OBTENER NUEVA FIGURA
        _user->selection_figure(
                _i_piece, _o_piece, _t_piece, _s_piece,
                _z_piece, _l_piece, _j_piece, _world
        );

        //ZONA INPUT
        _user->handleInput(_i_piece, _o_piece, _t_piece, _s_piece, 
                           _z_piece, _l_piece, _j_piece, _world); 
        
        //ZONA DE GRAFICAS
        window.clear();

        _world->draw(window); //esto dibuja el mural azul alrededor

        window.display();
    }
}

int main(){
    execute();
    return 0;
}

//g++ -o m main.cpp -lsfml-graphics -lsfml-window -lsfml-system
