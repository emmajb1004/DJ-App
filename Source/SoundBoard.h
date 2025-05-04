/*
  ==============================================================================

    SoundBoard.h
    Created: 28 Aug 2024 12:34:07pm
    Author:  Emma Bass

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class SoundBoard  : public juce::Component,
                    public Button::Listener,
                    public Slider::Listener
{
public:
    SoundBoard(DJAudioPlayer* player,
                      AudioFormatManager & formatManagerToUse);
    ~SoundBoard() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener for sounds to play*/
    void buttonClicked (Button *) override;

    /** implement Slider::Listener for volume of sounds*/
    void sliderValueChanged (Slider *slider) override;

private:
    /**create DJAudioPlayer to play sounds*/
    DJAudioPlayer* player;
    TextButton guitar{"GUITAR"};
    TextButton piano{"PIANO"};
    TextButton drum{"DRUM"};
    TextButton sing{"SING"};
    TextButton applause{"APPLAUSE"};
    TextButton car{"CAR"};
    TextButton dog{"DOG"};
    TextButton gameOver{"GAME OVER"};
    TextButton partyHorn{"PARTY HORN"};
    TextButton recordScratch{"RECORD SCRATCH"};
    TextButton toreador{"TOREADOR MARCH"};
    TextButton whistle{"WHISTLE"};
    
    Slider vol{"VOLUME"};
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundBoard)
};
