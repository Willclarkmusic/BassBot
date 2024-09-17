/*
  ==============================================================================

    AHDSRData.h
    Created: 6 Sep 2024 11:32:59pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AHDSRData
{
public:
    AHDSRData() {}

    void noteOn();
    void noteOff();

    void updateParams(float attack, float hold, float decay, float sustain, float release,
        float attackSlope, float decaySlope, float releaseSlope);

    void applyEnvelopeToBuffer(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);
    float getNextSample();

    bool isActive() const noexcept { return state != State::Idle; }

    void setSampleRate(double projSampleRate);

    void reset();

private:
    void calculateEnvelopeTimes();
    float applySlope(float input, float slope);

    enum class State { Idle, Attack, Hold, Decay, Sustain, Release };
    State state = State::Idle;

    float attack = 0.01f, hold = 0.01f, decay = 0.5f, sustain = 0.5f, release = 0.5f;
    float attackSlope = 1.0f, decaySlope = 1.0f, releaseSlope = 1.0f;

    int currentSample = 0;
    float envelopeValue = 0.0f;
    float releaseStartValue = 0.0f;

    int attackSamples = 0, holdSamples = 0, decaySamples = 0, releaseSamples = 0;
    int sampleRate = 44100; // Default, can be updated elsewhere

};