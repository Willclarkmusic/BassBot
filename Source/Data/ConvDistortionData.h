/*
  ==============================================================================

    ConvDistortionData.h
    Created: 23 Aug 2024 4:59:37pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ConvDistortionData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParams(const int& irIndex, const juce::StringArray& irFiles,
        const float& dryWet, const float& gain);
    void loadIRFile(const int& irIndex, const juce::StringArray& irFiles);

    void resetAll();

private:
    juce::dsp::Convolution convolutionModule;

    juce::dsp::DryWetMixer<float> dryWetParam;

    juce::dsp::Gain<float> gain1;

    //juce::File irDark = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
    //    .getParentDirectory().getParentDirectory().getChildFile("Source/Resources/ExcaliburDark1.wav");


};
