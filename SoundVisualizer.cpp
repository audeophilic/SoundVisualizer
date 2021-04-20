#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <string>
#include <thread>
#include <cmath>
#include <queue>
#include "AudioFile.h"
#include "Display.h"
#include "Timer.h"
#include "AudioPlayer.h"
#include "MiniBPM.h"
#include "wavelet2d.h"
using namespace std;
using breakfastquay::MiniBPM;

// The size of a sample for FFT
#define N 16384

// The width of the window in pixels
#define WIDTH 1920

// The height of the window in pixels
#define HEIGHT 1080

// Main Helpers
void runVisualizer(string audio_filename);
void handleDisplayError(Display::DispErrorType ERR);
void handleAudioError(AudioPlayer::AudioErrorType ERR);
void handleAudioFileError(AudioFile<double>::AudioFileErrorType ERR);
void doublevec(vector<double>& vec);
void displayDWT(vector<double>& sample, int J);
void displayFFT(vector<double>& samples);

// Main takes care of Error Handling and filename input
int main() {
    string audio_filename;
    cout << " ________________________________ \n";
    cout << "|        Audio Visualizer        |\n";
    cout << "|  A group project for EECS 351  |\n";
    cout << "|________________________________|\n\n";
    cout << "Controls\n";
    cout << "\tPause: Space Bar\n";
    cout << "\tExit: ESCAPE Key\n\n";
    cout << "Please input the name of a valid .WAV file:\n# ";

    getline(cin, audio_filename);

    cout << "Loading...\n";

    try {
        runVisualizer(audio_filename);
    }
    // ERROR HANDLING FOR DISPLAY
    catch (Display::DispErrorType ERR) {
        handleDisplayError(ERR);
        SDL_Delay(5000);
        return 1;
    }
    // ERROR HANDLING FOR AUDIO
    catch (AudioPlayer::AudioErrorType ERR) {
        handleAudioError(ERR);
        SDL_Delay(5000);
        return 2;
    }
    catch (AudioFile<double>::AudioFileErrorType ERR) {
        handleAudioFileError(ERR);
        SDL_Delay(5000);
        return 3;
    }
    return 0;
}

void runVisualizer(string audio_filename) {
    // Create a hamming window the length of the sample
    vector<double> hamming(N);
    for (int i = 0; i < hamming.size(); ++i) {
        hamming[i] = 0.54 - 0.46 * cos(2 * M_PI * i / N);
    }

    //SDL handler objects
    Display& disp = Display::getInstance();
    AudioPlayer& player = AudioPlayer::getInstance();

    // Load the audio into memory, perform BPM analysis on it
    AudioFile<double> audio;
    audio.load(audio_filename);
    MiniBPM tempo(audio.getSampleRate());
    tempo.setBeatsPerBar(4);
    tempo.setBPMRange(40, 200);
    double BPM = tempo.estimateTempoOfSamples(audio.samples[0].data(), audio.getNumSamplesPerChannel());
    
    // Start SDL audio handler object
    player.init(audio.getSampleRate(), audio.getNumChannels(), 2048);
    player.loadAudio(audio_filename.c_str());

    // Start SDL display handler object
    disp.init();
    disp.createWindow(
        "Sound Visualizer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);
    disp.createGridOverlay(audio.getSampleRate(), N);
    disp.setBackgroundImage("./resources/background.png");
    disp.setBPM(BPM);

    // A place to store events
    SDL_Event ev;
    bool quitProgram = false;

    // Program Loop
    bool paused = false;
    Timer frametimer;
    frametimer.start();
    player.playAudio();
    do {
        // Get events in event queue, do things with them
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                quitProgram = true;
                break;
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                case SDLK_SPACE:
                    paused = !paused;
                    if (paused) {
                        player.pauseAudio();
                        frametimer.pause();
                    }
                    else {
                        player.resumeAudio();
                        frametimer.resume();
                        //cout << "PAUSED FOR " << frametimer.pauseduration() << endl;
                    }
                    break;
                case SDLK_ESCAPE:
                    quitProgram = true; //ESCAPE TO CLOSE PROGRAM
                    break;

                }
            }
        }

        // If not paused, do things
        if (!paused) {
            //For storing the output of FFT
            vector<double> sample;
            sample.reserve(N);

            // Take an audio sample up to this current time
            double elap = frametimer.elapsed();
            int frameIndex = (uint32_t)floor(elap * (double)audio.getSampleRate());
            int counter = 0;
            for (int i = frameIndex - N/2; i < frameIndex + N/2; ++i) {
                if (i >= 0 && i < audio.getNumSamplesPerChannel()) sample.push_back(audio.samples[0][i]*hamming[counter]);
                else sample.push_back(0);
                ++counter;

            }
            if (frameIndex > audio.getNumSamplesPerChannel()) {
                cout << "Sound Visualization has finished. Program will now exit.\n";
                SDL_Delay(2000);
                quitProgram = true;
            }
            
            // Calculate and display this sample's FFT
            displayFFT(sample);
            
            // Update the display
            disp.renderDisplay(elap);
        }
    } while (!quitProgram);
    
}

