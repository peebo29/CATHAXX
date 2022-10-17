//wip
//#include "resolver.h"
//#include "Memory.h"
//#include "Interfaces.h"
//#include "EventListener.h"
//#include "Config.h"
//#include "Memory.h"
//#include "Interfaces.h"
//#include "SDK/ClientMode.h"
//
//bool NextLBYUpdate()
//{
//	Entity* LocalPlayer = Interfaces.EntityList->GetClientEntity(Interfaces.Engine->GetLocalPlayer());
//	int tick = *(int*)((DWORD)LocalPlayer + Offsets.m_nTickBase);
//	float flServerTime = (float)(tick * Interfaces.Globals->interval_per_tick);
//	if // NEPS_DEBUG
//	{
//		printf("%f\n", LocalPlayer->GetLowerBodyYaw());
//	}
//
//	if (OldLBY != LocalPlayer->GetLowerBodyYaw())
//	{
//		LBYBreakerTimer++;
//		OldLBY = LocalPlayer->GetLowerBodyYaw();
//		bSwitch = !bSwitch;
//		LastLBYUpdateTime = flServerTime;
//	}
//
//	if (CurrentVelocity(LocalPlayer) > 0.5)
//	{
//		LastLBYUpdateTime = flServerTime;
//		return false;
//	}
//
//	if ((LastLBYUpdateTime + 1 - (GetLatency() * 2) < flServerTime) && (LocalPlayer->GetFlags() & FL_ONGROUND))
//	{
//		if (LastLBYUpdateTime + 1.1 - (GetLatency() * 2) < flServerTime)
//		{
//			LastLBYUpdateTime += 1.1;
//		}
//		return true;
//	}
//	return false;
//}
//float GetLatency()
//{
//	INetChannelInfo* nci = Interfaces.Engine->GetNetChannelInfo();
//	if (nci)
//	{
//		float Latency = nci->GetAvgLatency(FLOW_OUTGOING) + nci->GetAvgLatency(FLOW_INCOMING);
//		return Latency;
//	}
//	else
//	{
//		return 0.0f;
//	}
//}
//float GetOutgoingLatency()
//{
//	INetChannelInfo* nci = Interfaces.Engine->GetNetChannelInfo();
//	if (nci)
//	{
//		float OutgoingLatency = nci->GetAvgLatency(FLOW_OUTGOING);
//		return OutgoingLatency;
//	}
//	else
//	{
//		return 0.0f;
//	}
//}
//float GetIncomingLatency()
//{
//	INetChannelInfo* nci = Interfaces.Engine->GetNetChannelInfo();
//	if (nci)
//	{
//		float IncomingLatency = nci->GetAvgLatency(FLOW_INCOMING);
//		return IncomingLatency;
//	}
//	else
//	{
//		return 0.0f;
//	}
//}