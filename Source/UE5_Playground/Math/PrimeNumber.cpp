// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimeNumber.h"

#include "Kismet/GameplayStatics.h"


FPrimeNumber::FPrimeNumber()
{
}

FPrimeNumber::~FPrimeNumber()
{
}

void FPrimeNumber::Init(const int32 In_StartPrimeNumber, const int32 In_LimitPrimeNumber)
{
	mLastPrimeNumber = In_StartPrimeNumber;
	mLimitPrimeNumber = In_LimitPrimeNumber;

	mPrimeNumbers.Empty();
	mPrimeNumbers.Reserve(In_LimitPrimeNumber);
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

		++TargetPrimeNumber;
		if (mLimitPrimeNumber < TargetPrimeNumber)
		{
			UE_LOG(LogTemp, Log, TEXT("PrimeNumber is reached limit(%d)(CalcCount: %d)"), mLimitPrimeNumber, mCalcCount);
			break;
		}
	}

	UGameplayStatics::GetAccurateRealTime(Seconds, PartialSeconds);
	FTimespan EndTime = FTimespan(0, 0, 0, Seconds, PartialSeconds * 1000000000);
	mSpendTime = EndTime - StartTime;
}

void FPrimeNumber::Print_AllPrimeNumbers()
{
	FString PrimeNumbersAsString;

	for (const auto& PrimeNumber : mPrimeNumbers)
	{
		PrimeNumbersAsString.Append(TEXT(", "));
		PrimeNumbersAsString.AppendInt(PrimeNumber);
	}

	UE_LOG(LogTemp, Log, TEXT("PrimeNumbers : %s"), *PrimeNumbersAsString);
	UE_LOG(LogTemp, Log, TEXT("mCalcCount : %d"), mCalcCount);

	FDateTime d = FDateTime(mSpendTime.GetTicks());
	UE_LOG(LogTemp, Log, TEXT("Elapsed time is %dm %02ds %03dmm, tick is %lld"), d.GetMinute(), d.GetSecond(), d.GetMillisecond(), mSpendTime.GetTicks());
}