/*
  ==============================================================================

    FilterComponent.cpp
    Created: 21 Aug 2024 11:21:34am
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId,
    juce::String dbOctID, juce::String driveID, juce::String cutoffID, juce::String resID, juce::String envID)
{
    //Title
    filterTitle.createSectionTitle("Filter");
    addAndMakeVisible(filterTitle);

    // Filter select
    juce::StringArray choices{ "Lpf", "Bpf", "Hpf" };
    typeSelector.createComboBox(apvts, filterTypeSelectorId, choices);
    addAndMakeVisible(typeSelector);

    juce::StringArray choices2{ "12db/oct", "24db/oct" };
    dbOctSelector.createComboBox(apvts, dbOctID, choices2);
    addAndMakeVisible(dbOctSelector);

    // Filter DB/oct
    cutoffKnob.createKnobWithLabel(apvts, cutoffID, "Cutoff");
    addAndMakeVisible(cutoffKnob);
    resKnob.createKnobWithLabel(apvts, resID, "Res");
    addAndMakeVisible(resKnob);
    driveSlider.createKnobWithLabel(apvts, driveID, "Drive");
    addAndMakeVisible(driveSlider);
    envAmountSlider.createKnobWithLabel(apvts, envID, "Env2");
    addAndMakeVisible(envAmountSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void FilterComponent::resized()
{
    // Global 
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Title
    filterTitle.setBoundsSectionTitle(padding, 8, 5);

    // Selector menu sizes
    typeSelector.setBoundsComboBox(filterTitle.getRight(), 8);
    dbOctSelector.setBoundsComboBox(typeSelector.getRight(), 8);

    // Knob sizes
    const auto KnobStartX = padding;
    const auto KnobStartY = filterTitle.getBottom();
    
    cutoffKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    resKnob.setBoundsKnobWithLabel(cutoffKnob.getRight(), KnobStartY);
    driveSlider.setBoundsKnobWithLabel(resKnob.getRight(), KnobStartY);
    envAmountSlider.setBoundsKnobWithLabel(resKnob.getRight(), driveSlider.getBottom());
}