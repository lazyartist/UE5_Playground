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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UnitTest_ParallelFor, "PG.ParallelFor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::CommandletContext)
bool UnitTest_ParallelFor::RunTest(FString const& Parameters)
{
	int32 MaxEntries = 100;
	ParallelFor( MaxEntries, [](int32 CurrIdx)
	{
		// 1개의 Task당 1.8초 가량 걸리고 100개라면 1800초.
		// 32쓰레드 CPU로 돌렸을 때 56(=1800/32)초 정도 걸림.
		// => 한 틱에 부분으로 나누어 독립적으로 실행할 수 있는 대량의 계산에 유용할 듯.
		FPrimeNumber PrimeNumber;
		PrimeNumber.Init(2, 10000);
		PrimeNumber.Find_AllPrimeNumbers();
		PrimeNumber.Print_AllPrimeNumbers(CurrIdx);
	} );

	// ParallelFor의 모든 태스크가 끝나고 아래 로그가 출력된다.
	UE_LOG(LogTemp, Log, TEXT("ParallelFor Done"));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UnitTest_TaskSystem, "PG.TaskSystem", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::CommandletContext)
bool UnitTest_TaskSystem::RunTest(FString const& Parameters)
{
	for (int i = 0; i < 100; ++i)
	{
		UE::Tasks::Launch(UE_SOURCE_LOCATION, [i]()
		{
			FPrimeNumber PrimeNumber;
			PrimeNumber.Init(2, 10000);
			PrimeNumber.Find_AllPrimeNumbers();
			PrimeNumber.Print_AllPrimeNumbers(i);
		});
	}
	
	// ParallelFor의 모든 태스크가 끝나고 아래 로그가 출력된다.
	UE_LOG(LogTemp, Log, TEXT("TaskSystem Done"));

	return true;
}
