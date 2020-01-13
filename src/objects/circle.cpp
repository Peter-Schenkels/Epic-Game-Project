//
// Created by pieper on 01-01-20.
//

#include "circle.hpp"


void Circle::update() {
    body.setPosition(position);
    body.setFillColor(color);
    if (selected){
        body.setOutlineThickness(2);
    } else {
        body.setOutlineThickness(0);
    }
}

void Circle::draw(sf::RenderWindow & window) {
    window.draw(body);
}

json Circle::export_to_json(json object) {
    color_to_json(object["color"], color);
    object["radius"] = radius;
    vector2f_to_json(object["position"], position);
    object["type"] = "Circle";
    return object;
}