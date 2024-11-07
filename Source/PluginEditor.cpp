/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "UI/HorizontalMeter.h"

//==============================================================================
BeastySynth1AudioProcessorEditor::BeastySynth1AudioProcessorEditor (BeastySynth1AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), presetPanel(p.getPresetManager()),
    osc1(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1MACRO", "OSC1TRANS", "OSC1GAIN", "OSC1PAN", "OSC1UNI", "OSC1WIDTH", "OSC1SPREAD"),
    osc2(audioProcessor, audioProcessor.apvts, "OSC2WAVETABLE", "OSC2MORPH", "OSC2TRANS", "OSC2GAIN", "OSC2PAN", "OSC2UNI", "OSC2WIDTH", "OSC2SPREAD"),
    ahdsr1(audioProcessor.apvts, "ATT1", "HOLD1", "DEC1", "SUS1", "REL1", "ATTSL1", "DECSL1", "RELSL1"),
    filter1(audioProcessor.apvts, "FILTERTYPE1", "DBOCT1", "FDRIVE1", "CUTOFF1", "RES1", "FENV1"),
    filter2(audioProcessor.apvts, "FILTERTYPE2", "DBOCT2", "FDRIVE2", "CUTOFF2", "RES2", "FENV2"),
    convDist1(audioProcessor, audioProcessor.apvts, "IRLOAD1", "CDWET1", "CDGAIN1"),
    reverb1(audioProcessor.apvts, "SIZE1", "DAMP1", "WIDTH1", "WET1", "DRY1"),
    ahdsr2(audioProcessor.apvts, "ATT2", "HOLD2", "DEC2", "SUS2", "REL2", "ATTSL1", "DECSL1", "RELSL1"),
    oscSub(audioProcessor.apvts, "OSCSUBWAVETYPE", "OSCSUBMACRO", "OSCSUBTRANS", "OSCSUBGAIN"),
    waveShaper1(audioProcessor.apvts, "WSINPUT1", "WSOUTPUT1", "WSTYPE1"),
    MSCompressor(audioProcessor.apvts, "MIDSGAIN", "SIDESGAIN")
{
    setSize (totalWidth, totalHeight);

    addAndMakeVisible(&presetPanel);
    addAndMakeVisible(&meterL);
    addAndMakeVisible(&meterR);
    startTimerHz(24);

    addAndMakeVisible(&osc1);
    addAndMakeVisible(&osc2);
    addAndMakeVisible(&ahdsr1);
    addAndMakeVisible(&filter1);
    addAndMakeVisible(&filter2);
    addAndMakeVisible(&convDist1);
    addAndMakeVisible(&ahdsr2);
    addAndMakeVisible(&oscSub);
    addAndMakeVisible(&waveShaper1);
    addAndMakeVisible(&reverb1);

    //addAndMakeVisible(MSCompressor);
}

BeastySynth1AudioProcessorEditor::~BeastySynth1AudioProcessorEditor()
{
}

//==============================================================================
void BeastySynth1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setFont (juce::FontOptions (10.0f));

    logo1 = juce::ImageCache::getFromMemory(BinaryData::Logo1_png, BinaryData::Logo1_pngSize);
    g.drawImageWithin(logo1, totalWidth - logo1.getWidth(), totalHeight - logo1.getHeight(), 
        logo1.getWidth(), logo1.getHeight(), juce::RectanglePlacement::stretchToFit);

}

void BeastySynth1AudioProcessorEditor::resized()
{
    // Preset manager
    presetPanel.setBounds(0, 0, getWidth() / 2, 40);

    // Meter
    auto meterX = presetPanel.getRight();
    auto meterY = 0;
    meterL.setBounds(meterX, meterY, getWidth() - meterX - 20, 15);
    meterR.setBounds(meterX, meterL.getBottom() + 5, getWidth() - meterX - 20, 15);

    // Draw Elements
    // First Row
    int yFirst = 41;
    osc1.setBounds(0, yFirst, 500, 150);
    filter1.setBounds(osc1.getRight(), yFirst, 250, 150);
    convDist1.setBounds(filter1.getRight(), yFirst, 200, 150);

    
    // Second Row
    int ySecond = osc1.getBottom();
    osc2.setBounds(0, ySecond, 500, 150);
    filter2.setBounds(osc2.getRight(), ySecond, 250, 150);
    reverb1.setBounds(filter2.getRight(), ySecond, 350, 150);

    // Third Row 
    int yThird = osc2.getBottom();
    ahdsr1.setBounds(0, yThird, 300, 110);
    ahdsr2.setBounds(ahdsr1.getRight(), yThird, 300, 110);

    // Bottom Row
    int yBot = ahdsr1.getBottom();
    oscSub.setBounds(0, yBot, 250, 150);
    waveShaper1.setBounds(oscSub.getRight(), yBot, 200, 150);

    //MSCompressor.setBounds(1000, 0, 200, 150);
}


void BeastySynth1AudioProcessorEditor::timerCallback()
{
    meterL.setMeterLevel(audioProcessor.getRmsValue(0));
    meterR.setMeterLevel(audioProcessor.getRmsValue(1));
    meterL.repaint();
    meterR.repaint();
}