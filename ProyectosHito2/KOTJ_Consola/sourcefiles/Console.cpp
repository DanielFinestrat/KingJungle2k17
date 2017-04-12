/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Console.cpp
 * Author: jesus
 * 
 * Created on 5 de abril de 2017, 16:02
 */

#include "../headerfiles/Console.h"
#include "../headerfiles/Partida.h"

using namespace std;

Partida * partida = Partida::getInstance();

Console::Console() {

    consoleInScreen = false;

    console = sf::RectangleShape(sf::Vector2f(1024, 250));
    console.setPosition(0, screenHeight - console.getSize().y);
    console.setFillColor(sf::Color(0, 0, 0, 200));

    consoleString = ">";
    commandString = "";
    nlines = 0;

    font = new sf::Font();
    if (!font->loadFromFile("resources/fonts/bits.ttf")) {
        cerr << "Error cargando la fuente";
        exit(0);
    }
    //consoleText = new Text();
    consoleText = new sf::Text(consoleString, *font, 20);
    consoleText->setColor(sf::Color::White);
    consoleText->setPosition(sf::Vector2f(0, screenHeight - console.getSize().y + 15));


    functionMap = new std::map < std::string, std::function<void (int) >>();
    loadFunctions();
}

Console::Console(const Console& orig) {
}

Console::~Console() {
}

void Console::toggleConsole() {
    //usingKeyboard = consoleInScreen;
    consoleInScreen = !consoleInScreen;

    if (consoleInScreen) {
        cout << "se activa la consola" << endl;
    } else {
        cout << "se desactiva la consola" << endl;
    }
}

void Console::send() {
    if (consoleInScreen) {
        //se controla el comando
        if (commandString != "") {
            char *line = new char[commandString.length() + 1]; // or
            char * token;
            string nombrefunction;
            int param1 = -1;

            strcpy(line, commandString.c_str());

            token = strtok(line, " ");
            nombrefunction = string(token);
            //pasa todo a minusculas
            transform(nombrefunction.begin(), nombrefunction.end(), nombrefunction.begin(), ::tolower);

            token = strtok(NULL, " ");
            if (token != NULL)
                param1 = atoi(token);

            //token = strtok(NULL, " ");
            token = strtok(NULL, "\0");

            //cout << nombrefunction << endl;
            if (functionMap->count(nombrefunction) > 0) {
                function<void (int) > fn = functionMap->at(nombrefunction);
                fn(param1);
            }

            delete token;
            delete[] line;
        }
        
        //se controlan los saltos de linea y to eso
        if (nlines == 10) {
            size_t pos = consoleString.find('\n');
            consoleString = consoleString.substr(pos + 1);
            nlines--;

            pos = consoleString.find('\n');
            consoleString = consoleString.substr(pos + 1);
            nlines--;
        }
        commandString = "";
        consoleString += "\n>";
        nlines++;
        consoleText->setString(consoleString);
    }
}

void Console::write(sf::Event even) {
    // Caracteres ascii solo menos el tab
    if (consoleInScreen && even.text.unicode < 128 &&
            (even.text.unicode != 13 && even.text.unicode != 9 && even.text.unicode != 8)) {
        //cout << even.text.unicode << endl;

        //se inserta en los strings que van a llevar el valor
        consoleString += static_cast<char> (even.text.unicode);
        commandString += static_cast<char> (even.text.unicode);

        //se le asigna el texto que se va a ver
        consoleText->setString(consoleString);
    }
}

void Console::deleteChar() {
    if (consoleInScreen && commandString != "") {
        commandString.resize(commandString.length() - 1);
        consoleString.resize(consoleString.length() - 1);

        consoleText->setString(consoleString);
    }
}

void suicideAll(int n) {
    //cout << "pum, tos muertos" << endl;

    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        partida->players2Delete.push_back(partida->worldPlayer.at(i));
    }
}

void Console::loadFunctions() {
    //se declara la funcion de suicidio
    function<void (int) > fn = suicideAll;
    //se inserta dentro del hash map
    functionMap->insert(std::pair<string, function<void (int) >>("suicide", fn));

    /*
    fn = suicideAll;
    //se inserta dentro del hash map
    functionMap->insert(std::pair<string,function<void (int)>>("notime", fn));
     */
}

void Console::draw(sf::RenderWindow *window) {
    if (consoleInScreen) {
        window->draw(console);

        string s1 = consoleText->getString();
        //cout << "valor: " << s1 << endl;
        window->draw(*consoleText);
    }
}

