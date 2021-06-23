// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/LoadingInstance.h"
#include "MoviePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void ULoadingInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this,&ULoadingInstance::StartLoadingScreen);
}

void ULoadingInstance::StartLoadingScreen(const FString& levelName)
{
	if (loadingWidgetClass != nullptr) {
		auto widget =
			CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), loadingWidgetClass.Get());

		if (widget != nullptr) {

			FLoadingScreenAttributes LoadingScreen;

			LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			LoadingScreen.WidgetLoadingScreen = widget->TakeWidget();
			LoadingScreen.MinimumLoadingScreenDisplayTime = 10.f;
			LoadingScreen.MoviePaths.Add("Blurred Distance_1080p");
			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);

		}
	}
}
