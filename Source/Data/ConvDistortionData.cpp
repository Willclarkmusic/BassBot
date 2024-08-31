/*
  ==============================================================================

    ConvDistortionData.cpp
    Created: 23 Aug 2024 4:59:37pm
    Author:  BB8

  ==============================================================================
*/

#include "ConvDistortionData.h"

void ConvDistortionData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    resetAll();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    convolutionModule.prepare(spec);

    gain1.prepare(spec);
    gain1.setGainDecibels(0.0f);

    dryWetParam.prepare(spec);
    dryWetParam.setMixingRule(juce::dsp::DryWetMixingRule::balanced);    
}

void ConvDistortionData::process(juce::AudioBuffer<float>& buffer)
{    
    juce::dsp::AudioBlock<float> block{ buffer };

    dryWetParam.pushDrySamples(block);

    gain1.process(juce::dsp::ProcessContextReplacing<float>(block));

    convolutionModule.process(juce::dsp::ProcessContextReplacing<float>(block));


    dryWetParam.mixWetSamples(block);

}

void ConvDistortionData::updateParams(const int& irIndex, const juce::StringArray& irArray,
    const float& dryWet, const float& gain)
{
    loadIRFile(irIndex, irArray);
    dryWetParam.setWetMixProportion(dryWet);
    juce::Logger::writeToLog("Mix set");


    gain1.setGainDecibels(gain);
}

void ConvDistortionData::loadIRFile(const int& irIndex, const juce::StringArray& irArray)
{
    if (irIndex >= 0 && irIndex < irArray.size())
    {
        juce::File selectedIRFile = irArray[irIndex];

        if (selectedIRFile.existsAsFile())
        {          
            convolutionModule.loadImpulseResponse(selectedIRFile,
                juce::dsp::Convolution::Stereo::no,
                juce::dsp::Convolution::Trim::no, 0,
                juce::dsp::Convolution::Normalise::yes);

            juce::Logger::writeToLog("Impulse response loaded " + selectedIRFile.getFullPathName());

        }
        else
        {
            juce::Logger::writeToLog("Impulse response file does not exist: " + selectedIRFile.getFullPathName());
        }

    }
}

void ConvDistortionData::resetAll()
{
    dryWetParam.reset();
    convolutionModule.reset();
}
