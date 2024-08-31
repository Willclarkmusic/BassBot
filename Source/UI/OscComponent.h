/*
  ==============================================================================

    OscComponent.h
    Created: 15 Aug 2024 11:37:38am
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomComponents.h"

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId,
        juce::String macroID, juce::String transID, juce::String gainID, juce::String panID, 
        juce::String unisonID, juce::String widthID, juce::String spreadID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    void setComboBoxDefault(juce::AudioProcessorValueTreeState& apvts, juce::StringArray& choices,
        juce::ComboBox& comboBox, juce::String& ID, std::unique_ptr <ComboBoxAttachment>& attachment);

    void setSliderLabelDefault(juce::Slider& slider, juce::Label& label,
        juce::AudioProcessorValueTreeState &apvts, juce::String ID,
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);

    void setBoundsSliderWLabel(juce::Slider& slider, juce::Label& label, int xPos, int yPos, 
        int sliderWH, int labelW, int labelH, int padding);

    // Osc wave select
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;



    AnimatedKnobMedium macroKnob;
    AnimatedKnobMedium transKnob;
    AnimatedKnobMedium gainKnob;
    AnimatedKnobMedium panKnob;
    AnimatedKnobMedium unisonKnob;
    AnimatedKnobMedium widthKnob;
    AnimatedKnobMedium spreadKnob;
    
    
    //// Macro
    //juce::Slider oscMacroSlider;
    //std::unique_ptr<SliderAttachment> oscMacroAttachment;
    //juce::Label oscMacroLabel{"Macro", "Macro"};  

    //// Transpose
    //juce::Slider oscTransSlider;
    //std::unique_ptr<SliderAttachment> oscTransAttachment;
    //juce::Label oscTransLabel{ "Trans", "Trans" };

    //// Gain
    //juce::Slider oscGainSlider;
    //std::unique_ptr<SliderAttachment> oscGainAttachment;
    //juce::Label oscGainLabel{ "Gain", "Gain" };

    //// Pan
    //juce::Slider oscPanSlider;
    //std::unique_ptr<SliderAttachment> oscPanAttachment;
    //juce::Label oscPanLabel{ "Pan", "Pan" };
    //
    //// Uni Voices
    //juce::Slider oscUniSlider;
    //std::unique_ptr<SliderAttachment> oscUniAttachment;
    //juce::Label oscUniLabel{ "Uni", "Uni" };
    //
    //// Uni Width
    //juce::Slider oscWidthSlider;
    //std::unique_ptr<SliderAttachment> oscWidthAttachment;
    //juce::Label oscWidthLabel{ "Width", "Width" };
    //
    //// Uni Spread
    //juce::Slider oscSpreadSlider;
    //std::unique_ptr<SliderAttachment> oscSpreadAttachment;
    //juce::Label oscSpreadLabel{ "Width", "Width" };



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
