
#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Resources {
    
    public:
       
        static Resources* getInstance();
        bool initialise();
        void cleanUp();
        bool loadAll();
        
        bool loadFont(string filename);
        Font &getFont(string filename);
        
        bool loadTexture(string filename);
        Texture &getTexture(string filename);
        
        bool loadImage(string filename);
        Image &getImage(string filename);

        const string myFont;
        const string triangle;
        const string sprites;
        const string armas;
        const string tiles;
        const string fondoJungla;
        

    private:
        Resources();
        map<string, Font*> fonts;
        map<string, Texture*> textures;
        map<string, Image*> images;

};

#endif
