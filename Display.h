#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <deque>
using std::vector;
using std::string;
using std::deque;

struct pixel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

struct LineStruct {
	string frequency;
	int y;
};

class Display
{
private:
	//Member Vars
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_Surface* imageSurface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* imagetexture = nullptr;
	TTF_Font* font = nullptr;

	int windowWidth = 0, windowHeight = 0;

	double omega;

	vector<unsigned char> pixelArray;
	deque<double> magnitudeQueue;
	vector<LineStruct> gridLines;

	//Singleton Constructors
	Display() {	}
	Display(const Display&) = delete;
	Display& operator=(const Display&) = delete;

public:
	enum class DispErrorType {
		ERR_INIT_VIDEO, ERR_LOAD_IMAGE, ERR_CREATE_WINDOW,
		ERR_CREATE_RENDERER, ERR_CREATE_TEXTURE, ERR_INIT_FONT
	};

	~Display();

	// Singleton getter: used to retrieve BY REFERENCE the ONLY instance of Display that can exist
	static Display& getInstance() {
		static Display dispInst;
		return dispInst;
	}

	// Initializes SDL Window Interfaces
	void init();

	// Handles window creation for the class via SDL methods
	void createWindow(const char* title, int pos_x, int pos_y, int w, int h, uint32_t flags);

	// Renders the visualization to the display
	void renderDisplay(double elapsedTime);

	// Displays an image on the screen (unused currently)
	void setDisplayImage(const char* filename);

	// Loads an image to be a background texture
	void setBackgroundImage(const char* filename);

	// Sets the BPM for visualization of beat timing
	void setBPM(double tempo) {
		omega = tempo * M_PI / 30;
	}
	
	// Generates a sequence of lines to be overlaid for frequency analysis
	void createGridOverlay(int fs, int N);

	// Takes in a vector of FFT magnitudes and pushes them to the right side of the display
	void setPixelColorArray(vector<double>& magnitude);

	// Returns the width of the window
	int width() const { return windowWidth; }
	 
	// Returns the height of the window
	int height() const { return windowHeight; }
};
