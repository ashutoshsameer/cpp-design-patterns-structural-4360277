#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Texture
{
public:
    explicit Texture(const string &fileName) : m_FileName(fileName), m_Id(arc4random_uniform(INT_MAX)) {}

    const string description() const
    {
        return "<" + m_FileName + " id" + to_string(m_Id) + ">";
    }
    ~Texture()
    {
        cout << "Destructing " << description() << endl;
    }
    // other texture manipulation methods
private:
    const string m_FileName;
    const int m_Id;
};

class Sprite
{
public:
    Sprite(const Texture *texture) : m_Texture(texture)
    {
        cout << "Creating sprite with texture: " << m_Texture->description() << endl;
    }

    void setPositionSize(int x, int y, int width, int height)
    {
        m_X = x;
        m_Y = y;
        m_Height = height;
        m_Width = width;
    }

    void render()
    {
        // draw sprite
        cout << "Rendering sprite with texture: " << m_Texture->description() << endl;
    }

    // ~Sprite()
    // {
    //     cout << "Destructing sprite with texture " << m_Texture->description() << endl;
    //     delete m_Texture;
    // }

private:
    int m_Width;
    int m_Height;
    int m_X;
    int m_Y;

    const Texture *m_Texture;
};

class SpriteFactory
{
public:
    Sprite* makeSprite(const string& filename)
    {
        auto it = d_spritePool.find(filename);
        if (it != d_spritePool.end())
        {
            return it->second;
        }

        const auto texture = getTexture(filename);
        auto [newIt, _] = d_spritePool.emplace(filename, new Sprite(texture));
        return newIt->second;
    }

    ~SpriteFactory()
    {
        // cout << "Destructing sprite with texture " << m_Texture->description() << endl;
        // delete m_Texture;
        for (auto &[filename, sprite] : d_spritePool)
        {
            delete sprite;
        }
        for (auto &[filename, texture] : d_texturePool)
        {
            delete texture;
        }
    }
private:
    unordered_map<string, Sprite*> d_spritePool;
    unordered_map<string, Texture*> d_texturePool;

    const Texture* getTexture(const string& filename)
    {
        auto it = d_texturePool.find(filename);
        if (it != d_texturePool.end())
        {
            return it->second;
        }
        auto [newIt, _] = d_texturePool.emplace(filename, new Texture(filename));
        return newIt->second;
    }
};

int main()
{
    // create a list of sprite objects
    vector<Sprite*> sprites;
    const int numSprites = 10;
    const string textureFile = "spaceship.png";

    SpriteFactory sf;

    for (int i = 0; i < numSprites; ++i)
    {
        auto sprite = sf.makeSprite(textureFile);
        sprite->setPositionSize(10, 10, i * 10, i * 10);
        // new Sprite(10, 10, i * 10, i * 10, textureFile);
        sprites.push_back(sprite);
    }

    // draw all sprites
    for (auto &sprite : sprites)
    {
        sprite->render();
    }

    // // cleanup
    // for (auto &sprite : sprites)
    // {
    //     delete(sprite);
    // }

    return 0;
}
