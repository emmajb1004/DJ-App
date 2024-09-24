/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener,
                           public Button::Listener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay() override;

    void paint (Graphics&) override;
    void resized() override;

    /**changeListener interface to receive changes as waveform is processed and drawn*/
    void changeListenerCallback (ChangeBroadcaster *source) override;

    /**turn URl of loaded file into input source of AudioThumbnail*/
    void loadURL(URL audioURL);

    /** set the relative position of the playhead and repaint if position has changed*/
    void setPositionRelative(double pos);

    /** implement Button::Listener to change color of waveform*/
    void buttonClicked (Button *) override;

private:
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;

    TextButton blueButton{"BLUE"};
    TextButton pinkButton{"PINK"};
    TextButton redButton{"RED"};
    TextButton purpleButton{"PURPLE"};

    juce::Colour color;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
