#ifndef TEXTURE_LOADING_CPP
#define TEXTURE_LOADING_CPP

#include "drawables.hpp"


// Function to load all the textures that are going to be used in the game in one place
// An std::map to be more specific
inline void load_textures(std::map<std::string, Picture*>& textures) {

	std::cout << "Loading Textures..." << std::endl;
	{
		textures["Player Texture"] = new Picture({ 10,10 }, { 100,100 }, "img/wovo idle.png");
		{
			textures["backdrop 1"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 1.png");
			textures["backdrop 2"] = new Picture({ 10,10 }, { 100,100 }, "img/backdrop 2.png");
		}
		{
			textures["Portal 1"] = new Picture({ 0,0 }, { 100,100 }, "img/test2.jpg");
			textures["Portal 2"] = new Picture({ 0,0 }, { 100,100 }, "img/test3.jpeg");
		}
		{
			textures["walk1"] = new Picture({ {0,0}, {46, 126}, "img/walking1.png" });
			textures["walk2"] = new Picture({ {0,0}, {46, 126}, "img/walking2.png" });
			textures["walk3"] = new Picture({ {0,0}, {46, 126}, "img/walking3.png" });
			textures["walk4"] = new Picture({ {0,0}, {46, 126}, "img/walking4.png" });
			textures["walk5"] = new Picture({ {0,0}, {46, 126}, "img/walking5.png" });
			textures["walk6"] = new Picture({ {0,0}, {46, 126}, "img/walking6.png" });
			textures["walk7"] = new Picture({ {0,0}, {46, 126}, "img/walking7.png" });
		}
		{
			textures["left1"] = new Picture({ {0,0}, {46, 126}, "img/left1.png" });
			textures["left2"] = new Picture({ {0,0}, {46, 126}, "img/left2.png" });
			textures["left3"] = new Picture({ {0,0}, {46, 126}, "img/left3.png" });
			textures["left4"] = new Picture({ {0,0}, {46, 126}, "img/left4.png" });
			textures["left5"] = new Picture({ {0,0}, {46, 126}, "img/left5.png" });
			textures["left6"] = new Picture({ {0,0}, {46, 126}, "img/left6.png" });
			textures["left7"] = new Picture({ {0,0}, {46, 126}, "img/left7.png" });
		}

		{
			textures["green1"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green1.png" });
			textures["green2"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green2.png" });
			textures["green3"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green3.png" });
			textures["green4"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green4.png" });
			textures["green5"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green5.png" });
			textures["green6"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green6.png" });
			textures["green7"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green7.png" });
			textures["green8"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green8.png" });
			textures["green9"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green9.png" });
			textures["green10"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green10.png" });
			textures["green11"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green11.png" });
			textures["green12"] = new Picture({ {0,0}, {46, 126}, "img/portals/Portal sprite green12.png" });
		}
		{
			textures["purple1"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple1.png" });
			textures["purple2"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple2.png" });
			textures["purple3"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple3.png" });
			textures["purple4"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple4.png" });
			textures["purple5"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple5.png" });
			textures["purple6"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple6.png" });
			textures["purple7"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple7.png" });
			textures["purple8"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple8.png" });
			textures["purple9"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple9.png" });
			textures["purple10"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple10.png" });
			textures["purple11"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple11.png" });
			textures["purple12"] = new Picture({ {0,0}, {46, 126}, "img/portals/purple12.png" });
		}
		{
			textures["filling"] = new Picture({ {0,0}, {100, 100}, "img/tiles/Filling normal.png" });
			textures["floor down"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor upsidedown.png" });
			textures["corner left down"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner flat left down.png" });
			textures["corner left"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner flat left.png" });
			textures["corner right down"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner flat right down.png" });
			textures["corner right"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner flat right.png" });
			textures["corner down left"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner left down.png" });
			textures["corner left in"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner left.png" });
			textures["corner rigth in down"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner right down.png" });
			textures["corner right in"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor corner right.png" });
			textures["floor"] = new Picture({ {0,0}, {100, 100}, "img/tiles/Floor normal.png" });
			textures["spike"] = new Picture({ {0,0}, {100, 100}, "img/tiles/spike.png" });
			textures["wall left"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor wall left.png" });
			textures["wall right"] = new Picture({ {0,0}, {100, 100}, "img/tiles/floor wall right.png" });
			textures["floor1"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/floor1.png" });
			textures["floor2"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/floor2.png" });
			textures["floor3"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/floor3.png" });
			textures["floor4"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/floor4.png" });
			textures["corner1"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/corner1.png" });
			textures["corner2"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/corner2.png" });
			textures["corner3"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/corner3.png" });
			textures["corner4"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/corner4.png" });
			textures["hook1"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/hook1.png" });
			textures["hook2"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/hook2.png" });
			textures["hook3"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/hook3.png" });
			textures["hook4"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/hook4.png" });
			textures["map"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/floor.png" });
			textures["fishstick"] = new Picture({ {0,0}, {100, 100}, "img/void tiles/fishstick.png" });

		}
	}
}





#endif // !TEXTURE_LOADING_CPP