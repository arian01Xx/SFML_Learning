#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML");

    sf::Vertex vertex;
    vertex.position=sf::Vector2f(10.f, 50.f);
    vertex.color=sf::Color::Green;
    vertex.texCoords=sf::Vector2f(100.f, 100.f);
    //sf::Vertex vertex{{10.f, 50.f}, sf::Color::Red, {100.f, 100.f}};
   
    sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);

    triangle[0].position=sf::Vector2f(10.f, 10.f);
    triangle[1].position=sf::Vector2f(100.f, 10.f);
    triangle[2].position=sf::Vector2f(100.f, 100.f);

    triangle[0].color=sf::Color::Red; //DEFINIMOS LOS COLORES POR CADA ESQUINA
    triangle[1].color=sf::Color::Blue;
    triangle[2].color=sf::Color::Green;

    //--------------------------------------------------------------
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({100.f, 20.f});

    //1. LOAD A FONT
    sf::Font font; 
    if(!font.openFromFile("arial.ttf")){
        std::cerr<<"Error loading font file"<<std::endl;
        return -;
    }

    //2. CREATE A TEXT OBJECT AND SET ITS PROPERTIES
    sf::Text text(font);
    text.setString("ARIAN JOSEPH");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition({100.f, 100.f});

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is < sf::Event::Closed>()) window.close();
        }

        window.clear();

        window.draw(shape);
        window.draw(text);
        window.draw(triangle);

        window.display();

    }

    return 0;
}

//tambien tiene para sf::Text
/*
 std::vector<sf::Vertex> vertices;
vertices.push_back(sf::Vertex{...});
...

window.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Triangles);

----------------------------------------------------------------------------
std::array vertices = {
    sf::Vertex{...},
    sf::Vertex{...}
};

window.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Lines);
 * */