//Error Handling
void handleAudioError(AudioPlayer::AudioErrorType ERR) {
    switch (ERR) {
    case AudioPlayer::AudioErrorType::ERR_INIT_AUDIO:
        cerr << "Error Initializing Audio: ";
        break;
    case AudioPlayer::AudioErrorType::ERR_OPEN_AUDIO:
        cerr << "Error Opening Audio: ";
        break;
    case AudioPlayer::AudioErrorType::ERR_LOAD_AUDIO:
        cerr << "Error Loading Audio: ";
        break;
    }
    cout << SDL_GetError() << endl;
}
void handleDisplayError(Display::DispErrorType ERR) {
    switch (ERR) {
    case Display::DispErrorType::ERR_INIT_VIDEO:
        cerr << "Error Initializing Video: ";
        break;
    case Display::DispErrorType::ERR_CREATE_WINDOW:
        cerr << "Error Creating Window: ";
        break;
    case Display::DispErrorType::ERR_LOAD_IMAGE:
        cerr << "Error Loading Image: ";
        break;
    case Display::DispErrorType::ERR_CREATE_RENDERER:
        cerr << "Error Creating Renderer: ";
        break;
    case Display::DispErrorType::ERR_CREATE_TEXTURE:
        cerr << "Error Creating Texture: ";
        break;
    case Display::DispErrorType::ERR_INIT_FONT:
        cerr << "Error Loading Font: ";
    }
    cout << SDL_GetError() << endl;
}
void handleAudioFileError(AudioFile<double>::AudioFileErrorType ERR) {
    cerr << "Error Using AudioFile Methods: ";
    cerr << ERR.msg << endl;
}

// For DWT Method: Upsamples a vector by inserting the average of two existing indeces
void doublevec(vector<double>& vec) {
    int size = vec.size();
    vec.push_back(0);
    vector<double> temp;
    for (int i = 0; i < size; ++i) {
        temp.push_back(vec[i]);
        temp.push_back((vec[i] + vec[i + 1]) / 2);
    }
    swap(temp, vec);
}

// TODO: This is incredibly slow because of how we're rendering to the entire screen. Need either:
//      A. a more efficient method of creating a texture (Research better SDL texture generation methods)
//          OR
//      B. a better scheme for displaying the DWT on the screen.
// 
// THIS METHOD IS CURRENTLY UNUSED UNTIL WE CAN FIGURE OUT SOMETHING BETTER TO DO WITH IT.
void displayDWT(vector<double>& sample, int J) {
    vector<double> dwt_out, flag;
    vector<int> length;

    dwt(sample, J, "db5", dwt_out, flag, length);

    int M = dwt_out.size();

    vector<vector<double>> levels(J + 1);
    static const int gain[] = { 1, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 };

    //At level[i], the size should be N/2^i
    int counter = 0;
    for (int i = 0; i < levels.size(); ++i) {
        levels[i].reserve(M);
        int G = M / (2 << i);
        for (int n = 0; n < G; ++n) {
            levels[i].push_back(dwt_out[counter]);
            ++counter;
        }
    }
    while (counter < M) {
        levels[J].push_back(dwt_out[counter]);
        ++counter;
    }

    int levelID = 0;
    for (auto& vec : levels) {
        double max = 0;
        //Apply full wave rectification to levels and add gain factor
        for (auto& v : vec) {
            v = gain[levelID] * abs(v);
            if (v > max) max = v;
        }
        cout << "MAX GAIN FOR LEVEL " << levelID << ": " << max << endl;

        //Extend every level to be N size
        while (vec.size() < M) doublevec(vec);
        ++levelID;
    }
}

//Create an FFT to push to the right-most line of pixels in the screen
void displayFFT(vector<double>& samples) {
    Display& disp = Display::getInstance();
    vector<complex<double>> fft_out;
    fft_out.reserve(samples.size());
    int counter = 0;
    for (auto s : samples) fft_out.push_back(s);

    //Take the FFT;
    fft(fft_out, 1, fft_out.size());

    //Fill Samples vector with FFT magnitudes
    samples.clear();
    samples.reserve(fft_out.size());
    counter = 0;
    int maxindex = 0;
    for (auto& comp : fft_out) {
        if (counter == disp.height()) break;
        samples.push_back(abs(comp));
        ++counter;
    }

    //Push this to the right of the screen
    disp.setPixelColorArray(samples);
}