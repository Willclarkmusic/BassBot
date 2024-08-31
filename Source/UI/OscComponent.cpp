/*
  ==============================================================================

    OscComponent.cpp
    Created: 15 Aug 2024 11:37:38am
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, 
    juce::String macroID, juce::String transID, juce::String gainID, juce::String panID, 
    juce::String unisonID, juce::String widthID, juce::String spreadID)
{
    // Wave select
    juce::StringArray choices{ "Sin", "Saw", "Squ" };
    setComboBoxDefault(apvts, choices, oscWaveSelector, waveSelectorId, oscWaveSelectorAttachment);

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
 
 
    //setSliderLabelDefault(oscMacroSlider, oscMacroLabel, apvts, macroID, oscMacroAttachment);
    //setSliderLabelDefault(oscTransSlider, oscTransLabel, apvts, transID, oscTransAttachment);
    //setSliderLabelDefault(oscGainSlider, oscGainLabel, apvts, gainID, oscGainAttachment);
    //setSliderLabelDefault(oscPanSlider, oscPanLabel, apvts, panID, oscPanAttachment);
    //setSliderLabelDefault(oscUniSlider, oscUniLabel, apvts, unisonID, oscUniAttachment);
    //setSliderLabelDefault(oscWidthSlider, oscWidthLabel, apvts, widthID, oscWidthAttachment);
    //setSliderLabelDefault(oscSpreadSlider, oscSpreadLabel, apvts, spreadID, oscSpreadAttachment);
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
    
    oscWaveSelector.setBounds((bounds.getWidth() / 3) * 2, 10, selectorWidth, selectorHeight);

    // OSC macro, trans and gain draw
    const auto smKnobWidth = 50;
    const auto smKnobHeight = 50;
    const auto defKnobWidth = 80;
    const auto defKnobHeight = 80;
    const auto KnobStartX = padding;
    const auto KnobStartY = oscWaveSelector.getBottom() + padding;
    const auto labelHeight = 15;
    const auto labelWidth = defKnobWidth;

    macroKnob.setBoundsKnobWithLabel(KnobStartX, KnobStartY);
    transKnob.setBoundsKnobWithLabel(macroKnob.getRight(), KnobStartY);
    gainKnob.setBoundsKnobWithLabel(transKnob.getRight(), KnobStartY);
    panKnob.setBoundsKnobWithLabel(gainKnob.getRight(), KnobStartY);
    unisonKnob.setBoundsKnobWithLabel(panKnob.getRight(), KnobStartY);
    widthKnob.setBoundsKnobWithLabel(unisonKnob.getRight(), KnobStartY);
    spreadKnob.setBoundsKnobWithLabel(widthKnob.getRight(), KnobStartY);



    //setBoundsSliderWLabel(oscMacroSlider, oscMacroLabel, KnobStartY, KnobStartY, defKnobHeight, 
    //    labelWidth, labelHeight, padding);
    //setBoundsSliderWLabel(oscTransSlider, oscTransLabel, macroKnob.getRight(), KnobStartY, defKnobHeight,
    //    labelWidth, labelHeight, padding);
    //setBoundsSliderWLabel(oscGainSlider, oscGainLabel, oscTransSlider.getRight(), KnobStartY, defKnobHeight,
    //    labelWidth, labelHeight, padding);
    //setBoundsSliderWLabel(oscPanSlider, oscPanLabel, oscGainSlider.getRight(), KnobStartY, defKnobHeight,
    //    labelWidth, labelHeight, padding);

    //setBoundsSliderWLabel(oscUniSlider, oscUniLabel, oscPanSlider.getRight(), KnobStartY, defKnobHeight,
    //    labelWidth, labelHeight, padding);
    //setBoundsSliderWLabel(oscWidthSlider, oscWidthLabel, oscUniSlider.getRight(), KnobStartY, defKnobHeight,
    //    labelWidth, labelHeight, padding);
    //setBoundsSliderWLabel(oscSpreadSlider, oscSpreadLabel, oscWidthSlider.getRight(), KnobStartY, defKnobHeight,
    //    labelWidth, labelHeight, padding);
}

void OscComponent::setComboBoxDefault(juce::AudioProcessorValueTreeState& apvts, juce::StringArray& choices,
    juce::ComboBox& comboBox, juce::String& ID, std::unique_ptr<ComboBoxAttachment>& attachment)
{
    comboBox.addItemList(choices, 1);
    addAndMakeVisible(comboBox);
    attachment = std::make_unique<ComboBoxAttachment>(apvts, ID, comboBox);
}

void OscComponent::setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, int sliderWH, int labelW, int labelH, int padding)
{
    label.setBounds(xPos, yPos, labelW, labelH);
    slider.setBounds(xPos, label.getBottom(), sliderWH, sliderWH);
}

void OscComponent::setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
    juce::AudioProcessorValueTreeState& apvts, juce::String ID,
    std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, ID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    addAndMakeVisible(label);
}
