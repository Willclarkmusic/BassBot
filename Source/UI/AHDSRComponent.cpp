/*
  ==============================================================================

    AHDSRComponent.cpp
    Created: 6 Sep 2024 11:33:20pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AHDSRComponent.h"

//==============================================================================
AHDSRComponent::AHDSRComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID,
    juce::String holdID, juce::String decayID, juce::String sustainID, juce::String releaseID)
{
    attackKnob.createKnobWithLabel(apvts, attackID, "A");
    addAndMakeVisible(attackKnob);
    holdKnob.createKnobWithLabel(apvts, holdID, "A");
    addAndMakeVisible(holdKnob);
    decaykKnob.createKnobWithLabel(apvts, decayID, "D");
    addAndMakeVisible(decaykKnob);
    sustainKnob.createKnobWithLabel(apvts, sustainID, "S");
    addAndMakeVisible(sustainKnob);
    releaseKnob.createKnobWithLabel(apvts, releaseID, "R");
    addAndMakeVisible(releaseKnob);

}

AHDSRComponent::~AHDSRComponent()
{
}

void AHDSRComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void AHDSRComponent::resized()
{
    const auto padding = 5;

    attackKnob.setBoundsKnobWithLabel(padding, padding);
    holdKnob.setBoundsKnobWithLabel(attackKnob.getRight(), padding);
    decaykKnob.setBoundsKnobWithLabel(holdKnob.getRight(), padding);
    sustainKnob.setBoundsKnobWithLabel(decaykKnob.getRight(), padding);
    releaseKnob.setBoundsKnobWithLabel(sustainKnob.getRight(), padding);
}
