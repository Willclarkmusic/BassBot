/*
  ==============================================================================

    OscSubComponent.cpp
    Created: 23 Aug 2024 4:02:41pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscSubComponent.h"

//==============================================================================
OscSubComponent::OscSubComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId,
    juce::String macroID, juce::String transID, juce::String gainID)
{
    //TItle
    oscSubTitle.createSectionTitle("Sub Osc");
    addAndMakeVisible(oscSubTitle);

    // Wave select
    juce::StringArray choices{ "Sin", "Saw", "Squ" };
    waveSelector.createComboBox(apvts, waveSelectorId, choices);
    addAndMakeVisible(waveSelector);

    // Osc Pitch and gain control
    macroKnob.createKnobWithLabel(apvts, macroID, "Macro");
    addAndMakeVisible(macroKnob);
    transKnob.createKnobWithLabel(apvts, transID, "Trans");
    addAndMakeVisible(transKnob);
    gainKnob.createKnobWithLabel(apvts, gainID, "Gain");
    addAndMakeVisible(gainKnob);
}

OscSubComponent::~OscSubComponent()
{
}

void OscSubComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void OscSubComponent::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Title
    oscSubTitle.setBoundsSectionTitle(padding, 8, 5);

    // Wave Selector menu 
    waveSelector.setBoundsComboBox(oscSubTitle.getRight(), 8);

    // OSC params draw
    const auto KnobStartX = padding;
    const auto KnobStartY = waveSelector.getBottom();
    macroKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    transKnob.setBoundsKnobWithLabel(macroKnob.getRight(), KnobStartY);
    gainKnob.setBoundsKnobWithLabel(transKnob.getRight(), KnobStartY);

}