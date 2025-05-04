/*
  ==============================================================================

    SoundBoard.cpp
    Created: 28 Aug 2024 12:34:07pm
    Author:  Emma Bass

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundBoard.h"
//==============================================================================
SoundBoard::SoundBoard(DJAudioPlayer* _player,
                                    AudioFormatManager & formatManagerToUse) :
                                    player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(guitar);
    addAndMakeVisible(piano);
    addAndMakeVisible(drum);
    addAndMakeVisible(sing);
    addAndMakeVisible(applause);
    addAndMakeVisible(car);
    addAndMakeVisible(dog);
    addAndMakeVisible(gameOver);
    addAndMakeVisible(partyHorn);
    addAndMakeVisible(recordScratch);
    addAndMakeVisible(toreador);
    addAndMakeVisible(whistle);

    addAndMakeVisible(vol);

    guitar.addListener(this);
    piano.addListener(this);
    drum.addListener(this);
    sing.addListener(this);
    applause.addListener(this);
    car.addListener(this);
    dog.addListener(this);
    gameOver.addListener(this);
    partyHorn.addListener(this);
    recordScratch.addListener(this);
    toreador.addListener(this);
    whistle.addListener(this);

    vol.addListener(this);
    vol.setSliderStyle(Slider::SliderStyle::LinearVertical);
    vol.setTextBoxStyle(juce::Slider::TextBoxAbove, false, vol.getTextBoxWidth(), vol.getTextBoxHeight());
    vol.setNumDecimalPlacesToDisplay(3);

    vol.setRange(0.1, 1.0);
}

SoundBoard::~SoundBoard()
{
}

void SoundBoard::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(Colour (1,32,78)); // set background color

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("SoundBoard", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    guitar.setColour(juce::TextButton::buttonColourId,juce::Colour (56, 118, 84));
    piano.setColour(juce::TextButton::buttonColourId,juce::Colour (2, 131, 145));
    drum.setColour(juce::TextButton::buttonColourId,juce::Colour (191, 167, 132));
    sing.setColour(juce::TextButton::buttonColourId,juce::Colour (250, 169, 104));
    applause.setColour(juce::TextButton::buttonColourId,juce::Colour (241, 165, 18));
    car.setColour(juce::TextButton::buttonColourId,juce::Colour (140, 0, 39));

    dog.setColour(juce::TextButton::buttonColourId,juce::Colour (140, 0, 39));
    gameOver.setColour(juce::TextButton::buttonColourId,juce::Colour (241, 165, 18));
    partyHorn.setColour(juce::TextButton::buttonColourId,juce::Colour (250, 169, 104));
    recordScratch.setColour(juce::TextButton::buttonColourId,juce::Colour (191, 167, 132));
    toreador.setColour(juce::TextButton::buttonColourId,juce::Colour (2, 131, 145));
    whistle.setColour(juce::TextButton::buttonColourId,juce::Colour (56, 118, 84));
}

void SoundBoard::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    int rowW = getWidth() / 13;
    vol.setBounds(0, 0, rowW, getHeight());
    guitar.setBounds(rowW, 0, rowW * 2, getHeight() / 2);
    piano.setBounds(rowW * 3, 0, rowW * 2, getHeight() / 2);
    drum.setBounds(rowW * 5, 0, rowW * 2, getHeight() / 2);
    sing.setBounds(rowW * 7, 0, rowW * 2, getHeight() / 2);
    applause.setBounds(rowW * 9, 0, rowW * 2, getHeight() / 2);
    car.setBounds(rowW * 11, 0, rowW * 2, getHeight() / 2);
    dog.setBounds(rowW, getHeight() / 2, rowW * 2, getHeight() / 2);
    gameOver.setBounds(rowW * 3, getHeight() / 2, rowW * 2, getHeight() / 2);
    partyHorn.setBounds(rowW * 5, getHeight() / 2, rowW * 2, getHeight() / 2);
    recordScratch.setBounds(rowW * 7, getHeight() / 2, rowW * 2, getHeight() / 2);
    toreador.setBounds(rowW * 9, getHeight() / 2, rowW * 2, getHeight() / 2);
    whistle.setBounds(rowW * 11, getHeight() / 2, rowW * 2, getHeight() / 2);
}

//written without assistance
void SoundBoard::buttonClicked(Button* button) 
//call loadBinary function from DJAudioPlayer with correct sound file from BinaryData
{
  if (button == &guitar)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::guitar_mp3, BinaryData::guitar_mp3Size, false));
    player->start();
  }
  if (button == &piano)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::piano_mp3, BinaryData::piano_mp3Size, false));
    player->start();
  }
  if (button == &drum)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::drum_mp3, BinaryData::drum_mp3Size, false));
    player->start(); 
  }
  if (button == &sing)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::sing_mp3, BinaryData::sing_mp3Size, false));
    player->start(); 
  }
  if (button == &applause)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::applause_mp3, BinaryData::applause_mp3Size, false));
    player->start(); 
  }
  if (button == &car)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::car_mp3, BinaryData::car_mp3Size, false));
    player->start(); 
  }
  if (button == &dog)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::dog_mp3, BinaryData::dog_mp3Size, false));
    player->start(); 
  }
  if (button == &gameOver)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::gameOver_mp3, BinaryData::gameOver_mp3Size, false));
    player->start(); 
  }
  if (button == &partyHorn)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::partyHorn_mp3, BinaryData::partyHorn_mp3Size, false));
    player->start(); 
  }
  if (button == &recordScratch)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::recordScratch_mp3, BinaryData::recordScratch_mp3Size, false));
    player->start(); 
  }
  if (button == &toreador)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::toreador_mp3, BinaryData::toreador_mp3Size, false));
    player->start(); 
  }
  if (button == &whistle)
  {
    player->loadBinary(std::make_unique<MemoryInputStream>(BinaryData::whistle_mp3, BinaryData::whistle_mp3Size, false));
    player->start(); 
  }
}
//

void SoundBoard::sliderValueChanged (Slider *slider)
{
  player->setGain(slider->getValue()); //set Volume for sounds
}