/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 29 Jul 2024 6:15:25pm
    Author:  Emma Bass

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player,
                                    AudioFormatManager & formatManagerToUse) :
                                    player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(play);
    addAndMakeVisible(stop);
    addAndMakeVisible(load);
    addAndMakeVisible(position);

    play.addListener(this);
    stop.addListener(this);
    position.addListener(this);
    load.addListener(this);
    
    //create column headers
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("Duration", 2, 100);
    tableComponent.getHeader().addColumn("Delete", 3, 100);

    tableComponent.getHeader().setColour(TableHeaderComponent::backgroundColourId, juce::Colour 	(186,225,255)); //background color of playlist header

    tableComponent.setModel(this); 
    addAndMakeVisible(tableComponent);
    
    position.setRange(0.0, 1.0);
    position.setNumDecimalPlacesToDisplay(3);

//image for load button
  load.setImages(true, true, false, 
                  ImageCache::getFromMemory(BinaryData::playlistLoad_png, 
                                              BinaryData::playlistLoad_pngSize), 
                  1.0f, Colours::transparentWhite, 
                  ImageCache::getFromMemory(BinaryData::playlistLoad_png, 
                                              BinaryData::playlistLoad_pngSize),
                  1.0f, Colours::transparentWhite, 
                  ImageCache::getFromMemory(BinaryData::playlistLoad_png, 
                                              BinaryData::playlistLoad_pngSize), 
                  1.0f, Colours::transparentWhite);

  //image for play button
  play.setImages(true, true, false, 
                  ImageCache::getFromMemory(BinaryData::playlistPlay_png, 
                                              BinaryData::playlistPlay_pngSize), 
                  1.0f, Colours::transparentWhite, 
                  ImageCache::getFromMemory(BinaryData::playlistPlay_png, 
                                              BinaryData::playlistPlay_pngSize),
                  1.0f, Colours::transparentWhite, 
                  ImageCache::getFromMemory(BinaryData::playlistPlay_png, 
                                              BinaryData::playlistPlay_pngSize), 
                  1.0f, Colours::transparentWhite);
  
  //image for stop button
  stop.setImages(true, true, false, 
                ImageCache::getFromMemory(BinaryData::playlistStop_png, 
                                            BinaryData::playlistStop_pngSize), 
                1.0f, Colours::transparentWhite, 
                ImageCache::getFromMemory(BinaryData::playlistStop_png, 
                                            BinaryData::playlistStop_pngSize),
                1.0f, Colours::transparentWhite, 
                ImageCache::getFromMemory(BinaryData::playlistStop_png, 
                                            BinaryData::playlistStop_pngSize), 
                1.0f, Colours::transparentWhite);

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(juce::Colour (196,155,223)); //background color
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText (" ", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() / 8;
    double rowW = getWidth() / 8;
    play.setBounds(0,0,rowW, rowH);
    stop.setBounds(rowW + rowW * 0.05,0,rowW, rowH); 
    position.setBounds(rowW * 2.5,0,rowW * 4, rowH); 
    load.setBounds(rowW * 7.05,0,rowW, rowH);   
    tableComponent.setBounds(0,rowH,getWidth(), rowH * 7);
}

int PlaylistComponent::getNumRows()
{
  return tracks.size();
}


void PlaylistComponent::paintRowBackground (Graphics & g,
                          int rowNumber,
                          int width,
                          int height, 
                          bool rowIsSelected)
{
  if (rowIsSelected)
  {
    g.fillAll(juce::Colour 	(184,219,211));
    //
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (18.0f));
  } else{
    g.fillAll(juce::Colour 	(196,155,223));
    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (14.0f));   
  }
}

void PlaylistComponent::paintCell (Graphics & g,
                int rowNumber,
                int columnId,
                int width,
                int height,
                bool rowIsSelected)
{
  if (columnId == 1) //write tracknames to first column
  {
          g.drawText(tracks[rowNumber].trackName, 2, 1,
          width - 4, height,
          Justification::centredLeft, true);
  }
  if (columnId == 2) //write duration of tracks to second column
  {
          g.drawText(tracks[rowNumber].duration, 2, 1,
          width - 4, height,
          Justification::centredLeft, true);
  }
}

Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                              int columnId, 
                              bool isRowSelected,
                              Component *existingComponentToUpdate)
{

  if (columnId == 3) //create delete button
  {
    if (existingComponentToUpdate == nullptr)
    {
      TextButton* btn = new TextButton("Delete");
      btn->setColour(TextButton::buttonColourId, juce::Colour (255,179,186));
      String id{std::to_string(rowNumber)}; //convert row number to string for set id argument
      btn->setComponentID(id);

      btn->addListener(this);
      existingComponentToUpdate = btn;
    }
  }
  return existingComponentToUpdate;
}

void PlaylistComponent::loadTracks()
{
         auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles; //add file chooser
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            File chosenFile = chooser.getResult();
            if (chosenFile.exists()){
              //written without assistance
                Track newTrack{chosenFile,
                                chosenFile.getFileNameWithoutExtension(),
                                URL{chosenFile},
                                duration(URL{chooser.getResult()}) //create Track object from loaded file
                              };
                tracks.push_back(newTrack); //push Track object to tracks vector
                tableComponent.updateContent(); // update table component so trackname, duration written to rows
                //
            }
        });
}

//written with partial assistance
juce::String PlaylistComponent::duration(URL audioURL)
{
  player->loadURL(audioURL);
  int seconds, minutes;
  seconds = player->songLength();
  minutes = seconds / 60;
  seconds = seconds % 60;
  juce::String minSecs;
  minSecs = std::to_string(minutes) + ":" + std::to_string(seconds);
  return minSecs; 

}

void PlaylistComponent::del(int id)
{
  tracks.erase(tracks.begin() + id);
}
//

void PlaylistComponent::buttonClicked(Button* button)
{
  std::cout << "PlaylistComponent::buttonClicked " << std::endl;
  if (button->getButtonText() == "Delete")
  {
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout << "Delete " << tracks[id].trackName << std::endl; 
    del(id); //delete entry in track that is the id (row) of delete button 
    tableComponent.updateContent();
  }
  if (button == &load)
  {
    loadTracks();
  }
  if (button == &play)
  {
    player->start();
  }
  if (button == &stop)
  {
    player->stop();
  }
}

void PlaylistComponent::sliderValueChanged(Slider *slider)
{
  
  if (slider == &position)
  {
      player->setPositionRelative(slider->getValue()); //change position in song
  }
}

//written without assistance
void PlaylistComponent::selectedRowsChanged (int lastRowSelected)
{
  if (lastRowSelected >= 0) //don't try to load if tracks index is -1 aka doesn't exist
  {
    lastRowSelected = tableComponent.getSelectedRow();
    player->loadURL(tracks[lastRowSelected].fileURL);
  }
}
//

bool PlaylistComponent::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "PlaylistComponent::isInterestedInFileDrag" << std::endl;
  return true; 
}

void PlaylistComponent::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1) //drag and drop that pushes files to tracks vector
  {
    File chosenFile = File{files[0]}; 
    if (chosenFile.exists()){
      //written without assistance
        Track newTrack{chosenFile,
                        chosenFile.getFileNameWithoutExtension(),
                        URL{chosenFile},
                        duration(URL{chosenFile})
                      };
        tracks.push_back(newTrack);
        tableComponent.updateContent();
        //
  }
}
}