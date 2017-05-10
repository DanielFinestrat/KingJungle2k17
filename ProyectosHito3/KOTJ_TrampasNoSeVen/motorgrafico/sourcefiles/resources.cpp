#include "../headerfiles/resources.h"
#include <iostream>

using namespace sf;
using namespace std;

static Resources* instance; 

Resources::Resources(): myFont("./resources/fonts/bits.ttf"),
                        menuFont("./resources/fonts/newrotic.ttf"),
                        sprites("./resources/sprites/sprites.png"),
                        armas("./resources/sprites/weapon_spritesheet.png"),
                        tiles("./resources/sprites/tilesheet.png"),
                        podio("./resources/sprites/podio.png"),
                        spikes("./resources/sprites/trapSpike.png"),
                        fondoCueva("./resources/fondos/fondoCueva.png"),
                        tnt("./resources/sprites/tnt-0.png"),
                        fondoHielo("./resources/fondos/fondoHielo.jpg"),
                        fondoHielo1("./resources/fondos/fondoHielo1.jpg"),
                        fondoJungle("./resources/fondos/fondoJungle.png"),
                        fondoMandala("./resources/fondos/fondoMandala.jpg"),
                        fondoMar("./resources/fondos/fondoMar.jpg"),
                        fondoSeleccion("./resources/fondos/fondoSeleccion.png"),
                        fondoMenu("./resources/fondos/fondomenu.png"),
                        puntero("./resources/sprites/puntero.png"),
                        transparente("./resources/sprites/transparente.png")
                        { initialise(); }



Resources* Resources::getInstance() {
    if (instance == NULL) {instance = new Resources();}
    return instance;
}

bool Resources::initialise() {
    if (loadAll()) {return true; }
    return false;
}

void Resources::cleanUp() {
    //Limpiar las fuentes
    map<string, Font*>::iterator font_it;
    for (font_it = fonts.begin(); font_it != fonts.end(); font_it++) {
        delete font_it->second;
        font_it->second = NULL;
    }
    fonts.clear();

    //Limpiar las texturas
    map<string, Texture*>::iterator texture_it;
    for (texture_it = textures.begin(); texture_it != textures.end(); texture_it++) {
        delete texture_it->second;
        texture_it->second = NULL;
    }
    textures.clear();
    
    //Limpiar las imagenes
    map<string, Image*>::iterator image_it;
    for (image_it = images.begin(); image_it != images.end(); image_it++) {
        delete image_it->second;
        image_it->second = NULL;
    }
    images.clear();
}

bool Resources::loadAll() {
    if (!loadFont(myFont)) return false;
    if (!loadFont(menuFont)) return false;
    if (!loadTexture(sprites)) return false;
    if (!loadTexture(armas)) return false;
    if (!loadTexture(tiles)) return false;
    if (!loadTexture(podio)) return false;
    if (!loadTexture(tnt)) return false;
    if (!loadTexture(fondoJungle)) return false;
    if (!loadTexture(fondoHielo)) return false;
    if (!loadTexture(fondoHielo1)) return false;
    if (!loadTexture(fondoSeleccion)) return false;
    if (!loadTexture(fondoCueva)) return false;
    if (!loadTexture(fondoMandala)) return false;
    if (!loadTexture(fondoMar)) return false;
    if (!loadTexture(fondoMenu)) return false;
    if (!loadTexture(puntero)) return false;
    if (!loadTexture(spikes))return false;
    if(!loadTexture(transparente)) return false;
  return true;
}

bool Resources::loadFont(string filename) {
    if (fonts.find(filename) != fonts.end()) return false;

    Font *font = new Font();
    err().rdbuf(NULL);
    
    if (!font->loadFromFile(filename)) {
        cout<<"Error cargando fuente"<<endl;
        delete font; font = NULL; return false;
    }

    const_cast<sf::Texture&>(font->getTexture(8)).setSmooth(false);
    const_cast<sf::Texture&>(font->getTexture(12)).setSmooth(false);
    const_cast<sf::Texture&>(font->getTexture(16)).setSmooth(false);
    const_cast<sf::Texture&>(font->getTexture(24)).setSmooth(false);

    fonts.insert(pair<string, Font*>(filename, font));

    return true;
}

Font &Resources::getFont(string filename) {
    return *(fonts.find(filename)->second);
}

bool Resources::loadTexture(string filename){
    if (textures.find(filename) != textures.end()) return false;

    loadImage(filename); //Cargamos la imagen si nuestra textura no existe
    
    Texture *texture = new Texture();
    err().rdbuf(NULL);

    texture->loadFromFile(filename);
    
    //Le asignamos la imagen guardada a la textura
    if (!texture->loadFromImage(getImage(filename))) {
        cout<<"Error cargando textura"<<endl;
        delete texture; texture = NULL; return false;
    }

    texture->setSmooth(false);
    textures.insert(pair<string, Texture*>(filename, texture));
    
    return true;
}

Texture &Resources::getTexture(string filename) {
    return *(textures.find(filename)->second);
}

bool Resources::loadImage(string filename){
    if (images.find(filename) != images.end()) return false;

    Image *image = new Image();
    err().rdbuf(NULL);

    if (!image->loadFromFile(filename)) {
        cout<<"Error al cargar la imagen"<<endl;
        delete image; image = NULL; return false;
    }

    images.insert(pair<string, Image*>(filename, image));

    return true;
}

Image &Resources::getImage(string filename) {
    return *(images.find(filename)->second);
}