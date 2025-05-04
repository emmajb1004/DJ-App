/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   background2_png;
    const int            background2_pngSize = 286411;

    extern const char*   loading_png;
    const int            loading_pngSize = 20839;

    extern const char*   playlistLoad_png;
    const int            playlistLoad_pngSize = 7692;

    extern const char*   playlistPlay_png;
    const int            playlistPlay_pngSize = 5788;

    extern const char*   playlistStop_png;
    const int            playlistStop_pngSize = 4304;

    extern const char*   recordOff_png;
    const int            recordOff_pngSize = 46711;

    extern const char*   recordOn_png;
    const int            recordOn_pngSize = 154902;

    extern const char*   stop1_png;
    const int            stop1_pngSize = 47123;

    extern const char*   applause_mp3;
    const int            applause_mp3Size = 94403;

    extern const char*   car_mp3;
    const int            car_mp3Size = 15765;

    extern const char*   dog_mp3;
    const int            dog_mp3Size = 16797;

    extern const char*   drum_mp3;
    const int            drum_mp3Size = 21409;

    extern const char*   gameOver_mp3;
    const int            gameOver_mp3Size = 38364;

    extern const char*   guitar_mp3;
    const int            guitar_mp3Size = 85961;

    extern const char*   partyHorn_mp3;
    const int            partyHorn_mp3Size = 42201;

    extern const char*   piano_mp3;
    const int            piano_mp3Size = 69892;

    extern const char*   recordScratch_mp3;
    const int            recordScratch_mp3Size = 61119;

    extern const char*   sing_mp3;
    const int            sing_mp3Size = 32912;

    extern const char*   toreador_mp3;
    const int            toreador_mp3Size = 134816;

    extern const char*   whistle_mp3;
    const int            whistle_mp3Size = 16964;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 20;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
