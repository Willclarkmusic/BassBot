/*
  ==============================================================================

    LFO1Component.cpp
    Created: 21 Sep 2024 3:19:56pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFO1Component.h"

//==============================================================================
LFO1Component::LFO1Component()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

LFO1Component::~LFO1Component()
{
}

void LFO1Component::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("LFO1Component", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LFO1Component::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
