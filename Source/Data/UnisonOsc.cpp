/*
  ==============================================================================

    UnisonOsc.cpp
    Created: 26 Aug 2024 4:05:14pm
    Author:  BB8

  ==============================================================================
*/

#include "UnisonOsc.h"



void UnisonOsc::prepareToPlay(juce::dsp::ProcessSpec& spec, const int index)
{
    prepare(spec);

    uniOscGain.prepare(spec);
    uniOscPan.prepare(spec);

    uniOscGain.setGainLinear(0.8f);
    uniOscPan.setPan(0.0f);
    resetAllUni();
}

void UnisonOsc::renderNextBuffer(juce::AudioBuffer<float> &buffer, int startSample, int numSamples)
{
    uniBuffer.setSize(buffer.getNumChannels(), numSamples, false, false, true);
    uniBuffer.clear();

    juce::dsp::AudioBlock<float> uniBlock{ uniBuffer };

    process(juce::dsp::ProcessContextReplacing<float>(uniBlock));
    uniOscGain.process(juce::dsp::ProcessContextReplacing<float>(uniBlock));
    uniOscPan.process(juce::dsp::ProcessContextReplacing<float>(uniBlock));

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        buffer.addFrom(ch, 0, uniBuffer, ch, 0, numSamples, 0.5f);
    }
}

void UnisonOsc::setUniFrequency(const int& index, const float& frequency, const float& spread)
{
    if ((index + 1) % 2 == 0)
    {
        const auto spreadFreqH = frequency + ((float)index * spread);
        setFrequency(spreadFreqH);    
    }
    else
    {
        const auto spreadFreqL = frequency - ((float)index * spread);
        setFrequency(spreadFreqL);
    }
}

void UnisonOsc::setUniWidth(const int& index, const float& pan, const float& uniWidth)
{
    if ((index + 1) % 2 == 0)
    {
        float delta = pan + ((float)index * 0.1) + uniWidth;
        float rightPan = juce::jlimit(-1.0f, 1.0f, delta);
        uniOscPan.setPan(rightPan);
    }
    else
    {
        float delta = pan - ((float)index * 0.1) - uniWidth;
        float leftPan = juce::jlimit(-1.0f, 1.0f, delta);
        uniOscPan.setPan(leftPan);
    }
}


void UnisonOsc::resetAllUni()
{
    reset();
    uniOscGain.reset();
    uniOscPan.reset();
}