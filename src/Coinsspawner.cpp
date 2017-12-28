
/* 
 * File:   Coinsspawner.cpp
 * Author: amygwyllion
 * 
 * Created on 1 de mayo de 2017, 16:44
 */

#include "headerfiles/Coinsspawner.h"
#include "headerfiles/Partida.h"
#include "motorgrafico/headerfiles/Motorgrafico.h"

Coinsspawner::Coinsspawner() {   
    leerCoins();
    leerSpawnerPosition();
    cargarCoins();
    
    currentTime =  respawnTime;
    
    clock = new InnerClock();
    clock->restartClock();
}

Coinsspawner::Coinsspawner(const Coinsspawner& orig) {
}

void Coinsspawner::leerSpawnerPosition(){
    deleteCoins();
    spawnCoins = Partida::getInstance()->mapa->getSpawnCoins();
}

void Coinsspawner::leerCoins(){
    if(!texture.loadFromFile(Resources::getInstance()->coin)){
        cout<<"Error al cargar textura"<<endl;
    }
    
    const char *cstr = coinsFile.c_str();
    TiXmlDocument doc(cstr);
    doc.LoadFile();
    
    TiXmlElement* coins = doc.FirstChildElement("coins");
    TiXmlElement* coin = coins->FirstChildElement("coin");
    
    int i = 0;
    
    while(coin){
        datosCoin nuevosDatos;
        coinAnimation = new Animation();
        coinAnimation->setSpriteSheet(texture);
        nuevosDatos.indice = i;
        
        coin->QueryIntAttribute("valor", &nuevosDatos.valor);
        coin->QueryIntAttribute("rareza", &nuevosDatos.rareza);
        
        TiXmlElement* sprite = coin->FirstChildElement("sprite");
        float x, y, w, h;
        
        while(sprite){
            
            sprite->QueryFloatAttribute("x",&x);
            sprite->QueryFloatAttribute("y",&y);
            sprite->QueryFloatAttribute("w",&w);
            sprite->QueryFloatAttribute("h",&h);
            
            //cout<<"para i = "<< i <<" "<< x <<" "<< y <<" "<< w <<" "<< h <<endl;
            coinAnimation->addFrame(IntRect(x,y,w,h));
            sprite = sprite->NextSiblingElement("sprite");
        }
        nuevosDatos.animation = coinAnimation;
        datosCoins.push_back(nuevosDatos);
        coin = coin->NextSiblingElement("coin");
        i++;
    }
}

void Coinsspawner::Update(){
    currentTime = currentTime - clock->getDeltaTimeAsSeconds();
    clock->restartClock();
    
    if (currentTime <= 0) {
        currentTime = respawnTime;
        //checkIfUsed();
        deleteCoins();
        cargarCoins();
    }

}

void Coinsspawner::cargarCoins(){
    Partida::getInstance()->worldCoins.clear();
    srand(time(NULL));
    for (int i = 0; i < spawnCoins.size(); i++) {

       datosCoin datos;
       int grupo = -1;
       int indice = rand() % 20; //100% (0 a 19)

       if (indice <= 8) grupo = 0; //40%
       else if (indice <= 15) grupo = 1; //35%
       else if (indice <= 19) grupo = 2; //25%

       do {
           indice = rand() % datosCoins.size();
           datos = datosCoins.at(indice);
       } while (grupo != datos.rareza);
       
       vector<int> spawn = spawnCoins.at(i);
       float x = spawn.at(0);
       float y = spawn.at(1);

       Coin* coin = new Coin(x,y,datos.valor, datos.animation);
       
       coins.push_back(coin);
       Partida::getInstance()->worldCoins.push_back(coin);
   }
    //cout<<"salgo de cargarCoins con el vector worldCoins de tamaño: "<<Partida::getInstance()->worldCoins.size()<<endl;
}

void Coinsspawner::checkIfUsed(){
    
    for (int i = 0; i < coins.size(); i++) {
        if (coins.at(i) != NULL) {
            Coin *coin = coins.at(i);
            if (coin->getInPossession()) {
                Partida::getInstance()->coins2Delete.push_back(coins.at(i));
                Partida::getInstance()->worldCoins.at(i) = NULL;
                coins.at(i) == NULL;
            }
        }
    }
}

void Coinsspawner::deleteCoins(){
    for (int i = 0; i < Partida::getInstance()->worldCoins.size(); i++) {
        Coin* coin = Partida::getInstance()->worldCoins.at(i);
        if (coin != NULL) {
            Partida::getInstance()->coins2Delete.push_back(Partida::getInstance()->worldCoins.at(i));
            Partida::getInstance()->worldCoins.at(i) = NULL;
        }
    }
    Partida::getInstance()->worldCoins.clear();
}

Coinsspawner::~Coinsspawner() {
}