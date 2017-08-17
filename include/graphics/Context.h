#pragma once

struct GLFWwindow;

class Context
{
private:
	GLFWwindow *handle;

public:
	// Pop up our window in windows OS
	bool init(size_t w = 800, size_t h = 600, 
						const char *title = "Graphics");

	// updating the window
		// this is what determines the FPS
	bool step();

	bool term();

	bool getKey(int key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();
};