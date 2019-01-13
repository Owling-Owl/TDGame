// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SUserWidget.h"


/**
 * 
 */
class TDGAME_PROJECT_API STD_Slate_Widget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STD_Slate_Widget){}
	SLATE_ARGUMENT(TWeakObjectPtr<class ATD_HUD_withSlate>, OwnerHUDArg);
	SLATE_END_ARGS();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
private:

	// ++ Pointer to our parent HUD. To make sure HUD's lifetime is controlled elsewhere, use "weak" ptr. // ++ HUD has a "strong" pointer to Widget, circular ownership would prevent/break self-destruction of hud/widget (cause a memory leak). 
	TWeakObjectPtr<class ATD_HUD_withSlate> OwnerHUD;
	TSharedPtr<SButton>		RefreshButton;
	TSharedPtr<STextBlock>	RefreshButtonText;
	TSharedPtr<SButton>		ClearTileButton;
	TAttribute<FMargin>		ButtonPaddingSize;
	FMargin GetButtonPaddingSize() const;
	FMargin Size;
	FReply DebugMessenge();

	void UpdateButtonSize();
	//int SCompoundWidget::OnPaint() override;


};
