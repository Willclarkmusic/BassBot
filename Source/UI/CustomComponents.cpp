/*
  ==============================================================================

    CustomComponents.cpp
    Created: 30 Aug 2024 4:20:19pm
    Author:  BB8

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================

CustomComponents::CustomComponents()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomComponents::~CustomComponents()
{
}

void CustomComponents::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void CustomComponents::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

//==============================================================================

void SectionTitleLabel::createSectionTitle(juce::String labelString)
{
    setSize(boundsWidth, boundsHeight);

    label.setText(labelString, juce::NotificationType::dontSendNotification);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(16.0f);
    addAndMakeVisible(label);
}

void SectionTitleLabel::setBoundsSectionTitle(int xPos, int yPos, int charCount)
{

    //boundsWidth = charCount * 5;

    setBounds(xPos, yPos, boundsWidth, boundsHeight);
    label.setBounds(padding, 0, labelWidth, labelHeight);
}

void SectionTitleLabel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
}

//==============================================================================

void AnimatedKnobMedium::createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& paramID, juce::String labelString)
{
    setSize(knobRadius, knobRadius + (2 * labelHeight));

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, paramID, slider);

    label.setText(labelString, juce::NotificationType::dontSendNotification);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    addAndMakeVisible(label);
}

void AnimatedKnobMedium::setBoundsKnobWithLabel(int xPos, int yPos)
{
    setBounds(xPos, yPos, knobRadius, knobRadius + (2 * labelHeight));
    label.setBounds(0, padding, labelWidth, labelHeight);
    slider.setBounds(0, label.getBottom(), knobRadius, knobRadius);
}

void AnimatedKnobMedium::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(5));
}
//==============================================================================

void AnimatedKnobSmall::createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& paramID, juce::String labelString)
{
    setSize(knobRadius, knobRadius + (2 * labelHeight));

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, paramID, slider);

    label.setText(labelString, juce::NotificationType::dontSendNotification);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    addAndMakeVisible(label);
}

void AnimatedKnobSmall::setBoundsKnobWithLabel(int xPos, int yPos)
{
    setBounds(xPos, yPos, knobRadius, knobRadius + (2 * labelHeight));
    label.setBounds(0, padding, labelWidth, labelHeight);
    slider.setBounds(0, label.getBottom(), knobRadius, knobRadius);
}

void AnimatedKnobSmall::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(5));
}

//==============================================================================

void ComboBoxMedium::createComboBox(juce::AudioProcessorValueTreeState& apvts, juce::String& comboBoxID, juce::StringArray& choices)
{
    comboBox.addItemList(choices, 1);
    addAndMakeVisible(comboBox);
    attachment = std::make_unique<ComboBoxAttachment>(apvts, comboBoxID, comboBox);
}

void ComboBoxMedium::setBoundsComboBox(int xPos, int yPos)
{
    setBounds(xPos, yPos, selectorWidth, selectorHeight);
    comboBox.setBounds(0, 0, selectorWidth, selectorHeight);
}

void ComboBoxMedium::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(5));
}

//==============================================================================

void SliderBoxMedium::createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& paramID, juce::String labelString)
{
    setSize(knobWidth, knobHeight + labelHeight);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    slider.setSliderSnapsToMousePosition(false);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, labelWidth, labelHeight);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, paramID, slider);

    label.setText(labelString, juce::NotificationType::dontSendNotification);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    addAndMakeVisible(label);
}

void SliderBoxMedium::setBoundsKnobWithLabel(int xPos, int yPos)
{
    setBounds(xPos, yPos, boundsWidth, boundsHeight);
    label.setBounds(0, padding, labelWidth, labelHeight);
    slider.setBounds((boundsWidth - knobWidth) / 2, label.getBottom(), knobWidth, knobHeight);
}

void SliderBoxMedium::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::ghostwhite);
    g.drawRect(getLocalBounds().reduced(5));
}

//==============================================================================

void SliderBoxSmall::createKnobWithLabel(juce::AudioProcessorValueTreeState& apvts, juce::String& paramID, juce::String labelString)
{
    setSize(knobWidth, knobHeight + labelHeight);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    slider.setSliderSnapsToMousePosition(false);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, labelWidth, labelHeight);
    addAndMakeVisible(slider);

    attachment = std::make_unique<SliderAttachment>(apvts, paramID, slider);

    label.setText(labelString, juce::NotificationType::dontSendNotification);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(8.0f);
    addAndMakeVisible(label);
}

void SliderBoxSmall::setBoundsKnobWithLabel(int xPos, int yPos)
{
    setBounds(xPos, yPos, boundsWidth, boundsHeight);
    label.setBounds(padding, 0, labelWidth, labelHeight);
    slider.setBounds(padding, label.getBottom(), knobWidth, knobHeight);

}

void SliderBoxSmall::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
}

//==============================================================================

