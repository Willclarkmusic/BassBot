/*
  ==============================================================================

    ADSR1Data.cpp
    Created: 14 Aug 2024 9:41:36pm
    Author:  BB8

  ==============================================================================
*/

#include "ADSR1Data.h"

void ADSR1Data::updateADSR1(const float attack1, const float decay1, const float sustain1, const float release1)
{
    adsr1Params.attack = attack1;
    adsr1Params.decay = decay1;
    adsr1Params.sustain = sustain1;
    adsr1Params.release = release1;
    setParameters(adsr1Params);
}