/*
==============================================================================

DJAudioPlayer.cpp
Created: 13 Mar 2020 4:22:22pm
Author:  matthew

==============================================================================
*/

#include "DJAudioPlayer.h"
#include <string>
#include <iostream>

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) 
: formatManager(_formatManager)
{
    //written with partial assistance
    reverbParam.roomSize = 0.5f;
    reverbParam.damping = 0.5f;
    reverbParam.wetLevel = 0.33f;
    reverbParam.dryLevel = 0.4f;
    reverbParam.freezeMode = 0.0f;
    reverbParam.width = 1.0f;
    reverbSource.setParameters(reverbParam); //set starting reverb parameters with values in JUCE documentaiton
    //
}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    IIRFilter.prepareToPlay(samplesPerBlockExpected, sampleRate);

    this->sampleRate = sampleRate; //save sample rate for IIR filters
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    IIRFilter.getNextAudioBlock(bufferToFill);

}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources(); 
    IIRFilter.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false)); //audioURL converted to Input Stream and passed to AudioFormatManager
    if (reader != nullptr) // good file!
    {       
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, 
true)); //audioFormatReaderSource created
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate); //audioFormatReaderSource passed to transportSource            
        readerSource.reset (newSource.release()); //pass local readerSource to class scope variable          
    }
}

//written with partial assistance
void DJAudioPlayer::loadBinary(std::unique_ptr<juce::MemoryInputStream> stream)
{
    auto* reader = formatManager.createReaderFor(std::move(stream));
    if (reader != nullptr) //good file
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true)); //audioFormatReaderSource created
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate); //audioFormatReaderSource passed to transportSource  
        readerSource.reset (newSource.release()); //pass local readerSource to class scope variable  
    }
}
//

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
   
}
void DJAudioPlayer::setSpeed(double ratio)
{
  if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
     if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}


void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
  transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

//written with partial assistance
void DJAudioPlayer::setIIRCoefficients(std::string slider, double frequency)
{
    if (slider == "lowSlider") //check for low Slider changed
        {
            IIRFilter.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, frequency));
        }
    if (slider == "highSlider") //check for high Slider changed
        {
            IIRFilter.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, frequency));
        }
    if (slider == "bandSlider") //check for band Slider changed
    {
        IIRFilter.setCoefficients(IIRCoefficients::makeBandPass(sampleRate, frequency));
    }
}
//

//written without assistance
double DJAudioPlayer::songLength()
{
    return transportSource.getLengthInSeconds();
}
//

//written with partial assistance
void DJAudioPlayer::damp(float damp)
{
    reverbParam.damping = damp;
    reverbSource.setParameters(reverbParam);
}
void DJAudioPlayer::dry (float dry)
{
    reverbParam.dryLevel = dry;
    reverbSource.setParameters(reverbParam);
}
void DJAudioPlayer::freeze(float freeze)
{
    reverbParam.freezeMode = freeze;
    reverbSource.setParameters(reverbParam);
}
void DJAudioPlayer::room(float size)
{
    reverbParam.roomSize = size;
    reverbSource.setParameters(reverbParam);
}
void DJAudioPlayer::wet (float wet)
{
    reverbParam.wetLevel = wet;
    reverbSource.setParameters(reverbParam);
}
void DJAudioPlayer::width(float width)
{
    reverbParam.width = width;
    reverbSource.setParameters(reverbParam);
}
//
