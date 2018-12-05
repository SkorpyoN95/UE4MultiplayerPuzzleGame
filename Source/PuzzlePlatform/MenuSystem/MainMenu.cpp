// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Components/Button.h>


void UMainMenu::Setup(void){
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly Input;
	Input.SetWidgetToFocus(this->TakeWidget());
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(Input);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::Teardown(void){
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly Input;

	PlayerController->SetInputMode(Input);
	PlayerController->bShowMouseCursor = false;

	this->RemoveFromViewport();
}

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success || !Host || !Join) return false;

	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* interface) {
	MenuInterface = interface;
}

void UMainMenu::HostServer(){
	if (!MenuInterface) return; 
	MenuInterface->Host();
}

void UMainMenu::JoinServer() {
	UE_LOG(LogTemp, Warning, TEXT("I'm about to join to server!"));
}
