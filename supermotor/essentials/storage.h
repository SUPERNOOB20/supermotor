#ifndef STORAGE_HEADER_FILE
#define STORAGE_HEADER_FILE

// At first I tried to abstract https://wiki.libsdl.org/SDL3/SDL_Storage features, but then quickly realised it's too complex, so here comes my own, less robust system...
// This is not async and WILL block your main thread and WON'T be compatible with a good number of platforms. Consider yourself warned.

#define DEVELOPER_NAME "SUPERNOOB_Studios"              //  <--- Name of the author here (person, company, studio, whatever it might be).
#define GAME_NAME "Painting_Test_Game"                          //   <--- Your videogame's name here.


namespace supermotor
{

namespace storage
{

void* loadedData;


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
    SDL_Storage* user = SDL_OpenUserStorage(DEVELOPER_NAME, GAME_NAME, 0);
    if (user == NULL) {
        handleException(__LINE__);
    }
    while (!SDL_StorageReady(user)) {
        SDL_Delay(1);
    }

    Uint64 saveLen = 0;
    if (SDL_GetStorageFileSize(user, savefile, &saveLen) && saveLen > 0) {

        loadedData = SDL_malloc(saveLen);        // Your loaded data will go here!
        if (!SDL_ReadStorageFile(user, savefile, loadedData, saveLen)) {
            handleException(__LINE__);
        }

    } else {

        handleException(__LINE__);
        SDL_Quit();
        exit(1);    // Exit with error :c
    }


    SDL_CloseStorage(user);
    return loadedData;
}



void WriteSave(const char* savefile)
{
    SDL_Storage* user = SDL_OpenUserStorage(DEVELOPER_NAME, GAME_NAME, 0);
    if (user == NULL) {
        handleException(__LINE__);
    }
    while (!SDL_StorageReady(user)) {
        SDL_Delay(1);
    }

    extern void* savedData;      // Put your data to be saved HERE (  with the proper (void*) and malloc()  ).
    extern Uint64 saveLen;
    if (!SDL_WriteStorageFile(user, savefile, savedData, saveLen)) {
        handleException(__LINE__);
    }

    SDL_CloseStorage(user);
}


}
}

#endif
