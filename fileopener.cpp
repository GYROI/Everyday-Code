#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#undef main
// Function to open a folder in the file explorer
void openFolder(const std::string& path) {
#ifdef _WIN32
    std::string command = "explorer \"" + path + "\"";
    system(command.c_str());
#elif __APPLE__
    std::string command = "open \"" + path + "\"";
    system(command.c_str());
#elif __linux__
    std::string command = "xdg-open \"" + path + "\"";
    system(command.c_str());
#else
    std::cerr << "Opening folder is not supported on this platform." << std::endl;
#endif
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Open a folder
    std::string folderPath = "D:\\APPS"; // Change this to your desired folder path
    openFolder(folderPath);

    // Quit SDL
    SDL_Quit();

    return 0;
}
