//#include "discord.hpp"
//#include "discord_register.h"
//#include "discord_rpc.h"
//#include <windows.h>
//
//
//discord_sdk::discord_sdk()
//{
//	{
//		DiscordEventHandlers Handler;
//		memset(&Handler, 0, sizeof(Handler));
//		Discord_Initialize("959754822465224724", &Handler, TRUE, nullptr);
//	}
//
//}
//
//bool discord_sdk::update() const
//{
//
//	{
//		DiscordRichPresence presence{};
//
//		DiscordRichPresence discordPresence;
//		memset(&discordPresence, 0, sizeof(discordPresence));
//		discordPresence.state = "CSGO || MEOWENGINE Codename: CSGO";
//		discordPresence.details = "V3.15";
//		discordPresence.startTimestamp = 1507665886;
//		discordPresence.largeImageText = "";
//		discordPresence.smallImageText = "";
//		discordPresence.largeImageKey = "https://Hitdaquan.0-o.pl/HFWU1c7W";
//		discordPresence.smallImageKey = "https://Hitdaquan.0-o.pl/0oQBvGWq";
//		Discord_UpdatePresence(&discordPresence);
//
//		Discord_UpdatePresence(&presence);
//	}
//
//}
//
//discord_sdk::~discord_sdk()
//{
//    Discord_Shutdown();
//}