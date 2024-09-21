/*
  ==============================================================================

    PresetComponent.h
    Created: 31 Aug 2024 5:00:50pm
    Author:  BB8

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace PresetComponent
{
    class PresetPanel : public juce::Component, juce::Button::Listener, juce::ComboBox::Listener
    {       
    public:
        PresetPanel(Service::PresetManager& pm) : presetManager(pm)
        {
            configureButton(saveButton, "Save");
            configureButton(deleteButton, "Delete");
            configureButton(previousButton, "Prev");
            configureButton(nextButton, "Next");

            // Configure Preset Combo Box
            presetList.setTextWhenNothingSelected("No Preset Selected");
            presetList.setMouseCursor(juce::MouseCursor::PointingHandCursor);
            addAndMakeVisible(presetList);
            presetList.addListener(this);

            loadPresetList();
        }

        ~PresetPanel()
        {
            saveButton.removeListener(this);
            deleteButton.removeListener(this);
            previousButton.removeListener(this);
            nextButton.removeListener(this);
            presetList.removeListener(this);
        }
        void paint(juce::Graphics& g) override
        {

        }

        void resized() override
        {
            const auto container = getLocalBounds().reduced(5);
            auto bounds = container;
            //
            saveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(5));
            previousButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(5));
            presetList.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.4f)).reduced(5));
            nextButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(5));
            deleteButton.setBounds(bounds.reduced(5));

        }

    private:
        void buttonClicked(juce::Button* button) override 
        {
            if (button == &saveButton)
            {
                fileChooser = std::make_unique<juce::FileChooser>("Please enther the name of the preset",                    
                    Service::PresetManager::defaultDirectory, "*." + Service::PresetManager::extension );

                fileChooser->launchAsync(juce::FileBrowserComponent::saveMode, [&](const juce::FileChooser& chooser)
                    {
                        const auto resultFile = chooser.getResult();
                        presetManager.savePreset(resultFile.getFileNameWithoutExtension());
                        loadPresetList();
                    });
            }
            if (button == &previousButton)
            {
                const auto index = presetManager.loadPrevPreset();
                presetList.setSelectedItemIndex(index, juce::dontSendNotification);
            }
            if (button == &nextButton)
            {
                const auto index = presetManager.loadNextPreset();
                presetList.setSelectedItemIndex(index, juce::dontSendNotification);
            }
            if (button == &deleteButton)
            {
                presetManager.deletePreset(presetManager.getCurrentPreset());
                loadPresetList();
            }
        }

        void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override 
        {
            if (comboBoxThatHasChanged == &presetList)
            {
                presetManager.loadPreset(presetList.getItemText(presetList.getSelectedItemIndex()));
            }
        }

        void configureButton(juce::Button& button, const juce::String& buttonText)
        {
            button.setButtonText(buttonText);
            button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
            addAndMakeVisible(&button);
            button.addListener(this);
        }

        void loadPresetList()
        {
            // Populate Preset List
            presetList.clear(juce::dontSendNotification);
            const auto allPresets = presetManager.getAllPresets();
            const auto currentPreset = presetManager.getCurrentPreset();
            presetList.addItemList(allPresets, 1);
            presetList.setSelectedItemIndex(allPresets.indexOf(currentPreset), juce::dontSendNotification);
        }

        Service::PresetManager& presetManager;

        juce::TextButton saveButton, deleteButton, previousButton, nextButton;
        juce::ComboBox presetList;
        
        std::unique_ptr<juce::FileChooser> fileChooser;
                     
        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetPanel)
    };
}

