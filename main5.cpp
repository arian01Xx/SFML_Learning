#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class EllipseShape: public sf::Shape{
    private:
        sf::Vector2f m_radius;
    public:
        explicit EllipseShape(sf::Vector2f radius={0,0}): m_radius(radius){
            update();
        }

        void setRadius(sf::Vector2f radius){
            m_radius=radius;
            update();
        }

        sf::Vector2f getRadius() const{ return m_radius; }

        std::size_t getPointCount() const override{ return 30; }

        sf::Vector2f getPoint(std::size_t index) const override{
            static constexpr float pi= 3.141592654f;

            float angle=index*2*pi/getPointCount()-pi/2;
            float x=std::cos(angle)*m_radius.x;
            float y=std::sin(angle)*m_radius.y;

            return m_radius+sf::Vector2f(x,y);
        }
};

class MyEntity: public sf::Drawable, public sf::Transformable{
    private:
        sf::VertexArray m_vertices;
        sf::Texture m_texture;

        void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
            state.transform*=getTransform();
            state.texture=&m_texture;

            target.draw(m_vertices, state);
        }
    public:
        //add functions to play with the entity's geometry / colors / texturing ...
};

int main(){

    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML");

    EllipseShape ellipse;
    ellipse.setRadius({80.f, 160.f});

    sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);

    triangle[0].position=sf::Vector2f(20.f, 20.f);
    triangle[1].position=sf::Vector2f(200.f, 20.f);
    triangle[2].position=sf::Vector2f(200.f, 200.f);

    triangle[0].color=sf::Color::Red;
    triangle[1].color=sf::Color::Blue;
    triangle[2].color=sf::Color::Green;

    //---------------------------------------------------------
    // create a triangle strip
    sf::VertexArray triangleStrip(sf::PrimitiveType::TriangleStrip, 4);

    // define it as a rectangle, located at (10, 10) and with size 100x100
    triangleStrip[0].position = sf::Vector2f(10.f, 10.f);
    triangleStrip[1].position = sf::Vector2f(10.f, 110.f);
    triangleStrip[2].position = sf::Vector2f(110.f, 10.f);
    triangleStrip[3].position = sf::Vector2f(110.f, 110.f);

    // define its texture area to be a 25x50 rectangle starting at (0, 0)
    triangleStrip[0].texCoords = sf::Vector2f(0.f, 0.f);
    triangleStrip[1].texCoords = sf::Vector2f(0.f, 50.f);
    triangleStrip[2].texCoords = sf::Vector2f(25.f, 0.f);
    triangleStrip[3].texCoords = sf::Vector2f(25.f, 50.f);

    triangleStrip[0].color=sf::Color::Green;
    triangleStrip[1].color=sf::Color::Blue;
    triangleStrip[2].color=sf::Color::Red;
    triangleStrip[3].color=sf::Color::Yellow;
    //---------------------------------------------------------
    
    MyEntity entity;

    entity.setPosition({10.f, 50.f});
    entity.setRotation(sf::degrees(45));

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is < sf::Event::Closed>()) window.close();
        }

        window.clear();

        window.draw(entity);
        window.draw(ellipse);
        window.draw(triangle);
        window.draw(triangleStrip);

        window.display();
    }

    return 0;
}

//g++ -o main5 main5.cpp -lsfml-graphics -lsfml-window -lsfml-system
