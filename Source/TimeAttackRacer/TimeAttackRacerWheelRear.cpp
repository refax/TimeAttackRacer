// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TimeAttackRacer.h"
#include "TimeAttackRacerWheelRear.h"
#include "TireConfig.h"

UTimeAttackRacerWheelRear::UTimeAttackRacerWheelRear()
{
	ShapeRadius = 18.0f;
	ShapeWidth = 15.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 0.f;

	// Setup suspension forces
	SuspensionForceOffset = 0;//-4.0f;
	SuspensionMaxRaise = 20.0f;//8.0f;
	SuspensionMaxDrop = 40.0f;//12.0f;
	SuspensionNaturalFrequency = 10.0f;
	SuspensionDampingRatio = 1.1f;

	// Find the tire object and set the data for it
	static ConstructorHelpers::FObjectFinder<UTireConfig> TireData(TEXT("/Game/VehicleAdv/Vehicle/WheelData/Vehicle_BackTireConfig.Vehicle_BackTireConfig"));
	TireConfig = TireData.Object;
}
