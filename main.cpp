#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

int main(){

    //para crear una ventana
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    
    //para crear un circulo y pintarlo
    sf::CircleShape shape(50.f); 
    /*PARA AGREGAR TEXTURA CON IMAGEN
    shape.setTexture(&texture);
    shape.setTextureRect(sf::IntRect({10,10},{100,100}));*/
    shape.setFillColor(sf::Color::Green); //o coloreas con (sf::Color::Green);     
    shape.setOutlineThickness(10.f);
    shape.setPosition({100.f, 20.f});
    shape.setOutlineColor(sf::Color::Blue);

    //RECTANGULO
    sf::RectangleShape rectangle({120.f, 50.f});
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition({100.f, 120.f});
    rectangle.setSize({100.f, 100.f});

    //CIRCULO
    sf::CircleShape circle(200.f);
    circle.setPosition({100.f, 240.f});
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(40.f);
    circle.setPointCount(100);

    //CREAR FIGURAS CON NUMERO DE LADO
    sf::CircleShape triangle(80.f, 3);
    triangle.setPosition({100.f, 300.f});
    triangle.setFillColor(sf::Color::Green);
    //triangle.setRadius(80.f);
    //triangle.setPointCount(100);
    
    sf::CircleShape square(80.f, 4);
    square.setPosition({100.f, 400.f});
    square.setFillColor(sf::Color::Red);
    //square.setRadius(80.f);
    //square.setPointCount(100);

    sf::CircleShape octagon(80.f, 8);
    octagon.setPosition({50.f, 500.f});
    octagon.setFillColor(sf::Color::Blue);
    //octagon.setRadius(80.f);
    //octagon.setPointCount(100);
    
    sf::ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0,{0.f, 0.f});
    convex.setPoint(1,{150.f, 10.f,});
    convex.setPoint(2,{120.f, 90.f});
    convex.setPoint(3,{30.f, 100.f});
    convex.setPoint(4,{0.f, 50.f});
    convex.setFillColor(sf::Color::White);

    sf::RectangleShape line({150.f, 5.f});
    line.setFillColor(sf::Color::Red);
    line.setPosition({40.f, 10.f});
    line.rotate(sf::degrees(45));

    std::array _line={
        sf::Vertex{sf::Vector2f(30.f, 30.f)},
        sf::Vertex{sf::Vector2f(150.f, 150.f)}
    };

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) window.close();
        }

        //mueve a la izquierda
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) shape.move({-0.1f, 0.f});
        //mueve a la derecha
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) shape.move({0.1f, 0.f});
        //mueve hacia arriba
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) shape.move({0.f, -1.f});
        //mueve hacia abajo 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) shape.move({0.f, 1.f});

        //mueve a la izquierda
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) rectangle.move({-0.1f, 0.f});
        //mueve a la derecha
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) rectangle.move({0.1f, 0.f});
        //mueve hacia arriba
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) rectangle.move({0.f, -1.f});
        //mueve hacia abajo 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) rectangle.move({0.f, 1.f});

        window.clear(); //fondo negro

        window.draw(shape); //para que dibuje las figuras creadas
        window.draw(rectangle);
        window.draw(circle);
        window.draw(triangle);
        window.draw(square);
        window.draw(octagon);
        window.draw(convex);
        window.draw(line);
        window.draw(_line.data(), _line.size(), sf::PrimitiveType::Lines);

        window.display(); //finalizar el frame actual
    }
    return 0;
}

//g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

/*NIVEL 1
 for (int y = 0; y < map.size(); y++)
{
    for (int x = 0; x < map[y].size(); x++)
    {
        sprite.setPosition(x * tileSize, y * tileSize);

        if (map[y][x] == 0)
            sprite.setTexture(grass);
        else if (map[y][x] == 1)
            sprite.setTexture(wall);
        else if (map[y][x] == 2)
            sprite.setTexture(box);

        window.draw(sprite);
    }
}
 */

/*NIVEL 2
 std::vector<int> map(width * height);
map[y * width + x]
  */

/*NIVEL 3
 sf::VertexArray tiles(sf::Quads, width * height * 4);

 */

