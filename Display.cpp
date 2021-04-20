#include "Display.h"
#include <cmath>
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
	SDL_Quit();
}

void Display::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) throw DispErrorType::ERR_INIT_VIDEO;
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

	do {
		
		delta = line_frequency/f_res;
		line_frequency *= 2;

		gridLines.push_back({ 0, windowWidth, windowHeight - delta, windowHeight - delta });
		//cout << "PUSHING k = " << delta << endl;

	} while (2 * delta < windowHeight);
}

void Display::renderDisplay(double elapsedTime) {

	//A rectangle containing a background image
	int w = 400;
	int h = 400;
	SDL_Rect image_rect = { 0, 0, w, h };

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

	//Create gray grid lines
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 30);
	for (auto& line : gridLines) {
		SDL_RenderDrawLine(renderer,
			line.x1, line.y1, line.x2, line.y2);
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