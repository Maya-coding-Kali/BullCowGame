// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include <time.h>
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Level();
    SetUpGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    /*if game is over clear screen and setTheGame back up
     else Check PlayerGuess*/
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
        return;
    }
    ProcessGuess(PlayerInput);
}
void UBullCowCartridge::SetUpGame()
{
   
    PrintLine(TEXT("Welcome to Bull Cows!"));
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    Isograms = GetValidWords(Words);
    PrintLine(TEXT("%i"), Isograms.Num());
    int32 RandoNum = FMath::RandRange(0, Isograms.Num() - 1);
    HiddenWord = Isograms[RandoNum];
    PrintLine(TEXT("Your word is  %s"), *HiddenWord);
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your Guess and \npress enter to continue"));
    PrintLine(TEXT("You have %i Live Left"), Lives);
}
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordsList) const
{
    TArray<FString> ValidWords;
    for (FString WordSearchFilter : WordsList)
    {
        if (WordSearchFilter.Len() >= 4 && WordSearchFilter.Len() <= 8 && IsIsogram(WordSearchFilter))
        {
            ValidWords.Emplace(WordSearchFilter);
        }
    }
    return ValidWords;
}
void UBullCowCartridge::EndGame()
{

    bGameOver = true;
    PrintLine(TEXT("press enter to play again"));

}

void UBullCowCartridge::LivesFunction()
{
    --Lives;
    if (Lives == 1)
    {
        PrintLine(TEXT("You have %i Life Left"), Lives);
    }
    else
    {
        PrintLine(TEXT("You have %i Lives Left"), Lives);
    }
}
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You won!!"));
        EndGame();
        return;
    }
    PrintLine(TEXT("Wrong Guess!!"));   
    if (HiddenWord.Len() != Guess.Len())
    {
        LivesFunction();
        PrintLine(TEXT("The word is %i letters long"), HiddenWord.Len());
        return;
    }   
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Not an isogram"));
    }
    else
    {
        PrintLine(TEXT("No repeating letters found"));
    }
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You lose"));
        PrintLine(TEXT("The Hidden Word Was: %s"), *HiddenWord);
        EndGame();
    }
    else if (Guess.Len() == HiddenWord.Len())
    {
       FbullCowCount Answer = GetBullCows(Guess);
       PrintLine(TEXT("You have %i Bulls and %i Cows"), Answer.Bulls, Answer.Cows);

    }
}
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[j] == Word[i])
            {
                return false;
            }
        }
    }
    return true;
}
FbullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FbullCowCount Count;
    Count.Bulls = 0;
    Count.Cows = 0;
    //if the index of Guess is the same as index hidden, BullCount++
    // If not a bull was it a cow? if yes CowCount++
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < Guess.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}
void UBullCowCartridge::Level()
{
    PrintLine(TEXT("What Level Would You Like To Play?"));
    PrintLine(TEXT("Press 1, 2, 3"));
    
}
