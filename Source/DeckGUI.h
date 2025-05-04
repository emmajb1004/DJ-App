/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI() override;

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    /**Callback to check whether deckGUI is interested in the set of files being offered*/
    bool isInterestedInFileDrag (const StringArray &files) override;
   
   /**convert string array of files to URL of single file dropped and then load to player*/
    void filesDropped (const StringArray &files, int x, int y) override; 

    /** repeatedly call get and set posiition for waveformDisplay playhead drawing*/
    void timerCallback() override; 


private:
    juce::FileChooser fChooser{"Select a file..."};
    ImageButton play{"PLAY ME"};

    ImageButton load{"LOAD"};
    ImageButton stop{"STOP"};
  
    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;
    Slider lowSlider;
    Slider highSlider;
    Slider bandSlider;
      
    Slider dampSlider; 
    Slider drySlider;
    Slider roomSlider;
    Slider wetSlider;
    Slider freezeSlider;
    Slider widthSlider;

    juce::Label playLabel;
    
    juce::Label volLabel;
    juce::Label speedLabel;
    juce::Label posLabel;
    juce::Label lowLabel;
    juce::Label highLabel;
    juce::Label bandLabel;

    juce::Label dampLabel;
    juce::Label dryLabel;
    juce::Label roomLabel;
    juce::Label wetLabel;
    juce::Label freezeLabel;
    juce::Label widthLabel;

    /**create WaveformDisplay for loaded files*/
    WaveformDisplay waveformDisplay;

    /**create DJAudioPlayer to play loaded files*/
    DJAudioPlayer* player; 
    juce::Image background;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
