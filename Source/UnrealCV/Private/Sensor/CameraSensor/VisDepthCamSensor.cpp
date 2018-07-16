// Weichao Qiu @ 2017
#include "VisDepthCamSensor.h"

UVisDepthCamSensor::UVisDepthCamSensor(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	FString VisDepthPPMaterialPath = TEXT("Material'/UnrealCV/SceneDepthWorldUnits.SceneDepthWorldUnits'");
	ConstructorHelpers::FObjectFinder<UMaterial> Material(*VisDepthPPMaterialPath);

	SetPostProcessMaterial(Material.Object);
}

void UVisDepthCamSensor::CaptureDepth(TArray<FFloat16Color>& DepthData, int& Width, int& Height)
{
	// this->CaptureScene(); // To check whether this update is real time and how fast it is
	Width = this->TextureTarget->SizeX, Height = TextureTarget->SizeY;
	DepthData.AddZeroed(Width * Height);
	FTextureRenderTargetResource* RenderTargetResource = this->TextureTarget->GameThread_GetRenderTargetResource();
	RenderTargetResource->ReadFloat16Pixels(DepthData);
}

void UVisDepthCamSensor::SetupRenderTarget()
{
	bool bUseLinearGamma = true;
	// TODO: Check whether InitAutoFormat = Float + UseLinearGamma?
	TextureTarget->InitCustomFormat(FilmWidth, FilmHeight, EPixelFormat::PF_FloatRGBA, bUseLinearGamma);
}

