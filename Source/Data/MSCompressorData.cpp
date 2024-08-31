/*
  ==============================================================================

    MSCompressorData.cpp
    Created: 22 Aug 2024 4:43:58pm
    Author:  BB8

  ==============================================================================
*/

#include "MSCompressorData.h"



void MSCompressorData::prepareToPlay(juce::dsp::ProcessSpec spec, double sampleRate, int samplesPerBlock, int outputChannels)
{    
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    midsGainParam.prepare(spec);
    sidesGainParam.prepare(spec);
}

void MSCompressorData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    //for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel)
    //{
    //    auto* leftData = audioBlock.getChannelPointer(0);
    //    auto* rightData = audioBlock.getChannelPointer(1);
    //    
    //    for (int sample = 0; sample < audioBlock.getNumSamples(); ++sample)
    //    {
    //        const auto mids = 0.5f * (leftData[sample] + rightData[sample]);
    //        const auto sides = 0.5f * (leftData[sample] - rightData[sample]);

    //        //midsGainParam.setGainLinear(mMidsGain);
    //        //sidesGainParam.setGainLinear(mSidesGain);
    //        //midsGainParam.process(mids);
    //        //sidesGainParam.process(sides); 

    //        const auto newLeft = mids + sides;
    //        const auto newRight = mids - sides;

    //        leftData[sample] = newLeft;
    //        rightData[sample] = newRight;
    //    }

    //}
}

void MSCompressorData::updateMSCompParams(float midsGain, float sidesGain)
{
    midsGainParam.setGainLinear(midsGain);
    sidesGainParam.setGainLinear(sidesGain);

    mMidsGain = midsGain;
    mSidesGain = sidesGain;
}

void MSCompressorData::setCrossover()
{

}

void MSCompressorData::setGains()
{

}
void MSCompressorData::setMidParams()
{

}

void MSCompressorData::setSideParams()
{

}