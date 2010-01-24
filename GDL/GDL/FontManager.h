#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

/**
 * FontManager load and manage fonts.
 */
class GD_API FontManager
{
public:
    const sf::Font * GetFont(string fontName);

    static FontManager *getInstance()
    {
        if ( NULL == _singleton )
        {
            _singleton = new FontManager;
        }

        return ( static_cast<FontManager*>( _singleton ) );
    }

    static void kill()
    {
        if ( NULL != _singleton )
        {
            delete _singleton;
            _singleton = NULL;
        }
    }

protected:
private:

    map < std::string, sf::Font* >   fonts;

    FontManager();
    virtual ~FontManager();

    static FontManager *_singleton;
};

#endif // FONTMANAGER_H
