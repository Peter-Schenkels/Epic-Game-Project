//
// Created by pieper on 01-01-20.
//

#include "rectangle.hpp"




void Rectangle::update() {
    body.setPosition(position);
    body.setFillColor(color);
    if (selected){
        body.setOutlineThickness(2);
    } else {
        body.setOutlineThickness(0);
    }
}


json Rectangle::export_to_json(json object){

    color_to_json(object["color"], color);
    vector2f_to_json(object["size"], size);
    vector2f_to_json(object["position"], position);
    object["type"] = "Rectangle";
    return object;

}