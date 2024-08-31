/*
  ==============================================================================

    Reverb1Data.cpp
    Created: 24 Aug 2024 3:34:17pm
    Author:  BB8

  ==============================================================================
*/

#include "Reverb1Data.h"

void ReverbData::prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int numChannels)
{
    resetAll();
}

void ReverbData::renderNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block{ buffer };
    processStereo(block.getChannelPointer(0), block.getChannelPointer(1), buffer.getNumSamples());
}

void ReverbData::updateParams(const float& size, const float& damping, const float& width, const float& wet, const float& dry)
{
    reverbParams.roomSize = size;
    reverbParams.damping = damping;
    reverbParams.width = width;
    reverbParams.wetLevel = wet;
    reverbParams.dryLevel = dry;
    setParameters(reverbParams);
}

void ReverbData::resetAll()
{

}