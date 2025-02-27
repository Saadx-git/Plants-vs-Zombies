#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pages");
//window.setFramerateLimit(60);

class Page {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(sf::Event event) = 0;
    virtual bool nextPage() const = 0;
    virtual ~Page() {}
};

class Page1 : public Page {
public:
    Page1() {
        button.setSize(sf::Vector2f(200, 50));
        button.setPosition(100, 100);
        button.setFillColor(sf::Color::Green);
        buttonText.setFont("Atop-R99O3.ttf");
        buttonText.setString("Page 2");
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(120, 115);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(button);
        window.draw(buttonText);
    }

    void handleEvent(sf::Event event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Convert to window coordinates
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Button 1 pressed\n";
                    nextPageFlag = true;
                }
            }
        }
    }

    bool nextPage() const override {
        return nextPageFlag;
    }

private:
    sf::RectangleShape button;
    sf::Text buttonText;
    bool nextPageFlag = false;
};

class Page2 : public Page {
public:
    Page2() {
        button.setSize(sf::Vector2f(200, 50));
        button.setPosition(100, 100);
        button.setFillColor(sf::Color::Red);

        buttonText.setString("Page 1");
        buttonText.setFont("Atop-R99O3.ttf");
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(120, 115);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(button);
        window.draw(buttonText);
    }

    void handleEvent(sf::Event event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Convert to window coordinates
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Button 2 pressed\n";
                    nextPageFlag = true;
                }
            }
        }
    }

    bool nextPage() const override {
        return nextPageFlag;
    }

private:
    sf::RectangleShape button;
    sf::Text buttonText;
    bool nextPageFlag = false;
};

int main() {
    

    Page1 page1;
    Page2 page2;

    Page* currentPage = &page1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            currentPage->handleEvent(event);
        }

        window.clear();

        if (currentPage->nextPage()) {
            if (currentPage == &page1) {
                currentPage = &page2;
            }
            else {
                currentPage = &page1;
            }
        }

        currentPage->draw(window);

        window.display();
    }

    return 0;
}
