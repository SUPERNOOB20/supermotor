#ifndef STORAGE_HEADER_FILE
#define STORAGE_HEADER_FILE

// At first I tried to abstract https://wiki.libsdl.org/SDL3/SDL_Storage features, but then quickly realised it's too complex, so here comes my own, less robust system...
// This is not async and WILL block your main thread and WON'T be compatible with a good number of platforms. Consider yourself warned.

// Some credits here...
// Mr. Hank     -   https://www.youtube.com/watch?v=16NXp7c53OQ
// w3           -   https://www.w3schools.com/cpp/ref_fstream_fstream.asp
// siliz4       - https://siliz4.github.io/guides/tutorials/2020/05/21/guide-on-binary-files-cpp.html
//      "In order to write the data in the file, it must be casted (transformed) into an array of characters" (thanks for that useful info! I was trying to save and load void*... ahahaha ":3)
// jahhaj       - https://stackoverflow.com/a/11919940
//      ^ nvm, ditch the char*, we'll trying reading and writing raw data instead :3
// istream::read   --->  https://en.cppreference.com/cpp/io/basic_istream/read
// ostream::write  --->  https://en.cppreference.com/cpp/io/basic_ostream/write





//#define DEVELOPER_NAME "SUPERNOOB_Studios"                       //  <--- Name of the author here (person, company, studio, whatever it might be).
//#define GAME_NAME "Painting_Test_Game"                          //   <--- Your videogame's name here.


#include <SDL3/SDL.h>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace supermotor
{

namespace storage
{




// Handles SDL exceptions.
// The reason why I made a function out of it is because
// I might even further overload this function in the future to allow logging... or make a logger.h entirely e.e
void handleException(){
    SDL_GetError();
}

void handleException(int line){
    SDL_Log("Exception occured at line %d.", line);
    handleException();
}



void* ReadSave(const char* savefile)
{

    void* loadedData;
    void* data_to_be_loaded;

    size_t savefile_size = std::filesystem::file_size(savefile);

    // std::fstream f(savefile);
    // f.open(savefile, ios::in | ios::binary);


    std::ifstream inputFileStream(savefile, std::ios::in|std::ios::binary);


    // Process data.
    // inputFileStream.read((char*) loadedData, (savefile_size / sizeof(char)));      // Casts our "binary void*" into "text" (and then it reads the file :3).
    const char* text_data;
    // inputFileStream >> text_data;
    std::istream::read(text_data, sizeof(text_data));
    loadedData = &text_data;     // (void*) ---> (std::string) conversion


    // Close the file.
    inputFileStream.close();



    loadedData = SDL_malloc(savefile_size);    // Your loaded data will go here!
    loadedData = data_to_be_loaded;    // text (char*)  --->  binary (void*)
    return loadedData;
}





void WriteSave(const char* savefile, void* savedData)       // Put your data to be saved HERE (  with the proper (void*) and malloc()  ).
{
    // FILE* my_opened_file = fopen(savefile,"w");
    // fputs(savedDatamy_opened_file);


    std::ofstream outputFileStream(savefile, std::ios::out|std::ios::binary);

    // Process data.
    // outputFileStream.write((char*) savedData, (size_t) ((sizeof(savedData)) / sizeof(char)));

    std::string* text_data = (std::string*)savedData;    // (void*) ---> (std::string) conversion
    outputFileStream << *text_data;


    // Close the file.
    outputFileStream.close();
}




}
}

#endif
