#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    std::string title = "Main Window";
    unsigned int window_width = 800;
    unsigned int window_height = 600;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), title);

    // Create the texture
    sf::Texture texture;
    if (!texture.loadFromFile("res/cute_image.jpg")) {
        return EXIT_FAILURE;
    }

    // Create the sprite.
    sf::Sprite sprite(texture);
    
    // Create the fonts
    sf::Font font;
    if (!font.loadFromFile("res/arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text text("Hello from SFML", font, 50);

    // Load the music to play
    sf::Music music;
    if (!music.openFromFile("res/nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music.
    music.play();

    // start the game loop
    while(window.isOpen()) {
        // handle the events in game loop.
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // clear the window
        window.clear();

        // draw the sprite
        window.draw(sprite);

        // draw the text
        window.draw(text);

        // display the window 
        window.display();
    }

    return EXIT_SUCCESS;
}
