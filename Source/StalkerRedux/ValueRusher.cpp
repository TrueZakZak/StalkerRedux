// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "ValueRusher.h"

UValueRusher::UValueRusher(float DefaultValue)
	: TotalTimeSec(0.5)
{
	Init(DefaultValue);
}

UValueRusher::~UValueRusher()
{
}

void UValueRusher::Init(float DefaultValue)
{
	CurrentValue = DefaultValue;
	StartingValue = DefaultValue;
	TargetValue = DefaultValue;
}

void UValueRusher::RushTo(float NewValue)
{
	LerpTime = 0.0f;
	TotalTimeSec = 0.15;

	StartingValue = CurrentValue;
	TargetValue = NewValue;
}

void UValueRusher::RushBack(float NewValue)
{
	TotalTimeSec = 0.5f * (LerpTime / 0.5f);
	LerpTime = 0.0f;

	StartingValue = CurrentValue;
	TargetValue = NewValue;
}

void UValueRusher::Update(float DeltaTime)
{
	if (LerpTime >= TotalTimeSec)
	{
		return;
	}

	LerpTime += DeltaTime;

	float T = LerpTime / TotalTimeSec;
	CurrentValue = FMath::Lerp(StartingValue, TargetValue, T);
}
