/*
Hellhunter
*/


#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "AccountMgr.h"
#include "Language.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"

class gm_commandscript : public CommandScript
{
public:
    gm_commandscript() : CommandScript("gm_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand gmCommandTable[] =
        {
            { "chat",           SEC_MODERATOR,      false, &HandleGMChatCommand,              "", NULL },
            { "fly",            SEC_ADMINISTRATOR,  false, &HandleGMFlyCommand,               "", NULL },
            { "ingame",         SEC_PLAYER,         true,  &HandleGMListIngameCommand,        "", NULL },
            { "list",           SEC_ADMINISTRATOR,  true,  &HandleGMListFullCommand,          "", NULL },
            { "visible",        SEC_MODERATOR,      false, &HandleGMVisibleCommand,           "", NULL },
            { "",               SEC_MODERATOR,      false, &HandleGMCommand,                  "", NULL },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "gm",             SEC_MODERATOR,      false, NULL,                     "", gmCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    // Enables or disables hiding of the staff badge
    static bool HandleGMChatCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            WorldSession* session = handler->GetSession();
            if (!AccountMgr::IsPlayerAccount(session->GetSecurity()) && session->GetPlayer()->isGMChat())
                session->SendNotification(LANG_GM_CHAT_ON);
            else
                session->SendNotification(LANG_GM_CHAT_OFF);
            return true;
        }

        std::string param = (char*)args;

        if (param == "on")
        {
            handler->GetSession()->GetPlayer()->SetGMChat(true);
            handler->GetSession()->SendNotification(LANG_GM_CHAT_ON);
            return true;
        }

        if (param == "off")
        {
            handler->GetSession()->GetPlayer()->SetGMChat(false);
            handler->GetSession()->SendNotification(LANG_GM_CHAT_OFF);
            return true;
        }

        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
    }

    static bool HandleGMFlyCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* target =  handler->getSelectedPlayer();
        if (!target)
            target = handler->GetSession()->GetPlayer();

