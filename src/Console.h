
/* 
 * File:   Console.h
 * Author: jesus
 *
 * Created on 5 de abril de 2017, 16:02
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <functional>
#include <vector>
#include "motorgrafico/headerfiles/Texto.h"
#include "motorgrafico/headerfiles/VisibleBody.h"
#include "motorgrafico/headerfiles/resources.h"

#define screenWidth 1024
#define screenHeight 600

class Console {
public:

    Console();

    /**
     * Activa y desactiva la consola 
     * @param toggle: si toggle es true muestra la consola, si es false la oculta
     */
    void toggleConsole();

    /**
     * Manda el comando para ejecutarlo
     */
    void send();

    /**
     * Escribe en la consola
     * @param evento con el texto escrito
     */
    void write(std::string s);

    /**
     * Funcion que se llama al pulsar la tecla de borrar
     */
    void deleteChar();


    void loadFunctions();

    /**
     * Dibuja la consola por pantalla
     * @param window: Puntero a window que dibuja a la consola
     */
    void draw();
    
    void getLastCommand();
    
    bool getConsoleInScreen();

    virtual ~Console();
private:

    bool consoleInScreen; /**Comprueba si esta la consola en pantalla o no*/

    VisibleBody console; /**Es la forma de la consola*/
    Texto *consoleText; /**Texto que se muestra en la consola*/
    std::string consoleString; /**String que se va concatenando continuamente y se asigna al texto drawable*/
    std::string commandString; /**String que contiene el valor del comando actual*/
    std::vector<std::string> commandStringVector; /**Vector que contiene los comandos de consola*/
    int lastCommand;
    //std::string backup;
    
    int nlines;
    std::map<std::string, std::function<void (int) >> *functionMap; /**HashMap de las funciones de la consola*/

    //sf::Font *font;
};

#endif /* CONSOLE_H */