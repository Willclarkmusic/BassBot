/*
  ==============================================================================

    OscComponent.cpp
    Created: 15 Aug 2024 11:37:38am
    Author:  BB8

  ==============================================================================
*/


#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, 
    juce::String macroID, juce::String transID, juce::String gainID, juce::String panID, 
    juce::String unisonID, juce::String widthID, juce::String spreadID)
{
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
    panKnob.createKnobWithLabel(apvts, panID, "Pan");
    addAndMakeVisible(panKnob); 
    unisonKnob.createKnobWithLabel(apvts, unisonID, "Unison");
    addAndMakeVisible(unisonKnob); 
    widthKnob.createKnobWithLabel(apvts, widthID, "Width");
    addAndMakeVisible(widthKnob); 
    spreadKnob.createKnobWithLabel(apvts, spreadID, "Spread");
    addAndMakeVisible(spreadKnob); 
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void OscComponent::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Wave Selector menu
    const auto selectorWidth = 60;
    const auto selectorHeight = 20;    
    waveSelector.setBoundsComboBox((bounds.getWidth() / 3) * 2, 10);

    // OSC params draw
    const auto KnobStartX = padding;
    const auto KnobStartY = waveSelector.getBottom() + padding;
    macroKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    transKnob.setBoundsKnobWithLabel(macroKnob.getRight(), KnobStartY);
    gainKnob.setBoundsKnobWithLabel(transKnob.getRight(), KnobStartY);
    panKnob.setBoundsKnobWithLabel(gainKnob.getRight(), KnobStartY);
    unisonKnob.setBoundsKnobWithLabel(panKnob.getRight(), KnobStartY);
    widthKnob.setBoundsKnobWithLabel(unisonKnob.getRight(), KnobStartY);
    spreadKnob.setBoundsKnobWithLabel(widthKnob.getRight(), KnobStartY);

}