        WorldPacket data;
        if (strncmp(args, "on", 3) == 0)
        {
            target->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY);
            target->SendMovementCanFlyChange();
        }
        else if (strncmp(args, "off", 4) == 0)
        {
            target->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY);
            target->SendMovementCanFlyChange();
        }
        else
        {
            handler->SendSysMessage(LANG_USE_BOL);
            return false;
        }
        handler->PSendSysMessage(LANG_COMMAND_FLYMODE_STATUS, handler->GetNameLink(target).c_str(), args);
        return true;
    }

    static bool HandleGMListIngameCommand(ChatHandler* handler, char const* /*args*/)
    {
        bool first = true;
        bool footer = false;

        TRINITY_READ_GUARD(HashMapHolder<Player>::LockType, *HashMapHolder<Player>::GetLock());
        HashMapHolder<Player>::MapType const& m = sObjectAccessor->GetPlayers();
        for (HashMapHolder<Player>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
        {
            AccountTypes itrSec = itr->second->GetSession()->GetSecurity();
            if ((itr->second->isGameMaster() || (!AccountMgr::IsPlayerAccount(itrSec) && itrSec <= AccountTypes(sWorld->getIntConfig(CONFIG_GM_LEVEL_IN_GM_LIST)))) &&
                (!handler->GetSession() || itr->second->IsVisibleGloballyFor(handler->GetSession()->GetPlayer())))
            {
                if (first)
                {
                    first = false;
                    footer = true;
                    handler->SendSysMessage(LANG_GMS_ON_SRV);
                    handler->SendSysMessage("========================");
                }
                std::string const& name = itr->second->GetName();
                uint8 size = name.size();
                uint8 security = itrSec;
                uint8 max = ((16 - size) / 2);
                uint8 max2 = max;
                if ((max + max2 + size) == 16)
                    max2 = max - 1;
                if (handler->GetSession())
                    handler->PSendSysMessage("|    %s GMLevel %u", name.c_str(), security);
                else
                    handler->PSendSysMessage("|%*s%s%*s|   %u  |", max, " ", name.c_str(), max2, " ", security);
            }
        }
        if (footer)
            handler->SendSysMessage("========================");
        if (first)
            handler->SendSysMessage(LANG_GMS_NOT_LOGGED);
        return true;
    }

    /// Display the list of GMs
    static bool HandleGMListFullCommand(ChatHandler* handler, char const* /*args*/)
    {
        ///- Get the accounts with GM Level >0
        PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_GM_ACCOUNTS);
        stmt->setUInt8(0, uint8(SEC_MODERATOR));
        stmt->setInt32(1, int32(realmID));
        PreparedQueryResult result = LoginDatabase.Query(stmt);

        if (result)
        {
            handler->SendSysMessage(LANG_GMLIST);
            handler->SendSysMessage("========================");
            ///- Cycle through them. Display username and GM level
            do
            {
                Field* fields = result->Fetch();
                char const* name = fields[0].GetCString();
                uint8 security = fields[1].GetUInt8();
                uint8 max = (16 - strlen(name)) / 2;
                uint8 max2 = max;
                if ((max + max2 + strlen(name)) == 16)
                    max2 = max - 1;
                if (handler->GetSession())
                    handler->PSendSysMessage("|    %s GMLevel %u", name, security);
                else
                    handler->PSendSysMessage("|%*s%s%*s|   %u  |", max, " ", name, max2, " ", security);
            } while (result->NextRow());
            handler->SendSysMessage("========================");
        }
        else
            handler->PSendSysMessage(LANG_GMLIST_EMPTY);
        return true;
    }

    //Enable\Disable Invisible mode
    static bool HandleGMVisibleCommand(ChatHandler* handler, char const* args)
    {
		Player* _player = handler->GetSession()->GetPlayer();

        if (!*args)
        {
			handler->PSendSysMessage(LANG_YOU_ARE, _player->isGMVisible() ? handler->GetTrinityString(LANG_VISIBLE) : handler->GetTrinityString(LANG_INVISIBLE));
			return true;
        }

        const uint32 VISUAL_AURA = 37800;
        std::string param = (char*)args;

        if (param == "on")
        {
            if (_player->HasAura(VISUAL_AURA, 0))
                _player->RemoveAurasDueToSpell(VISUAL_AURA);

            _player->SetGMVisible(true);
			_player->UpdateObjectVisibility();
            handler->GetSession()->SendNotification(LANG_INVISIBLE_VISIBLE);
            return true;
        }

        if (param == "off")
        {
			_player->AddAura(VISUAL_AURA, _player);
			_player->SetGMVisible(false);
			_player->UpdateObjectVisibility();
            handler->GetSession()->SendNotification(LANG_INVISIBLE_INVISIBLE);

            return true;
        }

        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
    }

    //Enable\Disable GM Mode
    static bool HandleGMCommand(ChatHandler* handler, char const* args)
    {
		Player* _player = handler->GetSession()->GetPlayer();

        if (!*args)
        {
			handler->GetSession()->SendNotification(_player->isGameMaster() ? LANG_GM_ON : LANG_GM_OFF);
            return true;
        }

        std::string param = (char*)args;

        if (param == "on")
        {
			_player->SetGameMaster(true);
            handler->GetSession()->SendNotification(LANG_GM_ON);
			_player->UpdateTriggerVisibility();
#ifdef _DEBUG_VMAPS
            VMAP::IVMapManager* vMapManager = VMAP::VMapFactory::createOrGetVMapManager();
            vMapManager->processCommand("stoplog");
#endif
            return true;
        }

        if (param == "off")
        {
			_player->SetGameMaster(false);
            handler->GetSession()->SendNotification(LANG_GM_OFF);
			_player->UpdateTriggerVisibility();
#ifdef _DEBUG_VMAPS
            VMAP::IVMapManager* vMapManager = VMAP::VMapFactory::createOrGetVMapManager();
            vMapManager->processCommand("startlog");
#endif
            return true;
        }

        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
    }
};

void AddSC_gm_commandscript()
{
    new gm_commandscript();
}
