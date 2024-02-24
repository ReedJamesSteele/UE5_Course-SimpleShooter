// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBT_Service_PlayerLocation::UBT_Service_PlayerLocation()
{
    NodeName = TEXT("UpdatePlayerLocation");
}

void UBT_Service_PlayerLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn{UGameplayStatics::GetPlayerPawn(GetWorld(), 0)};

    if(PlayerPawn == nullptr)
    {
        return;
    }
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());


}
