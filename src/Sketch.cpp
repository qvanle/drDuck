#include <Sketch.hpp>
/**
 * @brief sketch constructor 
 * 
 * set all pointer to be nullptr
 * default background color is black
 * default font color is white and there will be no text 
 * default text align is center
 * default border size is 0
 * default coordinate will be top left corner and size is 0
*/
Sketch::Sketch()
{
    font = nullptr;
    text = "";
    color = SDL_Color({0, 0, 0, 255});
    fontColor = SDL_Color({255, 255, 255, 255});

    tes[0] = nullptr;
    tes[1] = nullptr;
    coor[0] = SDL_Rect({0, 0, 0, 0});
    coor[1] = coor[0];
    ren = nullptr;

    borderWidth = 0;

    textAlignX = 2;
    textAlignY = 2;
}

/**
 * @brief clear texture, k = 0 - background, k = 1 - text, anything else will cause segment fault
 * @param k integer, index of textures, 0 will be background, 1 will be text
 * if tes[k] is nullptr, do nothing
 * call SDL_DestroyTexture and after that set tes[k] to be nullptr
*/
void Sketch::clearTexture(int k)
{
    if(tes[k] == nullptr) return ;
    SDL_DestroyTexture(tes[k]);
    tes[k] = nullptr;
}
/**
 * @brief destructor 
 * font and ren will not be deleted because it just a copy of the pointer
 * call clearTexture(0) and clearTexture(1) to delete texture
*/
Sketch::~Sketch()
{
    font = nullptr;
    text.clear();
    clearTexture(0);
    clearTexture(1);
    ren = nullptr;
}
/**
 * @brief create text texture 
 * delete old text texture if exist
 * if text is empty then do nothing
 * make sure that font is not nullptr, otherwise it may cause segment fault.
 * if text texture is greater than background texture, crop it, the top left.
*/
void Sketch::createTextTexture()
{
    clearTexture(1);
    if(text.empty()) return ;

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
    
    tes[1] = SDL_CreateTextureFromSurface(ren, surface);
    
    coor[1].w = surface->w;
    coor[1].h = surface->h;

    crop = coor[1];
    crop.x = 0;
    crop.y = 0;
    
    if(coor[1].w > coor[0].w || coor[1].h > coor[0].h)
    {
        crop = SDL_Rect({
                std::max(0, coor[1].w - coor[0].w), 
                std::max(0, coor[1].h - coor[0].h), 
                coor[0].w, 
                coor[0].h
            });
        coor[1].w = coor[0].w;
        coor[1].h = coor[0].h;
    }

    align();

    SDL_FreeSurface(surface);
}
/**
 * @brief typing text
 * @param ch character that will be add to the end of the text
 * add a character to the end of the text
 * after that new text texture will be created
*/
void Sketch::addChar(char ch)
{
    text = text + ch;
    createTextTexture();
}
/**
 * @brief erase a character 
 * if text is empty then do nothing
 * pop a character from the end of the text
 * after that new text texture will be create 
*/
void Sketch::popChar()
{
    if(text.empty()) return ;
    text.pop_back();
    createTextTexture();
}

/**
 * @brief set text to be s 
 * @param s string that will be set to text
 * set text to be s and create new text texture
*/
void Sketch::setText(std::string s)
{
    text = s;
    createTextTexture();
}
/**
 * @brief set text color to be (r, g, b)
 * @param r interger, red value, 0 - 255
 * @param b interger, blue value, 0 - 255
 * @param g interger, green value, 0 - 255
 * set text color to be (r, g, b) and create new text texture
*/
void Sketch::setTextColor(int r, int g, int b)
{
    fontColor.r = r;
    fontColor.g = g;
    fontColor.b = b;
    createTextTexture();
}

