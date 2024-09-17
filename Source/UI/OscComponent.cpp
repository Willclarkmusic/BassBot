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
    //TItle
    osc1Title.createSectionTitle("OSC 1");
    addAndMakeVisible(osc1Title);
    
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

    // Title
    osc1Title.setBoundsSectionTitle(padding, 8, 5);

    // Wave Selector menu 
    waveSelector.setBoundsComboBox(osc1Title.getRight(), 8);

    // OSC params draw
    const auto KnobStartX = padding;
    const auto KnobStartY = waveSelector.getBottom();
    macroKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    transKnob.setBoundsKnobWithLabel(macroKnob.getRight(), KnobStartY);
    gainKnob.setBoundsKnobWithLabel(transKnob.getRight(), KnobStartY);
    panKnob.setBoundsKnobWithLabel(gainKnob.getRight(), KnobStartY);
    unisonKnob.setBoundsKnobWithLabel(panKnob.getRight(), KnobStartY);
    widthKnob.setBoundsKnobWithLabel(unisonKnob.getRight(), KnobStartY);
    spreadKnob.setBoundsKnobWithLabel(unisonKnob.getRight(), widthKnob.getBottom());

}

