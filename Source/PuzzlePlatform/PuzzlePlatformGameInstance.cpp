// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include <Engine/Engine.h>
#include <GameFramework/PlayerController.h>

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer &ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuBPClass.Class != NULL) {
		MenuClass = MainMenuBPClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("Name of class: %s!"), *MenuClass->GetName());
	}
	
}

void UPuzzlePlatformGameInstance::Init(){
	UE_LOG(LogTemp, Warning, TEXT("GameInstance from init!"));
}

void UPuzzlePlatformGameInstance::LoadMenu(){
	UUserWidget* Menu;
	if (!MenuClass)  return;

	Menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!Menu) return;

	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;
		
	FInputModeUIOnly Input;
	Input.SetWidgetToFocus(Menu->TakeWidget());
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(Input);
	PlayerController->bShowMouseCursor = true;
}

void UPuzzlePlatformGameInstance::Host(){
	UEngine* Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("HOSTING"));

	UWorld* World = GetWorld();
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& address) {
	UEngine* Engine = GetEngine();
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, *FString::Printf(TEXT("JOINING %s"), *address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController) {
		PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
	}
}
