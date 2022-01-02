// Fill out your copyright notice in the Description page of Project Settings.


#include "QWClient.h"
#include "QWServerSDK.h"

bool AQWClient::SocketCreate(FString IPStr, int32 port)
{
	FIPv4Address::Parse(IPStr, ip);     //将传入的IPStr转为IPv4地址

	//创建一个addr存放ip地址和端口
	TSharedPtr<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	//创建客户端socket
	Host = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//连接成功
	if (Host->Connect(*addr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Connect Succeed!"));
		return true;
	}
	//连接失败
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Connect Failed!"));
		return false;
	}
}

bool AQWClient::SocketSend(FString message)
{
	TCHAR *seriallizedChar = message.GetCharArray().GetData();
	int32 size = FCString::Strlen(seriallizedChar) + 1;
	int32 sent = 0;

	if (Host->Send((uint8*)TCHAR_TO_UTF8(seriallizedChar), size, sent))
	{
		UE_LOG(LogTemp, Warning, TEXT("___Send Succeed!"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("___Send Failed!"));
		return false;
	}
}

// 受消息
bool AQWClient::SocketReceive()
{
	m_RecvThread = FRunnableThread::Create(new FReceiveThread(Host), TEXT("RecvThread"));
	return true;
}

bool AQWClient::ThreadEnd()
{
	if (m_RecvThread != nullptr)
	{
		m_RecvThread->Kill(true);
		delete m_RecvThread;
	}
	return true;
}

FString AQWClient::StringFromBinaryArray(TArray<uint8> BinaryArray)
{
	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
}

