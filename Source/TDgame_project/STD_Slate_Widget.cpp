// Fill out your copyright notice in the Description page of Project Settings.

#include "STD_Slate_Widget.h"
#include "SlateOptMacros.h"
#include "SWidget.h"
#include "SButton.h"
#include "SOverlay.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/SlateCore/Public/Rendering/DrawElements.h"
#include "STextBlock.h"
#define LOCTEXT_NAMESPACE "STD_HUD_withSlate"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STD_Slate_Widget::Construct(const FArguments& InArgs)
{
	Size = (100);
	ButtonPaddingSize.Bind(this, &STD_Slate_Widget::GetButtonPaddingSize);
	OwnerHUD = InArgs._OwnerHUDArg;
	ChildSlot.VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SOverlay) 
			
			+ SOverlay::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Center)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Red)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 60))
					.Text(LOCTEXT("HelloSlateText","Hello,Slate!"))
				]
			+ SOverlay::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Right)
				.Padding(100,700,100,10)
				[
					SNew(SButton)
					.ContentPadding(ButtonPaddingSize)
					.OnClicked(this,&STD_Slate_Widget::DebugMessenge)
					[
						SNew(STextBlock)
						.ShadowColorAndOpacity(FLinearColor::Black)
						.ColorAndOpacity(FLinearColor::Red)
						.ShadowOffset(FIntPoint(-1, 1))
						.Font(FSlateFontInfo("Veranda", 100))
						.Text(LOCTEXT("ButtonLabel", "Button!"))
					]
				]		
			+ SOverlay::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Left)
				.Padding(100, 10, 100, 600)
				[
					SNew(SButton)
					.ContentPadding(ButtonPaddingSize)
					.OnClicked(this, &STD_Slate_Widget::DebugMessenge)
					[
						SNew(STextBlock)
						.ShadowColorAndOpacity(FLinearColor::Black)
						.ColorAndOpacity(FLinearColor::Red)
						.ShadowOffset(FIntPoint(-1, 1))
						.Font(FSlateFontInfo("Veranda", 100))
						.Text(LOCTEXT("ButtonLabel", "Button!"))
					]
				]

		];
}
FMargin STD_Slate_Widget::GetButtonPaddingSize() const
{
	FMargin LTRB = Size;
	return FMargin(LTRB);
}
FReply STD_Slate_Widget::DebugMessenge()
{
	UpdateButtonSize();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("ButtonPressed %f"),Size.Bottom));
	
	return FReply::Handled();
}
void STD_Slate_Widget::UpdateButtonSize()
{
	Size.Left +=100;
}
#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

