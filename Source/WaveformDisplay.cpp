/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0)
                          
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

  audioThumb.addChangeListener(this);

  addAndMakeVisible(blueButton);
  addAndMakeVisible(pinkButton);
  addAndMakeVisible(redButton);
  addAndMakeVisible(purpleButton);

  blueButton.addListener(this);
  pinkButton.addListener(this);
  redButton.addListener(this);
  purpleButton.addListener(this);


  color = juce::Colours::turquoise;
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(juce::Colours::black);
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (color);
    if(fileLoaded) //draw waveformDisplay thumbnail if file is loaded
    {
      audioThumb.drawChannel(g, 
        getLocalBounds(), 
        0, 
        audioThumb.getTotalLength(), 
        0, 
        1.0f
      );
      g.setColour(Colours::lightgreen); //this is where color of waveform is set
      g.drawRect(position * getWidth(), 0, getWidth() / 80, getHeight());
    }
    else 
    {
      g.setFont (20.0f);
      g.drawText ("File not loaded...", getLocalBounds(),
                  Justification::centred, true);   // draw some placeholder text

    }
    blueButton.setColour(TextButton::buttonColourId, juce::Colour (1,30,254));
    pinkButton.setColour(TextButton::buttonColourId, juce::Colour (240,0,255));
    redButton.setColour(TextButton::buttonColourId, juce::Colour (254,0,0));
    purpleButton.setColour(TextButton::buttonColourId, juce::Colour (125,18,255));
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double w = getWidth() / 4;
    blueButton.setBounds(0, 0, getWidth() /4, getHeight() / 6);
    pinkButton.setBounds(w, 0, getWidth() /4, getHeight() / 6);
    redButton.setBounds(w * 2, 0, getWidth() /4, getHeight() / 6);
    purpleButton.setBounds(w * 3, 0, getWidth() /4, getHeight() / 6);

}

void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  if (fileLoaded)
  {
    std::cout << "wfd: loaded! " << std::endl;
    repaint(); 
  }
  else {
    std::cout << "wfd: not loaded! " << std::endl;
  }

}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;

    repaint();

}

void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position)
  {
    position = pos;
    repaint();
  } 
}

//written without assistance
void WaveformDisplay::buttonClicked (Button * button)
{
  if (button == &blueButton)
  {
    color = juce::Colour 	(1,30,254);
    repaint();
  }  
    if (button == &pinkButton)
  {
    color = juce::Colour (240,0,255);
    repaint();
  } 
    if (button == &redButton)
  {
    color = juce::Colour (254,0,0);
    repaint();
  } 
    if (button == &purpleButton)
  {
    color = juce::Colour 	(125,18,255);
    repaint();
  } 
}
//




