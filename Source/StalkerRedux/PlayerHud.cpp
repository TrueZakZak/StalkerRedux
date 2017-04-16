// Fill out your copyright notice in the Description page of Project Settings.

#include "StalkerRedux.h"
#include "PlayerHud.h"

void APlayerHud::DrawHUD()
{
	Super::DrawHUD();

	DrawCursor();
}

void APlayerHud::DrawCursor()
{
	if (CursorTexture)
	{
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CursorDrawPosition(Center.X - CursorTexture->GetSurfaceWidth() * 0.5f, Center.Y - CursorTexture->GetSurfaceHeight() * 0.5f);

		FCanvasTileItem TileItem(CursorDrawPosition, CursorTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;

		Canvas->DrawItem(TileItem);
	}
}
