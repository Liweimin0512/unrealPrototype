// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QWServerTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct QWSERVERSDK_API FMessage
{
	GENERATED_BODY()

	int32 DataLen; //消息的长度
	int32 ID;      //消息的ID
	uint8* Data; //消息的内容

	FMessage()
	: DataLen(uint32(0)),ID(0){}
	
	//NewMsgPackage 创建一个Message消息包
	FMessage(int32 id , uint8* data)
		: DataLen(strlen(reinterpret_cast<char*>(data))),ID(id),Data(data){}
	
	//GetDataLen 获取消息数据段长度
	int32 GetDataLen() {
		return DataLen;
	}

	//GetMsgID 获取消息ID
	int32 GetMsgID() {
		return ID;
	}

	//GetData 获取消息内容
	uint8* GetData() {
		return Data;
	}

	//SetDataLen 设置消息数据段长度
	void SetDataLen(int32 len) {
		DataLen = len;
	}

	//SetMsgID 设计消息ID
	void SetMsgID(int32 msgID) {
		ID = msgID;
	}

	//SetData 设计消息内容
	void SetData(uint8* data) {
		Data = data;
	}
};
