#include <iostream>
#include <memory>
#include <fstream>

//thse are the SFML and ImGui header files. this uses SFML 2.6.0
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

//remember this syntax
//auto p = std::make_shared<someClass>(args);

class Circle
{
public:
	std::string name = "";
	//float init_posX = 0.0f;
	//float init_posY = 0.0f;
	float init_speedX = 0.0f, init_speedY = 0.0f;
	//int colorR = 0, colorG = 0, colorB = 0;
	//int radius = 1;
	//std::vector<Circle> cList;

	Circle(const std::string& n, float& sx, float& sy)
		: name(n), init_speedX(sx), init_speedY(sy)
	{
	}

	Circle() {}
	std::string getCName() const
	{
		return name;
	}
	float getSpeedX() const
	{
		return init_speedX;
	}
	float getSpeedY() const
	{
		return init_speedY;
	}
	void setSpeedX(float x)
	{
		init_speedX = x;
	}
	void setSpeedY(float y)
	{
		init_speedY = y;
	}
	
};

class Rectangle
{
public:
	std::string name = "";
	//float init_posX = 0.0f;
	//float init_posY = 0.0f;
	float init_speedX = 0.0f, init_speedY = 0.0f;
	//int colorR = 0, colorG = 0, colorB = 0;
	//int radius = 1;
	//std::vector<Circle> cList;

	Rectangle(const std::string& n, float& sx, float& sy)
		: name(n), init_speedX(sx), init_speedY(sy)
	{
	}

	Rectangle() {}
	std::string getRName() const
	{
		return name;
	}
	float getSpeedX() const
	{
		return init_speedX;
	}
	float getSpeedY() const
	{
		return init_speedY;
	}
	void setSpeedX(float x)
	{
		init_speedX = x;
	}
	void setSpeedY(float y)
	{
		init_speedY = y;
	}

};

class Shape
{
public:
	std::string shape_name;
	std::vector<Circle> m_circ;
	std::vector<Rectangle> m_rect;

	Shape(const std::string sName)
		: shape_name(sName)
	{
	}
	Shape() {}
	void addCircle(const Circle& c)
	{
		m_circ.push_back(c);
	}
	const std::vector<Circle>& getCircles() const
	{
		return m_circ;
	}
	void addRectangle(const Rectangle& r)
	{
		m_rect.push_back(r);
	}
	const std::vector<Rectangle>& getRectangles() const
	{
		return m_rect;
	}

	void loadFromFile(const std::string& filename)
	{
		std::ifstream fin(filename);
		std::string label, shapeName;
		float posX, posY;
		float width, height;
		int roy, giy, biv, rad;
		float speedX, speedY;

		while (fin >> label)
		{
			if (label == "Circle")
			{
				fin >> shapeName >> posX >> posY >> speedX >> speedY >> roy >> giy >> biv >> rad;
				addCircle(Circle(shapeName, posX, posY));
			}
			if (label == "Rectangle")
			{
				fin >> shapeName >> posX >> posY >> speedX >> speedY >> roy >> giy >> biv >> width >> height;
				addRectangle(Rectangle(shapeName, speedX, speedY));
			}

		}

	}
};

class FontClass
{
public:
	std::string fontName = "";
	int fontSize = 4, fRoy = 0, fGiy = 0, fBiv = 255;

	FontClass(const std::string& fName, int& fSize, int& fR, int& fG, int& fB)
		: fontName(fName), fontSize(fSize), fRoy(fR), fGiy(fG), fBiv(fB)
	{
	}
	FontClass() {}

	//font setters
	void setFName(std::string fn)
	{
		fontName = fn;
	}
	void setSize(int size)
	{
		fontSize = size;
	}
	void setR(int r)
	{
		fRoy = r;
	}
	void setG(int g)
	{
		fGiy = g;
	}
	void setB(int b)
	{
		fBiv = b;
	}
	//font getters
	std::string getFName() const
	{
		return fontName;
	}
	int getFSize() const
	{
		return fontSize;
	}
	int getR() const
	{
		return fRoy;
	}
	int getG() const
	{
		return fGiy;
	}
	int getB() const
	{
		return fBiv;
	}

	void loadFromFile(const std::string& filename)
	{
		std::ifstream fin(filename);
		std::string label, fontName;
		int fSize;
		int roy, giy, biv;


		while (fin >> label)
		{
			fin >> fontName >> fSize >> roy >> giy >> biv;
			setFName(fontName);
			setSize(fSize);
			setR(roy);
			setG(giy);
			setB(biv);
		}

	}
};




int main(int argc, char* argv[])
{
	std::string label;
	int wWidth = 0;
	int wHeight = 0;
	float circleRadius = 50;
	float circleSpeedX = 40;
	float circleSpeedY = 0.5f;

	std::ifstream filein;
	filein.open("Config.txt");
	while (filein >> label)
	{
		if (label == "Window")
		{
			filein >> wWidth >> wHeight;
		}
	}












	Shape shapes;
	shapes.loadFromFile("Config.txt");

	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML Works!");
	window.setFramerateLimit(60);

	//initialize imgui and create a clock used for internal timing
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;

	//scale the imgui ui by a given factor, does not affect text size.
	ImGui::GetStyle().ScaleAllSizes(1.0f);

	//imgui color wheel requires floats from 0-1 instead of ints from 0 - 255
	//float c[3] = { 0.0f, 1.0f, 1.0f };

	//let's make a shape that we will draw to the scren
	
	bool drawCircle = true;
	bool drawText = true;






















	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
			
			//this event is triggered when a key is pressed
			if (event.type == sf::Event::KeyPressed)
			{
				// print the key that was pressed to the console
				std::cout << "Key pressed with code = " << event.key.code << "\n";


			}
		}

		//update imgui for this frame with the time that the last frame took
		ImGui::SFML::Update(window, deltaClock.restart());

		//draw the ui
		ImGui::Begin("IMGUI Window Title");
		ImGui::Text("Window Imgui Text");
		ImGui::Checkbox("Draw Circle", &drawCircle);
		ImGui::SameLine();
		ImGui::Checkbox("Draw Text", &drawText);
		ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
		ImGui::End();

		//this clears the window for the next frame
		window.clear();

		

		//Tells the IMGUI interface to render over the window (basically)
		ImGui::SFML::Render(window);

		for (auto& c : shapes.getCircles())
		{
			sf::CircleShape circle(circleRadius);
			circle.setPosition(c.getSpeedX(), c.getSpeedY());
			circle.setFillColor(sf::Color(250, 100, 78));
			std::cout << "NUmber of circles" << shapes.getCircles().size() << std::endl;
			std::cout << "Circle Position:" << c.getSpeedX() << ",  " << c.getSpeedY() << std::endl;
			window.draw(circle);
		}
		
		
		

		

		window.display();
	}


	return 0;
}