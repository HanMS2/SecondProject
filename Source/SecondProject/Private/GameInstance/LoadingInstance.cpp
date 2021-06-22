// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/LoadingInstance.h"
#include "MoviePlayer.h"

void ULoadingInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this,&ULoadingInstance::StartLoadingScreen);
}

void ULoadingInstance::StartLoadingScreen(const FString& levelName)
{
	if (loadingWidgetClass != nullptr)
	{
		auto widget = CreateWidget<UUserWidget>(GetWorld(),loadingWidgetClass.Get());
	
		if (widget != nullptr) 
		{
			FLoadingScreenAttributes loadingScreen;
			loadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			loadingScreen.MinimumLoadingScreenDisplayTime = 10.f;
			loadingScreen.WidgetLoadingScreen = widget->TakeWidget();

			GetMoviePlayer()->SetupLoadingScreen(loadingScreen);
		}
	}
}
