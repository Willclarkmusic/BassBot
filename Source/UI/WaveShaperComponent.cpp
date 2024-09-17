/*
  ==============================================================================

    WaveShaperComponent.cpp
    Created: 23 Aug 2024 12:16:27pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveShaperComponent.h"

//==============================================================================
WaveShaperComponent::WaveShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String inputID, 
    juce::String outputID, juce::String typeID)
{
    // Title
    saturationTitle.createSectionTitle("Shaper");
    addAndMakeVisible(saturationTitle);

    // Type select
    juce::StringArray choices{ "Tan", "Sin", "Cos" };
    waveTypeSelector.createComboBox(apvts, typeID, choices);
    addAndMakeVisible(waveTypeSelector);

    // Input Output gains
    inputSlider.createKnobWithLabel(apvts, inputID, "Input");
    addAndMakeVisible(inputSlider);

    outputSlider.createKnobWithLabel(apvts, outputID, "Output");
    addAndMakeVisible(outputSlider);
}

WaveShaperComponent::~WaveShaperComponent()
{
}

void WaveShaperComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void WaveShaperComponent::resized()
{
    // Global 
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Title
    saturationTitle.setBoundsSectionTitle(padding, 8, 5);

    // Wave Selector menu
    waveTypeSelector.setBoundsComboBox(saturationTitle.getRight(), 8);

    // Knob sizes
    const auto KnobStartX = padding;
    const auto KnobStartY = waveTypeSelector.getBottom();

    inputSlider.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    outputSlider.setBoundsKnobWithLabel(inputSlider.getRight(), KnobStartY);
}