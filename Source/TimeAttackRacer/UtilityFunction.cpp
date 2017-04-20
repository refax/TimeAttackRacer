// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackRacer.h"
#include "UtilityFunction.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"

UtilityFunction::UtilityFunction()
{
}

UtilityFunction::~UtilityFunction()
{
}


FString UtilityFunction::TimeToText(float Time)
{
	FString result;

	//Evalute minutes
	int32 minutes = FGenericPlatformMath::Floor(Time / 60.0f);
	if (minutes < 10)
	{
		result.Append("0");
	}
	result.Append(FString::FromInt(minutes)).Append(":");
	//Seconds
	int32_t seconds = FGenericPlatformMath::Fmod(Time, 60.0f);
	if (seconds < 10)
	{
		result.Append("0");
	}
	result.Append(FString::FromInt(seconds)).Append(":");

	//Milliseconds
	int32_t millisec = FGenericPlatformMath::Floor((Time - FGenericPlatformMath::Floor(Time)) * 1000);
	if (millisec < 10)
	{
		result.Append("0");
	}
	result.Append(FString::FromInt(millisec));

	return result;
}
