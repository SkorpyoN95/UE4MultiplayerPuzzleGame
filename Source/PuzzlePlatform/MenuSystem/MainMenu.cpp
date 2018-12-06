// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/EditableTextBox.h>

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success || !HostButton || !JoinMenuButton || !JoinButton || !CancelButton || !ExitButton) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::GoBack);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitToDesktop);

	return true;
}

void UMainMenu::HostServer(){
	if (!MenuInterface) return; 
	MenuInterface->Host();
}

void UMainMenu::JoinServer(){
	if (!MenuInterface || !IPAddressBox) return;
	MenuInterface->Join(IPAddressBox->GetText().ToString());
}

void UMainMenu::OpenJoinMenu() {
	if (!MenuSwitcher || !JoinMenu) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::GoBack() {
	if (!MenuSwitcher || !BaseMenu) return;

	MenuSwitcher->SetActiveWidget(BaseMenu);
}

void UMainMenu::ExitToDesktop() {
	if (!MenuInterface) return;
	MenuInterface->Exit();
}
