#ifndef json_sfml
#define json_sfml

#include "json.hpp"

using namespace nlohmann;

///\brief
/// turns a color into a json object
///\details
/// turns a color into a json object
inline void color_to_json(json &input, const sf::Color &color)
{

    input["r"] = color.r;
    input["g"] = color.g;
    input["b"] = color.b;
    input["a"] = color.a;
}

///\brief
/// turns a vector2f into a json object
///\details
/// turns a vector2f into a json object
inline void vector2f_to_json(json &input, const sf::Vector2f &vector)
{

    input["x"] = vector.x;
    input["y"] = vector.y;
}

///\brief
/// turns a json object into a sf::Color
///\details
/// turns a json object into a sf::Color
/// depencies is that the object has an r,g,b and a object
inline sf::Color json_to_color(json input)
{

    return sf::Color(
        int(input["r"]),
        int(input["g"]),
        int(input["b"]),
        int(input["a"]));
}

///\brief
/// turns a json object into a vector2f
///\details
/// turns a json object into a vector2f
/// depencies is that the object has an x and y object
inline sf::Vector2f json_to_vector2f(json input)
{

    return sf::Vector2f(
        float(input["x"]),
        float(input["y"]));
}

#endif