// Fill out your copyright notice in the Description page of Project Settings.

#include "TD_HUD_withSlate.h"
#include "STD_Slate_Widget.h"
#include "Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

void ATD_HUD_withSlate::BeginPlay()
{
	// So far only TSharePtr<SmyUIWidget> has been created , now create the
	//actual object 
	//create a SMyUIWidget on heap , our MyUIWidget
	//Shared pointer provides handle to object 
	//widget will not self destruct unless the HUD's SharedPtr (and all other SharedPtrs)
	//are destroyed first. 
	MyUIWidget = SNew(STD_Slate_Widget).OwnerHUDArg(this);

	//Pass our viewport a weak ptr to our widget 
	//viewport weak ptr will not give Viewport ownership of widget 
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));
	
	MyUIWidget->SetVisibility(EVisibility::Visible);


}





