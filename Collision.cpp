#include "Collision.h"
#include "Engine.h"
Collision* Collision::s_instance = nullptr;
//Collision::Collision() {
	/*create a map for all collision possible rectangles, give all the pixels in that rec a number !=0
	when PDrect updates, check if the pixel has value!=0, if it does, than that means there is a box
	Create a map of value to pointer of sdl_rect 
	eg.
	Lets say old position = 150,45
	new updated position should be 151,45
	check m1[{151,45}]
	lets say m1[{151,45}] == 3
	check another map lets say m2
	check m2[key] i.e. m2[3];
	lets say m2[3] p1(sdlrect pointer

	-> number coding
		0 - no collision
		1 - only Horizontal collision
		2 - only vertical collision
		3 - vertical and horizontal collision
	*/
//}
//write all sdl_rect in  xml, call a collision function to read the file and push

bool Collision::Load(const std::string& id, const std::string& source) {
	this->id = id;
	this->source = source;
	return Parse(id, source);
}

bool Collision::CheckCollision(SDL_Rect a) {
	for (auto i : v) {
		if (SDL_HasIntersection(&a, &i)) return true;
	}
	return false;
}
bool Collision::Parse(std::string id,std:: string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cout << "can not load collision.xml file" << source << std::endl;
		return false;
	}
	TiXmlElement* root = xml.RootElement();
	/*TiXmlElement* boxes = root->FirstChildElement("Boxes");
	if (!boxes) {
		std::cout << "No 'Boxes' element found in XML." << std::endl;
		return false;
	}*/
	for (TiXmlElement* group = root->FirstChildElement(); group; group = group->NextSiblingElement()) {
		SDL_Rect rectData;

		// Get and store the values of x, y, w, and h
		/*if (group->QueryIntAttribute("x", &rectData.x) != TIXML_SUCCESS ||
			group->QueryIntAttribute("y", &rectData.y) != TIXML_SUCCESS ||
			group->QueryIntAttribute("w", &rectData.w) != TIXML_SUCCESS ||
			group->QueryIntAttribute("h", &rectData.h) != TIXML_SUCCESS) {
			std::cout << "Error parsing 'group' attributes in XML." << std::endl;
		}*/
		if (group->QueryIntAttribute("x", &rectData.x) != TIXML_SUCCESS) {
			std::cout << "Error parsing 'x' attribute in XML for group." << std::endl;
			return false;
		}
		if (group->QueryIntAttribute("y", &rectData.y) != TIXML_SUCCESS) {
			std::cout << "Error parsing 'y' attribute in XML for group." << std::endl;
			return false;
		}
		if (group->QueryIntAttribute("w", &rectData.w) != TIXML_SUCCESS) {
			std::cout << "Error parsing 'w' attribute in XML for group." << std::endl;
			return false;
		}
		if (group->QueryIntAttribute("h", &rectData.h) != TIXML_SUCCESS) {
			std::cout << "Error parsing 'h' attribute in XML for group." << std::endl;
			return false;
		}
		// Push the data structure into the vector
		v.push_back(rectData);
	}
	return true;
}

void Collision::Render() {
	//std::cout << v.size() << std::endl;
	for (int i = 0; i < v.size(); i++) {
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(), 255, 255, 255, 100);//keep this part up to see the color of the rect you draw
		SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), &v[i]);
		//std::cout << "Rendered " << v[i].x << "," << v[i].y << "," << v[i].w << "," << v[i].h << std::endl;
	}
}