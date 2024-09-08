/*
  ==============================================================================

    AHDSRData.cpp
    Created: 6 Sep 2024 11:32:59pm
    Author:  BB8

  ==============================================================================
*/

#include "AHDSRData.h"

void AHDSRData::setSampleRate(double projSampleRate)
{
    sampleRate = projSampleRate;
}

void AHDSRData::noteOn()
{
    envelopeValue = 0.0f;
    state = State::Attack;
    currentSample = 0;
}

void AHDSRData::noteOff()
{
    state = State::Release;
    //currentSample = 0;
}

void AHDSRData::applyEnvelopeToBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int i = startSample; i < numSamples; ++i)
        {
            channelData[i] *= getNextSample();
        }
    }
}

float AHDSRData::getNextSample()
{
    calculateEnvelopeTimes();
    switch (state)
    {
    case State::Attack:
        envelopeValue += applySlope(1.0f / attackSamples, attackSlope);
        if (envelopeValue >= 1.0f) {
            envelopeValue = 1.0f;
            state = State::Hold;
        }
        break;

    case State::Hold:
        if (++currentSample >= holdSamples)
            state = State::Decay;
        break;

    case State::Decay:
        envelopeValue -= applySlope((1.0f - sustain) / decaySamples, decaySlope);
        if (envelopeValue <= sustain) {
            envelopeValue = sustain;
            state = State::Sustain;
        }
        break;

    case State::Sustain:
        // Remain at sustain level
        break;

    case State::Release:
        releaseStartValue = envelopeValue;
        if (releaseStartValue <= 0.0f)
        {
            break;
        }
        envelopeValue -= applySlope(releaseStartValue / releaseSamples, releaseSlope);
        if (envelopeValue <= 0.0f) {
            envelopeValue = 0.0f;
            state = State::Idle;
        }
        break;

    case State::Idle:
        break;
    }
    return envelopeValue;
}

void AHDSRData::updateParams(float newAttack, float newHold, float newDecay, float newSustain, float newRelease)
    //float newAttackSlope, float newDecaySlope, float newReleaseSlope)
{
    attack = newAttack;
    hold = newHold;
    decay = newDecay;
    sustain = newSustain;
    release = newRelease;

    //attackSlope = newAttackSlope;
    //decaySlope = newDecaySlope;
    //releaseSlope = newReleaseSlope;

    calculateEnvelopeTimes();
}

float AHDSRData::applySlope(float input, float slope)
{
    if (slope == 1.0f) {
        return input; // Linear
    }
    return std::pow(input, std::log(slope + 1.0f)); // Logarithmic
}

void AHDSRData::calculateEnvelopeTimes()
{
    attackSamples = static_cast<int>(attack * sampleRate);
    holdSamples = static_cast<int>(hold * sampleRate);
    decaySamples = static_cast<int>(decay * sampleRate);
    releaseSamples = static_cast<int>(release * sampleRate);
}

void AHDSRData::reset()
{
    envelopeValue = 0.0f;
    state = State::Idle;
}