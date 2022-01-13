// 收消息线程
#pragma once

// #include "ThreadingBase.h"
#include "Networking.h"

class QWSERVERSDK_API FReceiveThread : public FRunnable
{
	public:
	FReceiveThread(FSocket* client): m_Client(client)
	{}
	~FReceiveThread()
	{
		stopping = true;
	}

	virtual bool Init() override
	{
		stopping = false;
		return true;
	}

	virtual uint32 Run() override
	{
		if (!m_Client)
		{
			return 0;
		}

		TArray<uint8> ReceiveData;
		uint8 element = 0;
		//接收数据包
		while (!stopping)   //线程计数器控制
			{
			ReceiveData.Init(element, 1024u);
			int32 read = 0;
			m_Client->Recv(ReceiveData.GetData(), ReceiveData.Num(), read);
			const FString ReceivedUE4String = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceiveData.GetData())));
			if (ReceivedUE4String.IsEmpty())
			{
				break;
			}
			FString log = "Server:" + ReceivedUE4String;
			UE_LOG(LogTemp, Warning, TEXT("*** %s"), *log);

			FPlatformProcess::Sleep(0.01f);
			}


		return 1;
	}

	virtual void Stop() override
	{
		stopping = true;    //计数器-1
	}

	private:
	FSocket* m_Client;  //客户端套接字
	bool stopping;      //循环控制
	FThreadSafeCounter m_StopTaskCounter;   //线程引用计数器
};