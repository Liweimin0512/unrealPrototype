// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QWServerSDK.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "ReceiveThread.h"
#include "QWClient.generated.h"

UCLASS()
class QWSERVERSDK_API AQWClient : public AActor
{
	GENERATED_BODY()

	public:
	//创建Socket并连接到服务器（主线程）
	UFUNCTION(BlueprintCallable, Category = "MySocket")
	bool SocketCreate(FString IPStr, int32 port);

	//发消息(主线程)
	UFUNCTION(BlueprintCallable, Category = "MySocket")
	bool SocketSend(FString message);

	//收消息(子线程)
	UFUNCTION(BlueprintCallable, Category = "MySocket")
	bool SocketReceive();

	UFUNCTION(BlueprintCallable, Category = "MySocket")
	bool ThreadEnd();

	FString StringFromBinaryArray(TArray<uint8> BinaryArray);

	public:
	FSocket *Host;
	FIPv4Address ip;    
	FRunnableThread* m_RecvThread;
};
