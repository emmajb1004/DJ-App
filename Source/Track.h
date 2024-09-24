#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <string>
#include <iostream>


class Track 
{
public:
    Track(File _fileName,
            juce::String _trackName,
            URL _fileURL,
            juce::String _duration);
    
    File fileName;
    juce::String trackName;
    URL fileURL;
    juce::String duration;
}; //object to store track data from loaded in files
