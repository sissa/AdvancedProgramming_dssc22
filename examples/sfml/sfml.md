### SFML library

C++ isn't used only for console-only scientific appliations, but all for modern games. Of course, we are not going to write a real "modern" game, but you can easily create something like snake, tetrix, lines or "game of life" (which I provide you as an example).

To install, in your distribution repository, look for something like `libsfml-dev` (ubuntu) or `sfml2-devel` (suse).

Here is the [web-page](https://www.sfml-dev.org/) where you can download it from if it's not in your distribution repository and read tutorials.

If you are on WSL, unfortunately, there is a good chance that nothing graphical will work, but then if you can compile anything directly on windows, you can install the windows version directly.

Let's look at a "hello, world" example:

```
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
```

Compile it with 

```
g++ -o hello_sfml.x -lsfml-graphics -lsfml-window -lsfml-system basic.cpp 
```

If this compiles, then everything has been installed correctly. If you installed manually (from github instead of a repository), you might need to specify the include folder when you compile and update your `LIBRARY_PATH` and `LD_LIBRARY_PATH` environmental libraries.


There is a more advanced example, where you can see how to draw more complicated staff and move things - game of life.

To compile the "game of life" example, do

```
g++ -lsfml-window -lsfml-graphics -lsfml-system -o life.x life.cpp
```

Then, running `./life.x` should open a window with a field where you can draw anything by clicking on the squares. Once you are done drawing, press the space key to start the "game". You can pose it any time with the `p` or space keys. You can save the file with the `s` key. The file will be named "renameMe.txt". When you start the program, you can give it the save file so that you wouldn't need to draw again. You can move the screen with the arrow keys. To quit, press `q`.

### Exercises (for people who completely have nothing else to do):

**Exercise1:** Modify the game of life to have "periodic boundary conditions" (so that the things would just move over the edges rather then disappear).

**Exercise2:** Try to write a snake game.







