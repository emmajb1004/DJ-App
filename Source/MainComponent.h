/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "SoundBoard.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
     
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    /**instantiate player for deckGUI 1*/
    DJAudioPlayer player1{formatManager};
    /**instantiate deckGUI 1*/
    DeckGUI deckGUI1{&player1, formatManager, thumbCache}; 

    /**instantiate player for deckGUI 2*/
    DJAudioPlayer player2{formatManager};
    /**instantiate deckGUI 2*/
    DeckGUI deckGUI2{&player2, formatManager, thumbCache}; 

    MixerAudioSource mixerSource; 

    /**instantiate player for playlistComponent*/
    DJAudioPlayer playerP1{formatManager};
    /**instantiate playlistComponent*/
    PlaylistComponent playlistComponent{&playerP1,
                                        formatManager};

    /**instantiate player for soundBoard*/
    DJAudioPlayer playerSB1{formatManager};
    /**instantiate soundBoard*/
    SoundBoard soundBoard{&playerSB1,
                                        formatManager};
                                        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
