// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STD_Slate_Widget.h"
#include "TD_HUD_withSlate.generated.h"

/**
 * 
 */
UCLASS()
class TDGAME_PROJECT_API ATD_HUD_withSlate : public AHUD
{
	GENERATED_BODY()
public:
	//++reference to an SCompoudWidget , TSharedPtr adds to the refcount of MyUIWidget
	//MyUIWidget will not self-destruct as long as refcount >0 .refcount will be (refcout-1 ) if Hud is destroyed
	TSharedPtr<STD_Slate_Widget> MyUIWidget;
	virtual void BeginPlay() override;

protected:
	/*virtual void BeginPlay() override;
	TSharedPtr<STD_Slate_Widget> UIWidget;*/
	
	
	
};
