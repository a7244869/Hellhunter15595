#include "ScriptPCH.h"
#include "blackrock_caverns.h"
#include "utf8.h"

class teleporter_blackrock_caverns : public CreatureScript
{
public:
	teleporter_blackrock_caverns()
		: CreatureScript("teleporter_blackrock_caverns")
	{
	}

	struct teleporter_blackrock_cavernsAI : public ScriptedAI
	{
		teleporter_blackrock_cavernsAI(Creature *c) : ScriptedAI(c)
		{
		}

		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
		{
			me->GetMotionMaster()->Clear();
			ScriptedAI::EnterEvadeMode();
		}

		void ReceiveEmote(Player *pPlayer, uint32 uiTextEmote)
		{
			if (me->IsInEvadeMode() || me->isInCombat())
				return;
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new teleporter_blackrock_cavernsAI(pCreature);
	}

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	//uint32 PlayerMaxLevel() const
	//{
	//	return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	//}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		if (InstanceScript* instance = pCreature->GetInstanceScript())
		{
			if (instance->GetData(DATA_KARSH_STEELBENDER_EVENT) == DONE && pCreature->GetDBTableGUIDLow() == 318534)
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[我想我已经击败了卡尔许·控钢者] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 120);
			if (pCreature->GetDBTableGUIDLow() == 318535)
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[我要返回门口] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 130);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[返回 ] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 110);
			pPlayer->SEND_GOSSIP_MENU(20000, pCreature->GetGUID());
		}
	}
	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
	{
		MainMenu(pPlayer, pCreature);

		return true;
	}

	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
	{
		if (pPlayer->isInCombat())
		{
			pCreature->MonsterWhisper("你在战斗中，请先脱离战斗后再来进行传送！", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
		case GOSSIP_ACTION_INFO_DEF + 120:
			pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->TeleportTo(645, 281.584f, 838.455f, 95.916f, 3.81549f);   //这里就是传送到目的地的地图号，坐标x,y,z,o
			break;
		case GOSSIP_ACTION_INFO_DEF + 130:
			pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->TeleportTo(645, 230.232f, 1123.6f, 205.579f, 3.25786f);   //这里就是传送到目的地的地图号，坐标x,y,z,o
			break;
		case GOSSIP_ACTION_INFO_DEF + 110:
			pPlayer->CLOSE_GOSSIP_MENU();
			break;
		}

		return true;
	}
};

void AddSc_teleporter_blackrock_caverns()
{
	new teleporter_blackrock_caverns();
}