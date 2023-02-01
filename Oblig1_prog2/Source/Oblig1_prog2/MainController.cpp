// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMainController::AMainController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Spheres.Init(NULL, 9);
	Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Spheres[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Spheres[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Spheres[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh4"));
	Spheres[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh5"));
	Spheres[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh6"));
	Spheres[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh7"));
	Spheres[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh8"));
	Spheres[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh9"));

	RootComponent = Spheres[4];
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	for (int i = 0; i < 9; i++)
	{
		if (i != 4)
		{
			Spheres[i]->SetupAttachment(GetRootComponent());
		}
		Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
	}



	Red = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	Blue = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));
	White = CreateDefaultSubobject<UMaterial>(TEXT("WhiteMaterial"));


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1000.f;

	// Attach the Camera to SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);



	Spheres[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	Spheres[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	Spheres[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	Spheres[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	Spheres[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Spheres[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Spheres[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	Spheres[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	Spheres[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));

	TurnCounter = 0;
	win = false;
	SphereStatus.Init(NULL, 9);
	SphereC.Init(0, 9);

}

// Called when the game starts or when spawned
void AMainController::BeginPlay()
{
	Super::BeginPlay();
		
	for (int i = 0; i < 9; i++)
	{
		Spheres[i]->SetMaterial(0, White);
	}
}

// Called every frame
void AMainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("1", IE_Pressed, this, &AMainController::OnePressed);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &AMainController::TwoPressed);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &AMainController::ThreePressed);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &AMainController::FourPressed);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &AMainController::FivePressed);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &AMainController::SixPressed);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &AMainController::SevenPressed);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &AMainController::EightPressed);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &AMainController::NinePressed);

}

void AMainController::OnePressed()
{
	TurnController(0);

}

void AMainController::TwoPressed()
{
	TurnController(1);
}

void AMainController::ThreePressed()
{
	TurnController(2);
}

void AMainController::FourPressed()
{
	TurnController(3);
}

void AMainController::FivePressed()
{
	TurnController(4);
}

void AMainController::SixPressed()
{
	TurnController(5);
}

void AMainController::SevenPressed()
{
	TurnController(6);
}

void AMainController::EightPressed()
{
	TurnController(7);
}

void AMainController::NinePressed()
{
	TurnController(8);
}

void AMainController::CheckForWin() {
	if (TurnCounter>2)
	{
		if (SphereC[0] == 1 && SphereC[1] == 1 && SphereC[2] == 1 ||
			SphereC[0] == 2 && SphereC[1] == 2 && SphereC[2] == 2 ||

			SphereC[3] == 1 && SphereC[4] == 1 && SphereC[5] == 1 ||
			SphereC[3] == 2 && SphereC[4] == 2 && SphereC[5] == 2 ||

			SphereC[6] == 1 && SphereC[7] == 1 && SphereC[8] == 1 ||
			SphereC[6] == 2 && SphereC[7] == 2 && SphereC[8] == 2 ||

			SphereC[0] == 1 && SphereC[3] == 1 && SphereC[6] == 1 ||
			SphereC[0] == 2 && SphereC[3] == 2 && SphereC[6] == 2 ||
			
			SphereC[1] == 1 && SphereC[4] == 1 && SphereC[7] == 1 ||
			SphereC[1] == 2 && SphereC[4] == 2 && SphereC[7] == 2 ||

			SphereC[2] == 1 && SphereC[5] == 1 && SphereC[8] == 1 ||
			SphereC[2] == 2 && SphereC[5] == 2 && SphereC[8] == 2 ||

			SphereC[0] == 1 && SphereC[4] == 1 && SphereC[8] == 1 ||
			SphereC[0] == 2 && SphereC[4] == 2 && SphereC[8] == 2 ||

			SphereC[6] == 1 && SphereC[4] == 1 && SphereC[2] == 1 ||
			SphereC[6] == 2 && SphereC[4] == 2 && SphereC[2] == 2) {
			win = true;
		}
	}
}

void AMainController::TurnController(int sphereindex)
{
	if (SphereStatus[sphereindex] == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("That index is already taken"));

		return;
	}

	if (win == false) {
		if (TurnCounter % 2 == 0 && TurnCounter < 9)
		{
			Spheres[sphereindex]->SetMaterial(0, Blue);
			SphereC[sphereindex] = 1;
			CheckForWin();
			if (win == true) {
				UE_LOG(LogTemp, Warning, TEXT("Blue has won"));
			}
		}
		else if (TurnCounter % 2 == 1 && TurnCounter < 9)
		{
			Spheres[sphereindex]->SetMaterial(0, Red);
			SphereC[sphereindex] = 2;
			CheckForWin();
			if (win == true) {
				UE_LOG(LogTemp, Warning, TEXT("Red has won"));
			}
		}

		//UE_LOG(LogTemp, Warning, TEXT("Turncounter: %s"), FString(TurnCounter));

		if (TurnCounter == 8 && win == false) {
			UE_LOG(LogTemp, Warning, TEXT("Draw"));
		}
		SphereStatus[sphereindex] = true;
	


		TurnCounter++;
	}
}