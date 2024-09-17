/*
  ==============================================================================

    WTOscComponent.cpp
    Created: 2 Sep 2024 12:39:57pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WTOscComponent.h"
//==============================================================================
WTOscComponent::WTOscComponent(BeastySynth1AudioProcessor& processor, juce::AudioProcessorValueTreeState& apvts,
    juce::String waveSelectorId, juce::String morphID, juce::String transID, juce::String gainID,
    juce::String panID, juce::String unisonID, juce::String widthID, juce::String spreadID)
    : audioProcessor(processor)
{
    // Title
    osc2Title.createSectionTitle("OSC 2");
    addAndMakeVisible(osc2Title);

    // Wave select
    juce::StringArray choices{ audioProcessor.getWaveTableFiles() };
    for (int i = 0; i < choices.size(); i++)
    {
        choices.set(i, juce::File(choices[i]).getFileNameWithoutExtension());
    }
    waveSelector.createComboBox(apvts, waveSelectorId, choices);
    addAndMakeVisible(waveSelector);

    // Osc Pitch and gain control
    morphKnob.createKnobWithLabel(apvts, morphID, "Morph");
    addAndMakeVisible(morphKnob);
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

WTOscComponent::~WTOscComponent()
{
}

void WTOscComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(2));
}

void WTOscComponent::resized()
{
    const auto padding = 5;
    const auto bounds = getLocalBounds().reduced(10);

    // Title
    osc2Title.setBoundsSectionTitle(padding, 8, 5);

    // Wave Selector menu
    const auto selectorWidth = 60;
    const auto selectorHeight = 20;
    waveSelector.setBoundsComboBox(osc2Title.getRight(), 8);

    // OSC params draw
    const auto KnobStartX = padding;
    const auto KnobStartY = waveSelector.getBottom() + padding;
    morphKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    transKnob.setBoundsKnobWithLabel(morphKnob.getRight(), KnobStartY);
    gainKnob.setBoundsKnobWithLabel(transKnob.getRight(), KnobStartY);
    panKnob.setBoundsKnobWithLabel(gainKnob.getRight(), KnobStartY);
    unisonKnob.setBoundsKnobWithLabel(panKnob.getRight(), KnobStartY);
    widthKnob.setBoundsKnobWithLabel(unisonKnob.getRight(), KnobStartY);
    spreadKnob.setBoundsKnobWithLabel(unisonKnob.getRight(), widthKnob.getBottom());

}

