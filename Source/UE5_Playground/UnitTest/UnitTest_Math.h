#pragma once

#include "CoreMinimal.h"
#include "UE5_Playground/Math/PrimeNumber.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UnitTest_PrimeNumber, "PG.PrimeNumber", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::CommandletContext)

bool UnitTest_PrimeNumber::RunTest(FString const& Parameters)
{
	FPrimeNumber PrimeNumber;
	PrimeNumber.Init(2, 10000);
	PrimeNumber.Find_AllPrimeNumbers();
	// PrimeNumber.Print_AllPrimeNumbers();

	UE_LOG(LogTemp, Log, TEXT("Parameters : %s"), *FString::Join(Parameters, (TEXT(","))));

	return true;
}
