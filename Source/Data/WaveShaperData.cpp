/*
  ==============================================================================

    WaveShaperData.cpp
    Created: 23 Aug 2024 12:16:08pm
    Author:  BB8

  ==============================================================================
*/

#include "WaveShaperData.h"

void WaveShaperData::prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels)
{
    resetAll();

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    inputGain.prepare(spec);
    inputGain.setRampDurationSeconds(0.02f);
    outputGain.prepare(spec);
    outputGain.setRampDurationSeconds(0.02f);

    wsTahn.prepare(spec);        
}

void WaveShaperData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    inputGain.process(juce::dsp::ProcessContextReplacing<float>{audioBlock});

    switch (wsType)
    {
    case 0:
        wsTahn.process(juce::dsp::ProcessContextReplacing<float>{audioBlock});
        break;
    case 1:
        wsSinh.process(juce::dsp::ProcessContextReplacing<float>{audioBlock});
        break;
    case 2:
        wsCosh.process(juce::dsp::ProcessContextReplacing<float>{audioBlock});
        break;
    default:
        break;
    }

    outputGain.process(juce::dsp::ProcessContextReplacing<float>{audioBlock});
}

void WaveShaperData::updateParams(const float input, const float output, const int type)
{
    inputGain.setGainDecibels(input);
    outputGain.setGainDecibels(output);
    wsType = type;
}

void WaveShaperData::resetAll()
{
    wsTahn.reset();
    inputGain.reset();
    outputGain.reset();
}