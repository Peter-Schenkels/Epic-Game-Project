#ifndef FACTORY_HPP
#define FACTORY_HPP
#pragma warning(disable : 4996)

// factory.hpp
// Daniel van Eijk-Bos Bulkowski, 02-Dec-19, Version 1.1

// Functions for:
// - Reading objects from a file
// - Writing objects to a file

#include "drawables.hpp"


std::vector<Drawable*> drawable_object_read(std::string link, std::map<std::string, Picture*>& textures) {
	// Reads drawable objects from given file by writing all the text to a string
	// and afterwards splitting the string into usable parts
	std::vector<Drawable*> drawables;
	std::ifstream input(link);

	Json::Reader reader;
	Json::Value objects;

	// Exception in case there's a problem with the json file
	try {
		reader.parse(input, objects);
	}
	catch (Json::RuntimeError) {
		std::cout << "Error reading input json file";
		return drawables;
	}

	// Loop through all the objects and save them to drawables
	for (auto object : objects["Drawables"]["Circles"]) {
		drawables.push_back(new Circle{ sf::Vector2f(object["position_x"].asFloat(), object["position_y"].asFloat()),
			object["radius"].asFloat(), object["color"].asString() });
	}

	for (auto object : objects["Drawables"]["Pictures"]) {

		Picture* new_picture = new Picture{ sf::Vector2f(object["position_x"].asFloat(), object["position_y"].asFloat()),
		sf::Vector2f(object["size_x"].asFloat(), object["size_y"].asFloat()), object["link"].asString() };
		drawables.push_back(new_picture);
		new_picture->drawable_set_name(object["name"].asString());
		textures[new_picture->drawable_get_name()] = new_picture;

	}

	for (auto object : objects["Drawables"]["Rectangles"]) {

		std::string name = object["name"].asString();
		Rectangle* new_rectangle = new Rectangle{ sf::Vector2f(object["position_x"].asFloat(), object["position_y"].asFloat()),
			sf::Vector2f(object["size_x"].asFloat(), object["size_y"].asFloat()), textures[name] };
		std::cout << name << std::endl;
		new_rectangle->drawable_set_name(name);
		drawables.push_back(new_rectangle);

	}



	return drawables;
}


void drawable_object_write(std::string link, std::vector<Drawable*> drawables) {
	// Writes the drawable objects in drawables to the given json file
	std::ofstream output(link);
	Json::Value event;
	std::array<int, 3> count{ 0, 0, 0 };

	// Loop through all the drawable objects and store them with their corresponding keys, afterwards write these to the file
	for (auto object : drawables) {
		auto type = object->drawable_get_type();

		if (type == "PICTURE") {
			event["Drawables"]["Pictures"][count[1]]["position_x"] = object->drawable_get_location().x;
			event["Drawables"]["Pictures"][count[1]]["position_y"] = object->drawable_get_location().y;
			event["Drawables"]["Pictures"][count[1]]["link"] = object->drawable_get_visual();
			event["Drawables"]["Pictures"][count[1]]["size_x"] = object->drawable_get_size().x;
			event["Drawables"]["Pictures"][count[1]]["size_y"] = object->drawable_get_size().y;
			event["Drawables"]["Pictures"][count[1]]["name"] = object->drawable_get_name();
			count[0]++;
		}
		else if (type == "CIRCLE") {
			event["Drawables"]["Circles"][count[1]]["position_x"] = object->drawable_get_location().x;
			event["Drawables"]["Circles"][count[1]]["position_y"] = object->drawable_get_location().y;
			event["Drawables"]["Circles"][count[1]]["color"] = object->drawable_get_visual();
			event["Drawables"]["Circles"][count[1]]["radius"] = object->drawable_get_size().x / 2;
			count[1]++;
		}
		else if (type == "RECTANGLE") {
			event["Drawables"]["Rectangles"][count[2]]["position_x"] = object->drawable_get_location().x;
			event["Drawables"]["Rectangles"][count[2]]["position_y"] = object->drawable_get_location().y;
			event["Drawables"]["Rectangles"][count[2]]["name"] = object->drawable_get_name();
			event["Drawables"]["Rectangles"][count[2]]["size_x"] = object->drawable_get_size().x;
			event["Drawables"]["Rectangles"][count[2]]["size_y"] = object->drawable_get_size().y;
			count[2]++;
		}

	}

	output << event;
}


#endif