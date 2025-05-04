/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <string>
#include <iostream>

class DJAudioPlayer : public AudioSource {
  public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    /**create reader and transport souce for files loaded by user*/
    void loadURL(URL audioURL);
    /**change volume of song playing*/
    void setGain(double gain);
    /**change speed of song playing*/
    void setSpeed(double ratio);
    /** set the position of the song*/
    void setPosition(double posInSecs);
    /** set the position of the song realtive to slider value*/
    void setPositionRelative(double pos);
    
    /**set player to start playing song*/
    void start();
    /**set player to stop playing song*/
    void stop();

    /**set IIR filter coefficients frequency with slider value for high pass, bad pass, low pass*/
    void setIIRCoefficients(std::string slider, double frequency);

    /** get the realtive position of the playhead*/
    double getPositionRelative();
    
    /** get total length of song in seconds*/
    double songLength();

    /**set damp level for Reverb Filter */
    void damp(float damp);
    /**set dry level for Reverb Filter */
    void dry (float dry);
    /**set freeze level for Reverb Filter */
    void freeze(float freeze);
    /**set room size for Reverb Filter */
    void room(float size);
    /**set wet level for Reverb Filter */
    void wet (float wet);
    /**set width size for Reverb Filter */
    void width(float width);

    /**create reader and transport source for BinaryData files*/
    void loadBinary(std::unique_ptr<juce::MemoryInputStream> stream);

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    double sampleRate;

    /**create ResamplingAudioSource on transport source*/
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

    /**create ReverbAudioSource on resample source*/
    ReverbAudioSource reverbSource{&resampleSource, false};
    /**create IIRFilterAudioSource on reverb source*/
    IIRFilterAudioSource IIRFilter {&reverbSource, false};

    /**store reverb parameters*/
    Reverb::Parameters reverbParam;

};




