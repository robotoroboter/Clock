#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>    

int main()
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile("res/tick.wav");
    sf::Sound tick;
    tick.setBuffer(buffer);

    int seconds;
    int hours;
    int minutes;
    int currentSeconds = 0, previousSeconds = -1;

    sf::RenderWindow appWindow(sf::VideoMode(508, 508), "Clock");
    sf::Texture clockTexture;
    sf::Texture handTexture;
    clockTexture.loadFromFile("res/clock.png");
    handTexture.loadFromFile("res/hand.png");

    sf::Sprite clock;
    sf::Sprite handH;
    sf::Sprite handM;
    sf::Sprite handS;
    clock.setTexture(clockTexture);
    handH.setTexture(handTexture);
    handM.setTexture(handTexture);
    handS.setTexture(handTexture);

    handH.setPosition(248, 255);
    handM.setPosition(248, 255);
    handS.setPosition(248, 255);
    handH.setScale(0.5, 0.5);
    handS.setScale(0.5, 0.7);

    handM.setOrigin(14,239);
    handH.setOrigin(14, 239);
    handS.setOrigin(14, 239);

    while (appWindow.isOpen())
    {
        sf::Event appEvent;
        while (appWindow.pollEvent(appEvent))
        {
            if (appEvent.type == sf::Event::Closed || (appEvent.type == sf::Event::KeyPressed && appEvent.key.code == sf::Keyboard::Escape))
            {
                printf("app window closed");
                appWindow.close();
            }
        }

        time_t tt;
        time(&tt);
        tm TM = *localtime(&tt);
        seconds = TM.tm_sec;
        minutes = TM.tm_min;
        hours = TM.tm_hour;
        
        
        currentSeconds = seconds;
        if (currentSeconds != previousSeconds && previousSeconds>=0) {
            std::cout << hours << " " << minutes << " " << seconds << std::endl;
            std::string newTitle = "Clock: ";
            if (hours<10)
            newTitle += "0";
            newTitle += std::to_string(hours) + ":";
            if (minutes < 10)
                newTitle += "0";
            newTitle += std::to_string(minutes) + ":";
            if (seconds < 10)
                newTitle += "0";
            newTitle += std::to_string(seconds);
            appWindow.setTitle(newTitle);
            tick.play();
        }
        previousSeconds = currentSeconds;

        float secondPercent = (float)seconds / 60;
        float minutePercent = ((float)minutes+secondPercent) / 60;
        float hourPercent = ((float)hours + minutePercent) / 12;

        handH.setRotation(360 * hourPercent);
        handM.setRotation(360 * minutePercent);
        handS.setRotation(360 * secondPercent);

        appWindow.clear();
        appWindow.draw(clock);
        appWindow.draw(handM);
        appWindow.draw(handH);
        appWindow.draw(handS);
        appWindow.display();
    }

    return 0;
}