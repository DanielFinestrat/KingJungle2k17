
/* 
 * File:   Console.cpp
 * Author: jesus
 * 
 * Created on 5 de abril de 2017, 16:02
 */

#include "headerfiles/Console.h"
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"
#include <iostream>

using namespace std;

Console::Console() {

    consoleInScreen = false;

    console = VisibleBody(0, screenHeight - 250, 1024, 250, "", false);
    console.setColor(0, 0, 0, 200);

    consoleString = ">";
    commandString = "";
    nlines = 0;

    consoleText = new Texto(consoleString, 20, Resources::getInstance()->myFont, 255, 255, 255);
    consoleText->setPos(0, screenHeight - console.getHeight() + 15);

    commandStringVector = vector<std::string>();
    lastCommand = -1;

    functionMap = new std::map < std::string, std::function<void (int) >>();
    loadFunctions();
}

Console::~Console() {
}

void Console::toggleConsole() {
    consoleInScreen = !consoleInScreen;
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

            if (param1 == -1) commandStringVector.push_back(nombrefunction);
            else {
                ostringstream stm;
                stm << param1;
                string parametro1 = stm.str();
                commandStringVector.push_back(nombrefunction + " " + parametro1);
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
        lastCommand = -1;
        commandString = "";
        consoleString += "\n>";
        nlines++;
        consoleText->setTexto(consoleString);
    }
}

void Console::write(string s) {
    //se inserta en los strings que van a llevar el valor
    consoleString += s;
    commandString += s;

    //se le asigna el texto que se va a ver
    consoleText->setTexto(consoleString);

}

void Console::deleteChar() {
    if (consoleInScreen && commandString != "") {
        commandString.resize(commandString.length() - 1);
        consoleString.resize(consoleString.length() - 1);

        consoleText->setTexto(consoleString);
    }
}

void Console::draw() {
    if (consoleInScreen) {

        Motorgrafico::getInstance()->draw(console.getShape());

        string s1 = consoleText->getTexto();
        Motorgrafico::getInstance()->draw(consoleText->getDrawable());

        //cout << "valor: " << s1 << endl;
    }
}

void suicideAll(int n) {
    //cout << "pum, tos muertos" << endl;
    Partida * partida = Partida::getInstance();
    for (int i = 0; i < partida->worldPlayer.size(); i++) {
        partida->players2Delete.push_back(partida->worldPlayer.at(i));
    }
}

void reviveAll(int n) {
    //cout << "pum, tos muertos" << endl;
    Partida * partida = Partida::getInstance();
    partida->respawn();
}

void infiniteTime(int n) {
    Motorgrafico::getInstance()->getTemporizador()->stop(true);
    //cout << "adeu time" << endl;
}

void selectWeapon(int n) {
    Partida * partida = Partida::getInstance();
    partida->factoriaArmas->cargarArmas(n);

}

void selectMap(int n) {
    Partida * partida = Partida::getInstance();
    vector<string> maps = partida->mapa->mapas;

    if (n >= 0 && n < maps.size()) {
        if (maps.at(n).compare(partida->mapa->mapaPodio) == 0){
            partida->loadFinalMap();
            partida->indexMap = n;
        }
        else
            partida->loadMap(maps.at(n));
    }
}

void exitGame(int n) {
    Motorgrafico::getInstance()->getRenderWindow()->close();
}

void give5Points(int n) {
    Partida * partida = Partida::getInstance();
    if (n >= 0 && n < partida->worldPlayer.size()) {
        for (int i = 0; i < 5; i++) {
            partida->worldPlayer.at(n)->give1Point();
        }
    }
}

void Console::loadFunctions() {
    //se declara la funcion de suicidio
    function<void (int) > fn;
    fn = suicideAll;
    //se inserta dentro del hash map
    functionMap->insert(std::pair<string, function<void (int) >>("suicide", fn));

    fn = reviveAll;
    functionMap->insert(std::pair<string, function<void (int) >>("revive", fn));

    fn = infiniteTime;
    functionMap->insert(std::pair<string, function<void (int) >>("notime", fn));

    fn = selectWeapon;
    functionMap->insert(std::pair<string, function<void (int) >>("selectweapon", fn));

    fn = selectMap;
    functionMap->insert(std::pair<string, function<void (int) >>("selectmap", fn));

    fn = exitGame;
    functionMap->insert(std::pair<string, function<void (int) >>("exit", fn));
    
    fn = give5Points;
    functionMap->insert(std::pair<string, function<void (int) >>("give5", fn));
}

void Console::getLastCommand() {
    if (consoleInScreen) {
        int vecsize = commandStringVector.size();
        if (vecsize > 0) {
            if (lastCommand == -1) {
                lastCommand = vecsize - 1;

                commandString = commandStringVector.at(lastCommand);
                consoleString += commandString;
                consoleText->setTexto(consoleString);
            } else {
                if (commandString.compare(commandStringVector.at(lastCommand)) == 0) {
                    if (lastCommand > 0 && lastCommand < vecsize) {
                        lastCommand--;
                        consoleString.resize(consoleString.length() - commandString.length());

                        commandString = commandStringVector.at(lastCommand);
                        consoleString += commandString;
                        consoleText->setTexto(consoleString);
                    }
                }
            }
        }
    }
}

bool Console::getConsoleInScreen() {
    return consoleInScreen;
}