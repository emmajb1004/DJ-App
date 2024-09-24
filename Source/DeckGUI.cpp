/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(stop);
    addAndMakeVisible(load);
    addAndMakeVisible(play);
    playLabel.setText("TITLE", juce::dontSendNotification);
    playLabel.attachToComponent(&play, false);
    playLabel.setColour(juce::Label::textColourId, Colours::turquoise);
    playLabel.setFont (juce::Font (20.0f, juce::Font::bold));
    playLabel.setJustificationType (juce::Justification::centred);
    playLabel.setBorderSize (juce::BorderSize<int> (10));
 
    addAndMakeVisible(volSlider);
    addAndMakeVisible(volLabel);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&volSlider, true);
    volLabel.setColour(juce::Label::textColourId, Colours::turquoise);
    volSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, true);
    speedLabel.setColour(juce::Label::textColourId, Colours::turquoise);
    speedSlider.setNumDecimalPlacesToDisplay(3);
    
    addAndMakeVisible(posSlider);
    addAndMakeVisible(posLabel);
    posLabel.setText("Position", juce::dontSendNotification);
    posLabel.attachToComponent(&posSlider, true);
    posLabel.setColour(juce::Label::textColourId, Colours::turquoise);
    posSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(lowSlider);
    addAndMakeVisible(lowLabel);
    lowLabel.setText("Low Pass", juce::dontSendNotification);
    lowLabel.attachToComponent(&lowSlider, true);
    lowLabel.setColour(juce::Label::textColourId, Colours::violet);
    lowSlider.setNumDecimalPlacesToDisplay(3);
    
    addAndMakeVisible(highSlider);
    addAndMakeVisible(highLabel);
    highLabel.setText("High Pass", juce::dontSendNotification);
    highLabel.attachToComponent(&highSlider, true);
    highLabel.setColour(juce::Label::textColourId, Colours::violet);
    highSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(bandSlider);
    addAndMakeVisible(bandLabel);
    bandLabel.setText("Band Pass", juce::dontSendNotification);
    bandLabel.attachToComponent(&bandSlider, true);
    bandLabel.setColour(juce::Label::textColourId, Colours::violet);
    bandSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(roomSlider);
    addAndMakeVisible(roomLabel);
    roomLabel.setText("Room", juce::dontSendNotification);
    roomLabel.attachToComponent(&roomSlider, true);
    roomLabel.setColour(juce::Label::textColourId, Colours::deepskyblue);
    roomSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(dampSlider);
    addAndMakeVisible(dampLabel);
    dampLabel.setText("Damp", juce::dontSendNotification);
    dampLabel.attachToComponent(&dampSlider, true);
    dampLabel.setColour(juce::Label::textColourId, Colours::deepskyblue);
    dampSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(wetSlider);
    addAndMakeVisible(wetLabel);
    wetLabel.setText("Wet", juce::dontSendNotification);
    wetLabel.attachToComponent(&wetSlider, true);
    wetLabel.setColour(juce::Label::textColourId, Colours::deepskyblue);
    wetSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(drySlider);
    addAndMakeVisible(dryLabel);
    dryLabel.setText("Dry", juce::dontSendNotification);
    dryLabel.attachToComponent(&drySlider, true);
    dryLabel.setColour(juce::Label::textColourId, Colours::deepskyblue);
    drySlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(freezeSlider);
    addAndMakeVisible(freezeLabel);
    freezeLabel.setText("Freeze", juce::dontSendNotification);
    freezeLabel.attachToComponent(&freezeSlider, true);
    freezeLabel.setColour(juce::Label::textColourId, Colours::deepskyblue);
    freezeSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(widthSlider);
    addAndMakeVisible(widthLabel);
    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.attachToComponent(&widthSlider, true);
    widthLabel.setColour(juce::Label::textColourId, Colours::deepskyblue);
    widthSlider.setNumDecimalPlacesToDisplay(3);

    addAndMakeVisible(waveformDisplay);
    
    stop.addListener(this);
    load.addListener(this);
    play.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    lowSlider.addListener(this);
    highSlider.addListener(this);
    bandSlider.addListener(this);

    roomSlider.addListener(this);
    dampSlider.addListener(this);
    wetSlider.addListener(this);
    drySlider.addListener(this);
    freezeSlider.addListener(this);
    widthSlider.addListener(this);


    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    posSlider.setRange(0.0, 1.0);
    lowSlider.setRange(20.0, 10000.0);
    highSlider.setRange(500.0, 15000.0);
    bandSlider.setRange(20.0, 20000.0);

    roomSlider.setRange(0.0, 1.0);
    dampSlider.setRange(0.0, 1.0);
    wetSlider.setRange(0.0, 1.0);
    drySlider.setRange(0.0, 1.0);
    freezeSlider.setRange(0.0, 1.0);
    widthSlider.setRange(0.0, 1.0);

    startTimer(500);

    //written with partial assistance
    play.setImages(true, true, false, 
                ImageCache::getFromMemory(BinaryData::recordOff_png, 
                                            BinaryData::recordOff_pngSize), 
                1.0f, Colours::transparentWhite, 
                ImageCache::getFromMemory(BinaryData::recordOn_png, 
                                            BinaryData::recordOn_pngSize),
                1.0f, Colours::transparentWhite, 
                ImageCache::getFromMemory(BinaryData::recordOn_png, 
                                            BinaryData::recordOn_pngSize), 
                1.0f, Colours::transparentWhite);

    stop.setImages(true, true, false, 
                        ImageCache::getFromMemory(BinaryData::stop1_png, 
                                                    BinaryData::stop1_pngSize), 
                        1.0f, Colours::transparentWhite, 
                        ImageCache::getFromMemory(BinaryData::stop1_png, 
                                                    BinaryData::stop1_pngSize),
                        1.0f, Colours::transparentWhite, 
                        ImageCache::getFromMemory(BinaryData::stop1_png, 
                                                    BinaryData::stop1_pngSize), 
                        1.0f, Colours::transparentWhite);

    load.setImages(true, true, false, 
                        ImageCache::getFromMemory(BinaryData::loading_png, 
                                                    BinaryData::loading_pngSize), 
                        1.0f, Colours::transparentWhite, 
                        ImageCache::getFromMemory(BinaryData::loading_png, 
                                                    BinaryData::loading_pngSize),
                        1.0f, Colours::transparentWhite, 
                        ImageCache::getFromMemory(BinaryData::loading_png, 
                                                    BinaryData::loading_pngSize), 
                        1.0f, Colours::transparentWhite);
    //
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //make background image
    background = juce::ImageCache::getFromMemory(BinaryData::background2_png, BinaryData::background2_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    g.setColour (juce::Colour (253, 191, 224));
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 31; 
    double rowW = getWidth()/5;
    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 7);
    play.setBounds(getWidth() * 0.20, rowH * 10, getWidth() * 0.60, rowH * 8);
    stop.setBounds(getWidth() * 0.01, rowH * 13, getWidth() /6, rowH * 2); 
    load.setBounds(getWidth() * 0.82, rowH * 13, getWidth() / 6, rowH * 2);
    
    volSlider.setBounds(getWidth() * 0.15, rowH * 19, getWidth() * 0.75, rowH);
    posSlider.setBounds(getWidth() * 0.15, rowH * 20, getWidth() * 0.75, rowH);
    speedSlider.setBounds(getWidth() * 0.15, rowH * 21, getWidth() * 0.75, rowH);
    lowSlider.setBounds(getWidth() * 0.15, rowH * 22, getWidth()* 0.75, rowH);
    bandSlider.setBounds(getWidth() * 0.15, rowH * 23, getWidth()* 0.75, rowH);
    highSlider.setBounds(getWidth() * 0.15, rowH * 24, getWidth()* 0.75, rowH);

    roomSlider.setBounds(getWidth() * 0.15, rowH * 25, getWidth() * 0.75, rowH);
    dampSlider.setBounds(getWidth() * 0.15, rowH * 26, getWidth() * 0.75, rowH);
    wetSlider.setBounds(getWidth() * 0.15, rowH * 27, getWidth()* 0.75, rowH);
    drySlider.setBounds(getWidth() * 0.15, rowH * 28, getWidth()* 0.75, rowH);
    freezeSlider.setBounds(getWidth() * 0.15, rowH * 29, getWidth()* 0.75, rowH);
    widthSlider.setBounds(getWidth() * 0.15, rowH * 30, getWidth()* 0.75, rowH);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &play)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stop)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    if (button == &load)
    {
       auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles; //add file chooser
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            File chosenFile = chooser.getResult();
            if (chosenFile.exists()){
                player->loadURL(URL{chooser.getResult()}); //load URL of choosen file into player
                //written without assistance
                juce::String name = chosenFile.getFileNameWithoutExtension(); //get name file
                playLabel.setText(name.toUpperCase(), juce::dontSendNotification); //set label to file name saved
                playLabel.repaint();
                //
                waveformDisplay.loadURL(URL{chooser.getResult()}); //set waveform to current song
            }
        });
    }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    //written with partial assistance
    if (slider == &lowSlider)
    {
        player->setIIRCoefficients("lowSlider", slider->getValue());
    }

    if (slider == &highSlider)
    {
        player->setIIRCoefficients("highSlider", slider->getValue());
    }
        if (slider == &bandSlider)
    {
        player->setIIRCoefficients("bandSlider", slider->getValue());
    }

        if (slider == &roomSlider)
    {
        player->room(slider->getValue());
    }
    
    if (slider == &dampSlider)
    {
        player->damp(slider->getValue());
    }

    if (slider == &wetSlider)
    {
        player->wet(slider->getValue());
    }

    if (slider == &drySlider)
    {
        player->dry(slider->getValue());
    }
    if (slider == &freezeSlider)
    {
        player->freeze(slider->getValue());
    }

    if (slider == &widthSlider)
    {
        player->width(slider->getValue());
    }
    //
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


    

