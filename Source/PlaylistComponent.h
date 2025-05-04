/*
  ==============================================================================

    PlaylistComponent.h
    Created: 29 Jul 2024 6:15:25pm
    Author:  Emma Bass

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                            public TableListBoxModel,
                            public Button::Listener,
                            public Slider::Listener,
                            public FileDragAndDropTarget
{
public:
    PlaylistComponent(DJAudioPlayer* player,
                      AudioFormatManager & formatManagerToUse);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;
    
    void paintRowBackground (Graphics &,
                             int rowNumber,
                             int width,
                             int height, 
                             bool rowIsSelected) override;
    
    void paintCell (Graphics &,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;

    Component* refreshComponentForCell (int rowNumber,
                                  int columnId, 
                                  bool isRowSelected,
                                  Component *existingComponentToUpdate) override;

    /** implement Button::Listener for play, stop, load and delete buttons*/
    void buttonClicked (Button *) override;
    /** implement Slider::Listener for scrubbing slider*/
    void sliderValueChanged(Slider *) override;

    /**calculate total minutes and seconds of loaded audioURL*/
    juce::String duration(URL audioURL);
    
    /**delete track based on id of row of selected delete buttonl*/
    void del(int id);
    
    /**select files to create Track objects and push to tracks vector*/
    void loadTracks();

    /** implement Row::Listener to have selected row be index number of Track in tracks to load to player*/
    void selectedRowsChanged (int lastRowSelected) override;
    
    /**Callback to check whether playlistComponent is interested in the set of files being offered*/
    bool isInterestedInFileDrag (const StringArray &files) override;

    /**convert string array of files to Track Object of single file dropped and then push to tracks vector*/
    void filesDropped (const StringArray &files, int x, int y) override; 

    
    


private:

    TableListBox tableComponent;

    /** vector to save Track Objects*/
    std::vector<Track> tracks;

    Slider position;
    ImageButton play{"PLAY"};
    ImageButton stop{"STOP"};
    ImageButton load{"LOAD"};

    juce::FileChooser fChooser{"Select a file..."};
    
    /**create DJAudioPlayer to play track from tracks vector*/
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
