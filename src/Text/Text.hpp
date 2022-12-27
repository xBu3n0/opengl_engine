#ifndef TEXT_HPP
#define TEXT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace text
{
    struct Character
    {
        GLuint VAO, VBO;

        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2 Size; // Size of glyph
        glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
        unsigned int Advance; // Offset to advance to next glyph

        std::string text;
        glm::vec2 pos;
        float scale;
        glm::vec3 color;
    };

    class Text
    {
    public:
        Text();
    
    public:
        Character c;
        GLuint s;
        std::map<char, Character> Characters;

    
    private:
        FT_Library ft;
        FT_Face face;
    };

    void setShader(Text& t, GLuint shader);
}

#endif