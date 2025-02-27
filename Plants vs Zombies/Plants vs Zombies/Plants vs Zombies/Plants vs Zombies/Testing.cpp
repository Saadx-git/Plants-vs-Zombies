//#include <iostream>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include <ctime>
//using namespace sf;
//using namespace std;
//
//class Button
//{
//private:
//    sf::RectangleShape button;
//    sf::Text txt;
//    int x_cord;
//    int y_cord;
//
//public:
//    Button() {
//
//    }
//
//    Button(string t, sf::Vector2f location, sf::Vector2f size, sf::Color clr, sf::Color bgcolor, int character_size) {
//        // Button
//        button.setPosition(location.x, location.y);
//        button.setFillColor(bgcolor);
//        button.setSize(size);
//
//        // Text
//        txt.setFillColor(clr);
//        txt.setString(t);
//        txt.setCharacterSize(character_size);
//        txt.setPosition(location.x + size.x / 2 - txt.getLocalBounds().width / 2, location.y + size.y / 2 - txt.getLocalBounds().height / 2);
//        txt.setStyle(sf::Text::Bold);
//
//        sf::Font font;
//        if (!font.loadFromFile("Burbank Big Condensed Font.otf")) {
//            std::cerr << "Failed to load font" << std::endl;
//            return;
//        }
//        txt.setFont(font);
//
//        // Location
//        x_cord = location.x;
//        y_cord = location.y;
//    }
//
//    // Getters
//    sf::RectangleShape getButton() const {
//        return button;
//    }
//
//    sf::Text getText() const {
//        return txt;
//    }
//
//    float getX() const {
//        return x_cord;
//    }
//
//    float getY() const {
//        return y_cord;
//    }
//
//    // Setters
//    void setPosition(sf::Vector2f new_pos) {
//        button.setPosition(new_pos.x, new_pos.y);
//        txt.setPosition(new_pos.x + button.getSize().x / 2 - txt.getLocalBounds().width / 2, new_pos.y + button.getSize().y / 2 - txt.getLocalBounds().height / 2);
//    }
//
//    void setText(const std::string& newText) {
//        txt.setString(newText);
//    }
//
//    void setLocation(Vector2f newLocation) {
//        button.setPosition(newLocation);
//        txt.setPosition(newLocation.x + button.getSize().x / 2 - txt.getLocalBounds().width / 2, newLocation.y + button.getSize().y / 2 - txt.getLocalBounds().height / 2);
//    }
//
//    // Draw
//    void drawTo(sf::RenderWindow& win) {
//        win.draw(button);
//        win.draw(txt);
//    }
//
//    // Mouse Reaction
//    bool onButton(sf::RenderWindow& win) {
//        int mouse_x = sf::Mouse::getPosition(win).x;
//        int mouse_y = sf::Mouse::getPosition(win).y;
//
//        int btn_x = getX() + button.getLocalBounds().width;
//        int btn_y = getY() + button.getLocalBounds().height;
//
//        if (mouse_x < btn_x && mouse_x > getX() && mouse_y < btn_y && mouse_y > getY()) {
//            return true;
//        }
//        else {
//            return false;
//        }
//    }
//};
//
//int main()
//{
//    RenderWindow window(VideoMode(800, 600), "Test Window");
//
//    Button playBtn("Play", { 400, 300 }, { 200, 100 }, Color::Yellow, Color::Green, 24);
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        playBtn.drawTo(window);
//        window.display();
//    }
//
//    return 0;
//}
