/*
  ==============================================================================

    PresetManager.cpp
    Created: 31 Aug 2024 1:45:57pm
    Author:  BB8

  ==============================================================================
*/

#include "PresetManager.h"

namespace Service
{
    const juce::File PresetManager::defaultDirectory{ juce::File::getSpecialLocation(
        juce::File::SpecialLocationType::userDocumentsDirectory)
        .getChildFile(ProjectInfo::companyName)
        .getChildFile(ProjectInfo::projectName) };  // PresetDirectory

    const juce::String PresetManager::extension{ "bb" };    


    PresetManager::PresetManager(juce::AudioProcessorValueTreeState& apvts) :
        valueTreeState(apvts)
    {
        if (!defaultDirectory.exists())
        {
            const auto result = defaultDirectory.createDirectory();
            if (result.failed())
            {
                DBG("Could not create preset directory: " + result.getErrorMessage());
                jassertfalse;
            }
        }
    }

    void PresetManager::savePreset(const juce::String& presetName)
    {
        if (presetName.isEmpty())
            return;

        const auto xml = valueTreeState.copyState().createXml();
        const auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);

        if (!xml->writeTo(presetFile))
        {
            DBG("Could not create preset file: " + presetFile.getFullPathName());
            jassertfalse;
        }
        currentPreset = presetName;
    }

    void PresetManager::deletePreset(const juce::String& presetName)
    {
        if (presetName.isEmpty())
            return;

        auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
        if (!presetFile.existsAsFile())
        {
            DBG("Preset File " + presetFile.getFullPathName() + " does not exist");
            jassertfalse;
            return;
        }

        if (!presetFile.deleteFile())
        {
            DBG("PresetFile " + presetFile.getFullPathName() + " could not be deleted");
            jassertfalse;
            return;
        }

        currentPreset = "";
    }

    void PresetManager::loadPreset(const juce::String& presetName)
    {
        if (presetName.isEmpty())
            return;

        auto presetFile = defaultDirectory.getChildFile(presetName + "." + extension);
        if (!presetFile.existsAsFile())
        {
            DBG("Preset File " + presetFile.getFullPathName() + " does not exist");
            jassertfalse;
            return;
        }

        juce::XmlDocument xmlDocument{ presetFile };
        const auto valueTreeToLoad = juce::ValueTree::fromXml(*xmlDocument.getDocumentElement());

        valueTreeState.replaceState(valueTreeToLoad);
        currentPreset = presetName;

    }

    int PresetManager::loadNextPreset()
    {
        const auto allPresets = getAllPresets();
        if (allPresets.isEmpty())
            return -1;

        const auto currentIndex = allPresets.indexOf(currentPreset);
        const auto nextIndex = currentIndex + 1 > (allPresets.size() - 1) ? 0 : currentIndex + 1;

        loadPreset(allPresets.getReference(nextIndex));
        return nextIndex;
    }

    int PresetManager::loadPrevPreset()
    {
        const auto allPresets = getAllPresets();
        if (allPresets.isEmpty())
            return -1;

        const auto currentIndex = allPresets.indexOf(currentPreset);
        const auto prevIndex = currentIndex - 1 < 0 ? allPresets.size() - 1 : currentIndex - 1;

        loadPreset(allPresets.getReference(prevIndex));
        return prevIndex;
    }

    juce::StringArray PresetManager::getAllPresets() const
    {
        juce::StringArray presets;
        const auto fileArray = defaultDirectory.findChildFiles(
            juce::File::TypesOfFileToFind::findFiles, false, "*." + extension);

        for (const auto& file : fileArray)
        {
            presets.add(file.getFileNameWithoutExtension());
        }
        return presets;
    }

    juce::String PresetManager::getCurrentPreset() const
    {
        return currentPreset;
    }
}