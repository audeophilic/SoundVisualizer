#include "Display.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "PixelColors.h"
using namespace std;

Display::~Display() {
	if (window) SDL_DestroyWindow(window);
	if (windowSurface) SDL_FreeSurface(windowSurface);
	if (imageSurface) SDL_FreeSurface(imageSurface);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (texture) SDL_DestroyTexture(texture);
	if (imagetexture) SDL_DestroyTexture(imagetexture);
	TTF_Quit();
	SDL_Quit();
}

void Display::init() {
	//Init the display
	if (SDL_Init(SDL_INIT_VIDEO) < 0) throw DispErrorType::ERR_INIT_VIDEO;

	//Load a font for labeling
	TTF_Init();
	font = TTF_OpenFont("./resources/LemonMilk.otf", 100); //this opens a font style and sets a size
	if (!font) throw DispErrorType::ERR_INIT_FONT;
}

void Display::createWindow(const char* title, int pos_x, int pos_y, int w, int h, uint32_t flags) {
	windowWidth = w;
	windowHeight = h;

	window = SDL_CreateWindow(
		title,
		pos_x, pos_y,
		w, h,
		flags);

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		w, h);

	if (!window) throw DispErrorType::ERR_CREATE_WINDOW;
	if (!renderer) throw DispErrorType::ERR_CREATE_RENDERER;
	if (!texture) throw DispErrorType::ERR_CREATE_TEXTURE;


	pixelArray.resize(w * h * 4);
	magnitudeQueue = deque<double>(w*h, 0);

	//Set blend modes
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

}

void Display::setDisplayImage(const char* filename) {
	imageSurface = IMG_Load(filename);
	if (!imageSurface) throw DispErrorType::ERR_LOAD_IMAGE;

	if (imagetexture) SDL_DestroyTexture(imagetexture);
	imagetexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	if (!imagetexture) throw DispErrorType::ERR_CREATE_TEXTURE;

	SDL_SetTextureBlendMode(imagetexture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, imagetexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Display::createGridOverlay(int fs, int N) {
	
	//The frequency of A0
	const double f_base = 27.5;
	double line_frequency = f_base;
	double f_res = (double)fs / (double)N;

	int delta = 0;
	unsigned char counter = 0;
	do {
		
		delta = line_frequency/f_res;

		// Create the string to display on the line
		string label = "A";
		label.push_back('0' + counter);

		std::ostringstream ss;
		ss << fixed << setprecision(1) << line_frequency;
		string freq = ss.str();

		label = label + " (" + freq + " Hz)";

		gridLines.push_back({ label, windowHeight - delta });

		line_frequency *= 2;
		++counter;
	} while (line_frequency < fs/2);
}

void Display::renderDisplay(double elapsedTime) {

	//A rectangle containing a background image
	int w = 400;
	int h = 400;
	SDL_Rect image_rect = { 0, 0, w, h };

	//A slightly transparent color for labels and lines
	SDL_Color gridColor = { 255, 255, 255, 50 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color


	//Modulate the size of the image
	double factor = max(1.0,1 - 0.05*sin(omega * elapsedTime));
	image_rect.w = (int)((double)w * factor);
	image_rect.h = (int)((double)h * factor);
	image_rect.x = (windowWidth - image_rect.w) / 2;
	image_rect.y = (windowHeight - image_rect.h) / 2;

	//Set the background black
	SDL_Rect rect = { 0, 0, windowWidth, windowHeight };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	//Render bg image
	SDL_RenderCopy(renderer, imagetexture, nullptr, &image_rect);

	//Render texture
	SDL_UpdateTexture
	(
		texture,
		NULL,
		pixelArray.data(),
		windowWidth * 4
	);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	//Render Grid Lines
	SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
	for (auto& line : gridLines) {
		{
			SDL_RenderDrawLine(renderer, 0, line.y, windowWidth, line.y);

			SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, line.frequency.c_str(), gridColor); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

			SDL_Rect Message_rect;
			Message_rect.x = 20;
			Message_rect.y = line.y;
			Message_rect.w = 8 * line.frequency.size();
			Message_rect.h = 10;

			SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

			//Don't forget to free your surface and texture
			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(Message);
		}
	}

	SDL_RenderPresent(renderer);
}

void Display::setBackgroundImage(const char* filename) {

	// Try loading the image
	imageSurface = IMG_Load(filename);
	if (!imageSurface) throw DispErrorType::ERR_LOAD_IMAGE;

	// If there was already an image texture, delete it before loading this one
	if (imagetexture) SDL_DestroyTexture(imagetexture);

	// Try to create a texture from this image
	imagetexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	if (!imagetexture) throw DispErrorType::ERR_CREATE_TEXTURE;

	SDL_SetTextureBlendMode(imagetexture, SDL_BLENDMODE_BLEND);
}

void Display::setPixelColorArray(vector<double>& magnitude) {
	auto magBegin = magnitude.begin();

	for (int i = 0; i < 4; ++i) {
		pixelArray.erase(pixelArray.begin());
	}
	for (int i = 0; i < 4; ++i) {
		pixelArray.push_back(0);
	}
	
	auto iter = magnitude.begin();
	for (int i = pixelArray.size() - 4; i >= 0; i -= windowWidth*4) {
		unsigned char* pixel = &pixelArray[i];
		size_t colorindex = (size_t)std::min(((*iter) * 2), 764.0);
		size_t val = ColorCycle[colorindex];
		pixel[0] = val & 0xff;			//Blue
		pixel[1] = (val >> 8) & 0xff;	//Green
		pixel[2] = (val >> 16) & 0xff;	//Red
		pixel[3] = (val >> 24) & 0xff;	//Alpha
		++iter;
	}
}