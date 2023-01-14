// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimeNumber.h"

#include "Kismet/GameplayStatics.h"


FPrimeNumber::FPrimeNumber()
{
}

FPrimeNumber::~FPrimeNumber()
{
}

void FPrimeNumber::Init(const int32 In_StartPrimeNumber, const int32 In_LimitPrimeNumberCount)
{
	mLastPrimeNumber = In_StartPrimeNumber;
	mLimitPrimeNumberCount = In_LimitPrimeNumberCount;

	mPrimeNumbers.Empty();
	mPrimeNumbers.Reserve(mLimitPrimeNumberCount);
}

void FPrimeNumber::Find_AllPrimeNumbers()
{
	int32 Seconds;
	double PartialSeconds;
	UGameplayStatics::GetAccurateRealTime(Seconds, PartialSeconds);
	FTimespan StartTime = FTimespan(0, 0, 0, Seconds, PartialSeconds * 1000000000);
	
	int32 TargetPrimeNumber = mLastPrimeNumber + 1;

	while (true)
	{
		while (true)
		{
			int32 DivideNumber = 2;
			for (; DivideNumber < TargetPrimeNumber; ++DivideNumber)
			{
				++mCalcCount;

				if (0 == TargetPrimeNumber % DivideNumber)
				{
					break;
				}
			}

			if (TargetPrimeNumber == DivideNumber)
			{
				// Succeed to find
				mLastPrimeNumber = TargetPrimeNumber;
				mPrimeNumbers.Add(mLastPrimeNumber);
			}
			break;
		}

		if (mPrimeNumbers.Num() > mLimitPrimeNumberCount)
		{
			UE_LOG(LogTemp, Log, TEXT("PrimeNumberCount is reached limit(%d)(CalcCount: %lld)"), mLimitPrimeNumberCount, mCalcCount);
			break;
		}
		
		++TargetPrimeNumber;
	}

	UGameplayStatics::GetAccurateRealTime(Seconds, PartialSeconds);
	FTimespan EndTime = FTimespan(0, 0, 0, Seconds, PartialSeconds * 1000000000);
	mSpendTime = EndTime - StartTime;
}

void FPrimeNumber::Print_AllPrimeNumbers(const int32& In_Id)
{
	// FString PrimeNumbersAsString;
	//
	// for (const auto& PrimeNumber : mPrimeNumbers)
	// {
	// 	PrimeNumbersAsString.Append(TEXT(", "));
	// 	PrimeNumbersAsString.AppendInt(PrimeNumber);
	// }
	// UE_LOG(LogTemp, Log, TEXT("PrimeNumbers : %s"), *PrimeNumbersAsString);
	
	FDateTime SpendDateTime = FDateTime(mSpendTime.GetTicks());
	UE_LOG(LogTemp, Log, TEXT("In_Id(%d), mPrimeNumbers.Num(%d), mCalcCount(%lld), ElapsedTime(%dm %02ds %03dmm), Tick(%lld)"), In_Id, mPrimeNumbers.Num(), mCalcCount, SpendDateTime.GetMinute(), SpendDateTime.GetSecond(), SpendDateTime.GetMillisecond(), mSpendTime.GetTicks());
}
