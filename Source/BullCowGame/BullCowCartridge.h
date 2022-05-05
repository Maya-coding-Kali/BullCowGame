// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"
struct FbullCowCount
{
	int32 Bulls;
	int32 Cows;
};
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& PlayerInput) override;
	void SetUpGame();
	void LivesFunction();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Guess) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordsList)const;
	FbullCowCount GetBullCows(const FString& Guess) const;
	void Level();
	// Your declarations go below!
private:
	bool bGameOver;
	FString HiddenWord;
	int32 Lives;
	TArray<FString> Words;
	TArray<FString> Isograms;

};
