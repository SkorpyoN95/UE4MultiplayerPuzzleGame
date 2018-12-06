// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"


void UMenuWidget::Setup(void){
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

void UMenuWidget::Teardown(void){
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly Input;

	PlayerController->SetInputMode(Input);
	PlayerController->bShowMouseCursor = false;

	this->RemoveFromViewport();
}

void UMenuWidget::SetMenuInterface(IMenuInterface* interface) {
	MenuInterface = interface;
}
