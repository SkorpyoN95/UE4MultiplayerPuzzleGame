// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include <Components/Button.h>

bool UInGameMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success || !ResumeButton || !QuitButton) return false;

	ResumeButton->OnClicked.AddDynamic(this, &UInGameMenu::Resume);
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	return true;
}

void UInGameMenu::QuitPressed() {
	if (!MenuInterface) return;
	Teardown();
	MenuInterface->LoadMainMenu();
}

void UInGameMenu::Resume() {
	Teardown();
}
