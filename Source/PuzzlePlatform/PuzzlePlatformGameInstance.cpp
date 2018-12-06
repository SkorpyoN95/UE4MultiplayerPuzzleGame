// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include <Engine/Engine.h>
#include <GameFramework/PlayerController.h>
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer &ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuBPClass.Class != NULL) {
		MenuClass = MainMenuBPClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("Name of class: %s!"), *MenuClass->GetName());
	}
	
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class != NULL) {
		InGameMenuClass = InGameMenuBPClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("Name of class: %s!"), *InGameMenuClass->GetName());
	}
}

void UPuzzlePlatformGameInstance::Init(){
	UE_LOG(LogTemp, Warning, TEXT("GameInstance from init!"));
}

void UPuzzlePlatformGameInstance::LoadMenu(){
	if (!MenuClass)  return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!Menu) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::LoadInGameMenu() {
	if (!InGameMenuClass)  return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!Menu) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::Host(){
	if (Menu) {
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("HOSTING"));

	UWorld* World = GetWorld();
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& address) {
	if (Menu) {
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, *FString::Printf(TEXT("JOINING %s"), *address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController) {
		PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformGameInstance::LoadMainMenu(){
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController) {
		PlayerController->ClientTravel("/Game/MenuSystem/MenuLevel", ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformGameInstance::Exit() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController) {
		PlayerController->ConsoleCommand(TEXT("quit"));
	}
}
