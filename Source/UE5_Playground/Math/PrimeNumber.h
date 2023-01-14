// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimeNumber.generated.h"

USTRUCT()
struct FPrimeNumber
{
	GENERATED_BODY()
	
public:
	FPrimeNumber();
	~FPrimeNumber();

	void Init(const int32 In_StartPrimeNumber, const int32 In_LimitPrimeNumberCount);

	void Find_AllPrimeNumbers();

	void Print_AllPrimeNumbers();

private:
	int32 mLimitPrimeNumberCount = 100000;

	int32 mLastPrimeNumber = 1;

	TArray<int32> mPrimeNumbers;

	int64 mCalcCount = 0;

	FTimespan mSpendTime;
};
