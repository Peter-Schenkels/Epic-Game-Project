#include "portal.hpp"


Portal::Portal(sf::Vector2f position, sf::Vector2f size, std::string entrance, std::vector<Animation> animations, bool order) :
	Drawable(position, size, "Portal", "White"),
	entrance(entrance),
	animation_controller(animations),
	order(order),
	portal_size(size)
{
	portal_align();
}

// Draw portal
void Portal::drawable_draw(sf::RenderWindow& window){
	body = animation_controller.get_frame();
	body->drawable_draw(window);
	// The commented part is for debugging: showing the portals' hitbox
	/*sf::RectangleShape hitbox_draw(sf::Vector2f(hitbox.width, hitbox.height));
	hitbox_draw.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	hitbox_draw.setFillColor(sf::Color::White);
	window.draw(hitbox_draw);*/
}

// Return visual
std::string Portal::drawable_get_visual() { 
	return color; 
}

// Update portal
void Portal::drawable_update() {
	animation_controller.update();
	body->drawable_set_position(location);
	body->drawable_update();
	//std::cout << location.x << " " << location.y << std::endl;
	hitbox = sf::FloatRect(location.x - 32, location.y - 32, 64, 64);

}

// To get first time placement
bool Portal::portal_placed_get() {
	return placed;
}

// for first time placement
void Portal::portal_placed_set(bool new_value) {
	placed = new_value;
}

// Set entrance
void Portal::portal_set_entrance(std::string new_entrance) {
	entrance = new_entrance;
}

// Return doorway
std::string Portal::portal_get_entrance() {
	return entrance;
}

// Return order
bool Portal::portal_get_order() {
	return order;
}

void Portal::portal_align() {
	float rotation;
	std::array<std::string, 4> orientations{ "RIGHT", "BOTTOM", "LEFT", "TOP" };

	for (unsigned int i = 0; i < 4; i++) {
		if (orientations[i] == entrance) {
			rotation = float(i * 90);
		}
	}
	animation_controller.animation_controller_set_state("Idle");
	animation_controller.animation_set_size("Idle", portal_size);
	animation_controller.set_origin_of_animation("Idle", { portal_size.x / 4, portal_size.y / 4 });
	animation_controller.rotate_animation("Idle", rotation);
	body = animation_controller.get_frame();
}
