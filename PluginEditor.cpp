#include "PluginEditor.h"

JUCEVSTTemplateAudioProcessorEditor::JUCEVSTTemplateAudioProcessorEditor(JUCEVSTTemplateAudioProcessor& p)
    : AudioProcessorEditor(&p), proc(p)
{
    addAndMakeVisible(oscMixSlider);
    oscMixSlider.setSliderStyle(juce::Slider::Rotary);
    oscMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        proc.parameters, "oscMix", oscMixSlider));

    addAndMakeVisible(filterCutoffSlider);
    filterCutoffSlider.setSliderStyle(juce::Slider::Rotary);
    filterCutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        proc.parameters, "filterCutoff", filterCutoffSlider));

    setSize(400, 300);
}

void JUCEVSTTemplateAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::cyan);
    g.setFont(24.0f);
    g.drawText("JUCE VST Template", getLocalBounds(), juce::Justification::centredTop);
}

void JUCEVSTTemplateAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    oscMixSlider.setBounds(area.removeFromLeft(180).reduced(10));
    filterCutoffSlider.setBounds(area.reduced(10));
}