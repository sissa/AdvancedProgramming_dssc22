#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(700, 700), "Hello, World!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);
    //this is how most games are run, it's an infinite "while" loop
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){   
          //without this, the window won't react to close button
            if (event.type == sf::Event::Closed){
                window.close();
            }   
            //an example of keyboard interaction
            if (event.type == sf::Event::KeyPressed){
              switch (event.key.code){ 
              case sf::Keyboard::Q:
                window.close();
              break;
              }//switch
            }//if keypressed 
        }//while poll event
        
        window.clear();
        window.draw(shape);
        window.display();
   
    }//main game loop
    return 0;
} 
