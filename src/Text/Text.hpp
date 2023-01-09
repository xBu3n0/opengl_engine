#ifndef TEXT_HPP
#define TEXT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#include <windows.h>
#endif
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

        unsigned int TextureID = 0; // ID handle of the glyph texture
        glm::ivec2 Size = glm::ivec2(0.0f, 0.0f); // Size of glyph
        glm::ivec2 Bearing = glm::ivec2(0.0f, 0.0f); // Offset from baseline to left/top of glyph
        unsigned int Advance = 0; // Offset to advance to next glyph

        std::string text = "";
        glm::vec2 pos = glm::vec2(0.0f, 0.0f);
        float scale = 1.0f;
        glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
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