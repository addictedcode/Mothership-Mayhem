// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/InteractableComponent.h"



void UInteractableComponent::Trigger(UObject* Context) {
  this->OnInteract.Broadcast(Context);
}