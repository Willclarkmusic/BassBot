/*
  ==============================================================================

    Reverb1Component.cpp
    Created: 24 Aug 2024 3:34:36pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Reverb1Component.h"

//==============================================================================
Reverb1Component::Reverb1Component(juce::AudioProcessorValueTreeState& apvts, juce::String sizeID, 
    juce::String dampID, juce::String widthID, juce::String wetID, juce::String dryID)
{
    reverbTitle.createSectionTitle("Reverb");
    addAndMakeVisible(reverbTitle);

    sizeSlider.createKnobWithLabel(apvts, sizeID, "Size");
    addAndMakeVisible(sizeSlider);
    widthSlider.createKnobWithLabel(apvts, widthID, "Width");
    addAndMakeVisible(widthSlider);
    dampSlider.createKnobWithLabel(apvts, dampID, "Damp");
    addAndMakeVisible(dampSlider);
    wetSlider.createKnobWithLabel(apvts, wetID, "Wet");
    addAndMakeVisible(wetSlider);
    drySlider.createKnobWithLabel(apvts, dryID, "Dry");
    addAndMakeVisible(drySlider);
}

Reverb1Component::~Reverb1Component()
{
}

void Reverb1Component::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void Reverb1Component::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Title
    reverbTitle.setBoundsSectionTitle(padding, 8, 5);

    // OSC macro, trans and gain draw
    const auto KnobStartX = padding;
    const auto KnobStartY = reverbTitle.getBottom();
    sizeSlider.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    widthSlider.setBoundsKnobWithLabel(sizeSlider.getRight(), KnobStartY);
    dampSlider.setBoundsKnobWithLabel(widthSlider.getRight(), KnobStartY);
    wetSlider.setBoundsKnobWithLabel(dampSlider.getRight(), KnobStartY);
    drySlider.setBoundsKnobWithLabel(dampSlider.getRight(), wetSlider.getBottom());
}