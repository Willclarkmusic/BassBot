/*
  ==============================================================================

    LFO1Data.h
    Created: 21 Sep 2024 3:19:36pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class LFO1
{
public:
    enum class WaveShape : int
    {
        none,
        sine,
        triangle,
        sawUp,
        sawDown,
        square,
        squarePos,
        sampleAndHold,
        noise,
        stepUp3,
        stepUp4,
        stepup8,
        stepDown3,
        stepDown4,
        stepDown8,
        pyramid3,
        pyramid5,
        pyramid9,
    };
    
    struct Parameters
    {
        WaveShape waveShape = WaveShape::sine;
        float frequency = 0, phase = 0, offset = 0, depth = 0, delay = 0, fade = 0;
    };

    LFO1()
    {
        juce::Random rnd{ 1 };

        for (int i = 0; i < 1000; i++)
            randomPoints.add(rnd.nextFloat() * 2 - 1);
    }

    void setSampleRate(double sr) { sampleRate = sr; }
    void setParameters(Parameters p) { parameters = p; }
    void reset()
    {
        output = 0.0f;
        phase = 0.0f;
        curPhase = 0.0f;
        curFade = 1.0f;
        fadeDelta = 0.0f;
        delaySteps = 0;
    }

private:

    Parameters parameters;

    double sampleRate = 0.0;
    float phase = 0.0f, curPhase = 0.0f, output = 0.0f, fadeDelta = 0.0f, curFade = 1.0f;
    int delaySteps = 0;
    juce::Array<float> randomPoints;
}; 