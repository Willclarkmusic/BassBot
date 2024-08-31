/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BeastySynth1AudioProcessorEditor::BeastySynth1AudioProcessorEditor (BeastySynth1AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    osc1(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1MACRO", "OSC1TRANS", "OSC1GAIN", "OSC1PAN", "OSC1UNI", "OSC1WIDTH", "OSC1SPREAD"),
    adsr1(audioProcessor.apvts, "ATT1", "DEC1", "SUS1", "REL1"),
    filter1(audioProcessor.apvts, "FILTERTYPE1", "DBOCT1", "FDRIVE1", "CUTOFF1", "RES1", "FENV1"),
    convDist1(audioProcessor, audioProcessor.apvts, "IRLOAD1", "CDWET1", "CDGAIN1"),
    reverb1(audioProcessor.apvts, "SIZE1", "DAMP1", "WIDTH1", "WET1", "DRY1"),
    adsr2(audioProcessor.apvts, "ATT2", "DEC2", "SUS2", "REL2"),
    oscSub(audioProcessor.apvts, "OSCSUBWAVETYPE", "OSCSUBMACRO", "OSCSUBTRANS", "OSCSUBGAIN"),
    waveShaper1(audioProcessor.apvts, "WSINPUT1", "WSOUTPUT1", "WSTYPE1"),
    MSCompressor(audioProcessor.apvts, "MIDSGAIN", "SIDESGAIN")
{
    setSize (2000, 400);

    addAndMakeVisible(osc1);
    addAndMakeVisible(adsr1);
    addAndMakeVisible(filter1);
    addAndMakeVisible(convDist1);
    addAndMakeVisible(adsr2);
    addAndMakeVisible(oscSub);
    addAndMakeVisible(waveShaper1);
    addAndMakeVisible(reverb1);

    //addAndMakeVisible(MSCompressor);

}

BeastySynth1AudioProcessorEditor::~BeastySynth1AudioProcessorEditor()
{
}

//==============================================================================
void BeastySynth1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::darkgrey);
    g.setFont (juce::FontOptions (10.0f));
}

void BeastySynth1AudioProcessorEditor::resized()
{
    // Draw Elements
    // Top Row
    osc1.setBounds(0, 0, 600, 150);
    filter1.setBounds(osc1.getRight(), 0, 350, 150);
    convDist1.setBounds(filter1.getRight(), 0, 250, 150);
    reverb1.setBounds(convDist1.getRight(), 0, 400, 150);


    // Middle Row 
    adsr1.setBounds(0, osc1.getBottom(), 250, 100);
    adsr2.setBounds(adsr1.getRight(), filter1.getBottom(), 250, 100);

    // Bottom Row
    oscSub.setBounds(0, adsr1.getBottom(), 250, 150);
    waveShaper1.setBounds(oscSub.getRight(), adsr2.getBottom(), 250, 150);


    MSCompressor.setBounds(1000, 0, 200, 150);
}