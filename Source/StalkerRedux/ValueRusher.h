// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class STALKERREDUX_API UValueRusher
{
public:
	UValueRusher(float DefaultValue = 0.0f);
	~UValueRusher();

	void Init(float DefaultValue);

	void RushTo(float NewValue);
	void RushBack(float NewValue);
	void Update(float DeltaTime);

	inline float GetCurrentValue() const { return CurrentValue; }

private:
	float CurrentValue;
	float StartingValue;
	float TargetValue;

	float LerpTime;
	float TotalTimeSec;
};