/**
 * @brief return text
 *
*/
const std::string& Sketch::getText()
{
    return text;
}
/**
 * @brief set background color to be c
 * @param c SDL_Color, background color
*/
void Sketch::setColor(SDL_Color c)
{
    color = c;
}
/**
 * @brief set background color to be (r, g, b)
 * @param r interger, red value, 0 - 255
 * @param b interger, blue value, 0 - 255
 * @param g interger, green value, 0 - 255
 * set background color to be (r, g, b)
*/
void Sketch::setColor(int r, int g, int b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

/**
 * @brief set background color to be (r, g, b a)
 * @param r interger, red value, 0 - 255
 * @param b interger, blue value, 0 - 255
 * @param g interger, green value, 0 - 255
 * @param a interger, alpha value, 0 - 255
 * set background color to be (r, g, b, a)
*/
void Sketch::setColor(int r, int g, int b, int a)
{
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

/**
 * @brief set coordinate of sketch
 * @param x interger, x coordinate of the top left corner of the sketch
 * @param y interger, y coordinate of the top left corner of the sketch
 * @param w interger, width of the sketch
 * @param h interger, height of the sketch
 * set coordinate of sketch 
*/
void Sketch::setCoor(int x, int y, int w, int h)
{
    coor[0] = SDL_Rect({x, y, w, h});
    align();
}
/**
 * @brief set coordinate of sketch
 * @param x interger, x coordinate of the top left corner of the sketch
 * set x coordinate of sketch
*/
void Sketch::setX(int x)
{
    coor[0].x = x;
    align();
}
/**
 * @brief set coordinate of sketch
 * @param x, interger, change of x coordinate of the top left corner of the sketch
 * add x to x coordinate of sketch
*/
void Sketch::addX(int x)
{
    coor[0].x += x;
    align();
}

/**
 * @brief set coordinate of sketch
 * @param y interger, change of y coordinate of the top left corner of the sketch
 * add y to y coordinate of sketch
*/
void Sketch::addY(int y)
{
    coor[0].y += y;
    align();
}

/**
 * @brief set coordinate of sketch
 * @param y interger, y coordinate of the top left corner of the sketch
 * set y coordinate of sketch
*/
void Sketch::setY(int y)
{
    coor[0].y = y;
    align();
}
/**
 * @brief set coordinate of sketch
 * @param w interger, width of the sketch
 * set width of sketch
*/
void Sketch::setW(int w)
{
    coor[0].w = w;
    align();
}
/**
 * @brief set coordinate of sketch
 * @param h interger, height of the sketch
 * set height of sketch
*/
void Sketch::setH(int h)
{
    coor[0].h = h;
    align();
}
/**
 * @brief align text texture 
 * align x coordinate of text texture to be in the center of the background texture
*/
void Sketch::setInCenterX()
{
    int x = coor[0].x;
    int w = coor[0].w;
    coor[1].x = x + (w - coor[1].w) / 2;
}
/**
 * @brief align text texture
 * align y coordinate of text texture to be in the center of the background texture
*/
void Sketch::setInCenterY()
{
    int y = coor[0].y;
    int h = coor[0].h;
    coor[1].y = y + (h - coor[1].h) / 2;
}
/**
 * @brief align text texture
 * align x coordinate of text texture to be in the left side of the background texture
*/
void Sketch::setOnLeftSideX()
{
    coor[1].x = coor[0].x;
}
/**
 * @brief align text texture
 * align x coordinate of text texture to be in the right side of the background texture
*/
void Sketch::setOnRightSideX()
{
    int x = coor[0].x;
    int w = coor[0].w;
    coor[1].x = x + w - coor[1].w;
}
/**
 * @brief align text texture
 * align y coordinate of text texture to be in the top side of the background texture
*/
void Sketch::setOnLeftSideY()
{
    coor[1].y = coor[0].y;
}
/**
 * @brief align text texture
 * align y coordinate of text texture to be in the bottom side of the background texture
*/
void Sketch::setOnRightSideY()
{
    int y = coor[0].y;
    int h = coor[0].h;
    coor[1].y = y + h - coor[1].h;
}
/**
 * @brief render
 * if sketch is hided, do nothing
 * render sketch
 * if renderer is nullptr, it may cause error, require setRender() before render()
 * render background fisrt then render text 
*/
void Sketch::render()
{
    if(!isVisible()) return ;
    if(tes[0] != nullptr) SDL_RenderCopy(ren, tes[0], nullptr, &coor[0]);
    if(tes[1] != nullptr) SDL_RenderCopy(ren, tes[1], &crop, &coor[1]);
}
/**
 * @brief set render 
 * @param r address of SDL_Renderer pointer
 * set render of sketch
*/
void Sketch::setRender(SDL_Renderer *&r)
{
    ren = r;
}
/** 
 * @brief set border 
 * 
 * set border of sketch
 * 
 * @param w interger, width of border
 * @param r interger, red value of border color, 0 - 255
 * @param g interger, green value of border color, 0 - 255
 * @param b interger, blue value of border color, 0 - 255
 * @param a interger, alpha value of border color, 0 - 255

*/
void Sketch::setBorder(int w, int r, int g, int b, int a)
{
    borderWidth = w;
    borderColor.r = r;
    borderColor.g = g;
    borderColor.b = b;
    borderColor.a = a;
}
/**
 * @brief set border color 
 * @param r interger, red value of border color, 0 - 255
 * @param g interger, green value of border color, 0 - 255
 * @param b interger, blue value of border color, 0 - 255
 * set border color
*/
void Sketch::setBorderColor(int r, int g, int b)
{
    borderColor.r = r;
    borderColor.g = g;
    borderColor.b = b;
}
/**
 * @brief fill background color with color C
 * @param c SDL_Color, color to fill
 * fill background color with color C
*/
void Sketch::FillWithColor(SDL_Color c)
{
    SDL_Color temp = color;
    color = c;
    FillWithColor();
    color = temp;
}

/**
 * @brief fill background color with default color, which is set by SetColor function
 * fill background color with default color, which is set by SetColor function 
 * at default color is black  
*/
void Sketch::FillWithColor()
{
    int w = coor[0].w;
    int h = coor[0].h;
    clearTexture(0);

    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_BLEND);

    SDL_FillRect(surf, nullptr, SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a));
    
    SDL_Rect borderRect;

    Uint32 c = SDL_MapRGBA(surf->format, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    borderRect = SDL_Rect({0, 0, borderWidth, h});
    SDL_FillRect(surf, &borderRect, c);
    
    borderRect = SDL_Rect({0, 0, w, borderWidth});
    SDL_FillRect(surf, &borderRect, c);

    borderRect = SDL_Rect({0, h - borderWidth, w, borderWidth});
    SDL_FillRect(surf, &borderRect, c);

    borderRect = SDL_Rect({w - borderWidth, 0, borderWidth, h});
    SDL_FillRect(surf, &borderRect, c);
    
    tes[0] = SDL_CreateTextureFromSurface(ren, surf);

    SDL_FreeSurface(surf);

}
/**
 * @brief set cooridnate of sketch from json 

 * if mem is not contain "rect" key, do nothing

 * if in "rect" object contain "x" key, set x coordinate of sketch to be mem["rect"]["x"]

 * if in "rect" object contain "y" key, set y coordinate of sketch to be mem["rect"]["y"]

 * if in "rect" object contain "w" key, set w coordinate of sketch to be mem["rect"]["w"]

 * if in "rect" object contain "h" key, set h coordinate of sketch to be mem["rect"]["h"]

 * example of param mem: 

 * {

 *     "rect": {

 *          "x": 0,

 *          "y": 0,

 *          "w": 0,

 *          "h": 0

 * }

 * @param mem json, contain coordinate of sketch
*/

void Sketch::initRect(const json& mem)
{
    if(mem.contains("rect"))
    {
        if(mem["rect"].contains("x"))
        {
            coor[0].x = mem["rect"]["x"];
        }
        if(mem["rect"].contains("y"))
        {
            coor[0].y = mem["rect"]["y"];
        }
        if(mem["rect"].contains("w"))
        {
            coor[0].w = mem["rect"]["w"];
        }
        if(mem["rect"].contains("h"))
        {
            coor[0].h = mem["rect"]["h"];
        }
    }
}
/**
 * @brief init color from json 
 * 
 * if mem is not contain "color" key, do nothing
 * 
 * if in "color" object contain "r" key, set r color of sketch to be mem["color"]["r"]
 * 
 * if in "color" object contain "g" key, set g color of sketch to be mem["color"]["g"]
 * 
 * if in "color" object contain "b" key, set b color of sketch to be mem["color"]["b"]
 * 
 * if in "color" object contain "a" key, set a color of sketch to be mem["color"]["a"]
 * 
 * example of param mem:
 * 
 * {
 * 
 *    "color": {
 * 
 *         "r": 0,
 * 
 *         "g": 0,
 * 
 *         "b": 0,
 * 
 *         "a": 0
 * 
 *    }
 * 
 * }
 * 
 * @param mem json, contain color of sketch
*/
void Sketch::initColor(const json& mem)
{
    if(mem.contains("color"))
    {
        if(mem["color"].contains("r"))
            color.r = mem["color"]["r"];
        if(mem["color"].contains("g"))
            color.g = mem["color"]["g"];
        if(mem["color"].contains("b"))
            color.b = mem["color"]["b"];
        if(mem["color"].contains("a"))
            color.a = mem["color"]["a"];
        cache = color;
    }
}
/**
 * @brief init font from json
 * 
 * if mem is not contain "font" key, do nothing
 * 
 * get font file and combine with GLOBAL::FontsFolder to get full path of font file
 * 
 * source font from that path and source the size of the font 
 * 
 * if in "font" object contain "rect" key, get rect text 
 * 
 * if in "font" object contain "color" key, get color text
 * 
 * if int "font" object contain "text", set default text of sketch to be mem["font"]["text"]
 * 
 * example of param mem:
 * 
 * {
 * 
 *    "font": {
 * 
 *         "name": "font.ttf",
 * 
 *         "size": 0,
 * 
 *         "rect": {
 * 
 *              "x": 0,
 * 
 *              "y": 0,
 * 
 *              "w": 0,
 * 
 *              "h": 0
 * 
 *        },
 * 
 *        "color": {
 * 
 *              "r": 0,
 * 
 *              "g": 0,
 * 
 *              "b": 0,
 * 
 *              "a": 0
 * 
 *        },
 * 
 *        "text": "text"
 * 
 *    }
 * 
 * }
 * 
 * @param mem json, contain font of sketch
*/
void Sketch::initFont(const json& mem)
{
    if(!mem.contains("font")) return ;
    if(mem["font"].contains("name") && mem["font"].contains("size"))
    {
        char* name = combineLink(GLOBAL::FontsFolder, mem["font"]["name"].get<std::string>().c_str());
        if(font != nullptr) 
        {
            TTF_CloseFont(font);
            font = nullptr;
        }
        font = TTF_OpenFont(name, mem["font"]["size"]);
    }
    if(mem["font"].contains("rect"))
    {
        if(mem["font"]["rect"].contains("x"))
            coor[1].x = mem["font"]["rect"]["x"];
        if(mem["font"]["rect"].contains("y"))
            coor[1].y = mem["font"]["rect"]["y"];
        if(mem["font"]["rect"].contains("align X"))
            textAlignX = mem["font"]["rect"]["align X"];
        if(mem["font"]["rect"].contains("align Y"))
            textAlignX = mem["font"]["rect"]["align Y"];
    }
    if(mem["font"].contains("color"))
    {
        if(mem["font"]["color"].contains("r"))
        {
            fontColor.r = mem["font"]["color"]["r"];
        }
        if(mem["font"]["color"].contains("g"))
        {
            fontColor.g = mem["font"]["color"]["g"];
        }
        if(mem["font"]["color"].contains("b"))
        {
            fontColor.b = mem["font"]["color"]["b"];
        }
        if(mem["font"]["color"].contains("a"))
        {
            fontColor.a = mem["font"]["color"]["a"];
        }
    }
    if(mem["font"].contains("text"))
    {
        setText(mem["font"]["text"].get<std::string>());
    }
}
/**
 * @brief init border from json
 * 
 * if mem is not contain "border" key, do nothing
 * 
 * if in "border" object contain "width" key, set width of border to be mem["border"]["width"]
 * 
 * if in "border" object contain "color" key, set color of border to be mem["border"]["color"]
 * 
 * example of param mem:
 * 
 * {
 * 
 *    "border": {
 * 
 *        "width": 0,
 * 
 *        "color": {
 * 
 *          "r": 0,
 * 
 *          "g": 0,
 * 
 *          "b": 0,
 * 
 *          "a": 0
 * 
 *        }
 * 
 *    }
 * 
 * }
 * 
 * @param mem json, contain border of sketch
*/
void Sketch::initBorder(const json& mem)
{
    if(!mem.contains("border")) return ;
    if(mem["border"].contains("width"))
        borderWidth = mem["border"]["width"];

    if(mem["border"].contains("color"))
    {
        if(mem["border"]["color"].contains("r"))
        {
            borderColor.r = mem["border"]["color"]["r"];
        }
        if(mem["border"]["color"].contains("g"))
        {
            borderColor.g = mem["border"]["color"]["g"];
        }
        if(mem["border"]["color"].contains("b"))
        {
            borderColor.b = mem["border"]["color"]["b"];
        }
        if(mem["border"]["color"].contains("a"))
        {
            borderColor.a = mem["border"]["color"]["a"];
        }
    }
}
/**
 * @brief init sketch from json
 * 
 * this function call initRect, initColor, initFont, initBorder
 * this function also change visible, if mem contain "visible" key
 * this function will fill with color, if mem contain "fill with color" key
 * 
 * @param mem json 
 * 
 * example of param mem:
 * 
 * {
 * 
 *      "rect": 
 * 
 *      {
 * 
 *      },
 * 
 *      "color":
 * 
 *      {
 * 
 *      },
 * 
 *      "font":
 * 
 *      {
 * 
 *      },
 * 
 *      "border":
 * 
 *      {
 * 
 *      },
 * 
 *      "text": "text",
 * 
 *      "visible": true,
 * 
 *     "fill with color": true
 * 
 * }
*/
void Sketch::init(const json &mem)
{
    
    initRect(mem);
    initColor(mem);
    initFont(mem);
    initBorder(mem);

    if(mem.contains("text"))
    {
        setText(mem["text"].get<std::string>());
    }
    if(mem.contains("visible"))
        visible = mem["visible"];
    if(mem.contains("fill with color"))
    {
        FillWithColor();
    }
}
/**
 * @brief align text 
 * this function will call setOnLeftSideX, setOnRightSideX, setInCenterX, setOnLeftSideY, setOnRightSideY, setInCenterY
*/
void Sketch::align()
{

    if(textAlignX == 1) setOnLeftSideX();
    if(textAlignX == 2) setInCenterX();
    if(textAlignX == 3) setOnRightSideX();

    if(textAlignY == 1) setOnLeftSideY();
    if(textAlignY == 2) setInCenterY();
    if(textAlignY == 3) setOnRightSideY();
}
/**
 * @brief get coordinate
 * this function will return coordinate of background of sketch
 * @return SDL_Rect
*/
SDL_Rect Sketch::getCoor()
{
    return coor[0];
}
/**
 * @brief get visible
 * this function will return visible of sketch
 * @return bool
*/
bool Sketch::isVisible()
{
    return visible;
}
/**
 * @brief show the sketch 
 * this function will set visible to true, that will enable the sketch to be rendered
*/
void Sketch::show()
{
    visible = true;
}
/**
 * @brief hide the sketch
 * this function will set visible to false, that will disable the sketch to be rendered
*/
void Sketch::hide()
{
    visible = false;
}
/**
 * @brief determine a point is lie inside sketch or not 
 * this function will return true if point (x, y) lie inside sketch
 * @param x int
 * @param y int
 * @return bool
*/
bool Sketch::isLieInside(int x, int y)
{
    if(x < coor[0].x || coor[0].x + coor[0].w <= x) return false;
    if(y < coor[0].y || coor[0].y + coor[0].y <= y) return false;
    return true;
}
/**
 * @brief animation of sketch to move the sketch to point (x, y) in time (second)
 * this function will move the sketch to point (x, y) in time (second)
 * @param x int
 * @param y int
 * @param time double
*/
void Sketch::moveTo(int x, int y, double time)
{
    int dx = x - getCoor().x;
    int dy = y - getCoor().y;
    
    if(diff(time, 0))
    {
        setX(x);
        setY(y);
        return ;
    }

    double velo;

    if(abs(dx) < abs(dy))
        velo = dy / time;
    else velo = dx / time;  
     
    int loop = std::min(80.0, abs(velo * time));

    time = time / loop; 
    
    for(int i = 0; i <= loop; i++)
    {
        Uint32 startTime = SDL_GetTicks();

        addX(-dx * (i - 1) / loop);
        addX(dx * i / loop);
        addY(-dy * (i - 1) / loop);
        addY(dy * i / loop);
        render(); 
        Uint32 deltaTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();
        if(deltaTime <= time * 1000)
            SDL_Delay(time * 1000 - deltaTime);
    }
}
/**
 * @brief hightlight the sketch
 * this function will change color of background to invert color
*/
void Sketch::highlight()
{
    color.r = 255 - color.r;
    color.g = 255 - color.g;
    color.b = 255 - color.g;
    if(color.r > 20 && color.g > 20 && color.b > 20)
    {
        color.r -= color.r * 0.3;
        color.g -= color.g * 0.3;
        color.b -= color.b * 0.3;
    }
    FillWithColor();
}
/**
 * @brief unhightlight the sketch
 * this function will change color of background to normal color
*/
void Sketch::unHighlight()
{
    color = cache;
    FillWithColor();
}
