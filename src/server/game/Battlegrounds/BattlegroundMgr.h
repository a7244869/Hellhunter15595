/*
Hellhunter
*/

#ifndef __BATTLEGROUNDMGR_H
#define __BATTLEGROUNDMGR_H

#include "Common.h"
#include "DBCEnums.h"
#include "Battleground.h"
#include "BattlegroundQueue.h"
#include <ace/Singleton.h>

typedef std::map<uint32, Battleground*> BattlegroundContainer;
typedef std::set<uint32> BattlegroundClientIdsContainer;

typedef UNORDERED_MAP<uint32, BattlegroundTypeId> BattleMastersMap;

#define WS_CURRENCY_RESET_TIME 20001                    // Custom worldstate

struct CreateBattlegroundData
{
    BattlegroundTypeId bgTypeId;
    bool IsArena;
    uint32 MinPlayersPerTeam;
    uint32 MaxPlayersPerTeam;
    uint32 LevelMin;
    uint32 LevelMax;
    char* BattlegroundName;
    uint32 MapID;
    float Team1StartLocX;
    float Team1StartLocY;
    float Team1StartLocZ;
    float Team1StartLocO;
    float Team2StartLocX;
    float Team2StartLocY;
    float Team2StartLocZ;
    float Team2StartLocO;
    float StartMaxDist;
    uint32 scriptId;
};

struct BattlegroundData
{
    BattlegroundContainer m_Battlegrounds;
    BattlegroundClientIdsContainer m_ClientBattlegroundIds[MAX_BATTLEGROUND_BRACKETS];
    BGFreeSlotQueueContainer BGFreeSlotQueue;
};

class BattlegroundMgr
{
    friend class ACE_Singleton<BattlegroundMgr, ACE_Null_Mutex>;

    private:
        BattlegroundMgr();
        ~BattlegroundMgr();

    public:
        void Update(uint32 diff);

        /* Packet Building */
        void BuildPlayerJoinedBattlegroundPacket(WorldPacket* data, uint64 guid);
        void BuildPlayerLeftBattlegroundPacket(WorldPacket* data, uint64 guid);
        void BuildBattlegroundListPacket(WorldPacket* data, uint64 guid, Player* player, BattlegroundTypeId bgTypeId);
        void BuildStatusFailedPacket(WorldPacket* data, Battleground* bg, Player* pPlayer, uint8 QueueSlot, GroupJoinBattlegroundResult result);
        void BuildUpdateWorldStatePacket(WorldPacket* data, uint32 field, uint32 value);
        void BuildPvpLogDataPacket(WorldPacket* data, Battleground* bg);
        void BuildBattlegroundStatusPacket(WorldPacket* data, Battleground* bg, Player* player, uint8 queueSlot, uint8 statusId, uint32 time1, uint32 time2, uint8 arenaType);
        void BuildPlaySoundPacket(WorldPacket* data, uint32 soundId);
        void SendAreaSpiritHealerQueryOpcode(Player* player, Battleground* bg, uint64 guid);

        /* Battlegrounds */
        Battleground* GetBattlegroundThroughClientInstance(uint32 instanceId, BattlegroundTypeId bgTypeId);
        Battleground* GetBattleground(uint32 InstanceID, BattlegroundTypeId bgTypeId);
        Battleground* GetBattlegroundTemplate(BattlegroundTypeId bgTypeId);
        Battleground* CreateNewBattleground(BattlegroundTypeId bgTypeId, PvPDifficultyEntry const* bracketEntry, uint8 arenaType, bool isRated);

        void AddBattleground(Battleground* bg);
        void RemoveBattleground(BattlegroundTypeId bgTypeId, uint32 instanceId);
        void AddToBGFreeSlotQueue(BattlegroundTypeId bgTypeId, Battleground* bg);
        void RemoveFromBGFreeSlotQueue(BattlegroundTypeId bgTypeId, uint32 instanceId);
        BGFreeSlotQueueContainer& GetBGFreeSlotQueueStore(BattlegroundTypeId bgTypeId);

        void CreateInitialBattlegrounds();
        void DeleteAllBattlegrounds();

        void SendToBattleground(Player* player, uint32 InstanceID, BattlegroundTypeId bgTypeId);

        /* Battleground queues */
        BattlegroundQueue& GetBattlegroundQueue(BattlegroundQueueTypeId bgQueueTypeId) { return m_BattlegroundQueues[bgQueueTypeId]; }
        void ScheduleQueueUpdate(uint32 arenaMatchmakerRating, uint8 arenaType, BattlegroundQueueTypeId bgQueueTypeId, BattlegroundTypeId bgTypeId, BattlegroundBracketId bracket_id);
        uint32 GetPrematureFinishTime() const;

        void ToggleArenaTesting();
        void ToggleTesting();

        void SetHolidayWeekends(uint32 mask);

        bool isArenaTesting() const { return m_ArenaTesting; }
        bool isTesting() const { return m_Testing; }

        static BattlegroundQueueTypeId BGQueueTypeId(BattlegroundTypeId bgTypeId, uint8 arenaType);
        static BattlegroundTypeId BGTemplateId(BattlegroundQueueTypeId bgQueueTypeId);
        static uint8 BGArenaType(BattlegroundQueueTypeId bgQueueTypeId);

        static HolidayIds BGTypeToWeekendHolidayId(BattlegroundTypeId bgTypeId);
        static BattlegroundTypeId WeekendHolidayIdToBGType(HolidayIds holiday);
        static bool IsBGWeekend(BattlegroundTypeId bgTypeId);

        uint32 GetMaxRatingDifference() const;
        uint32 GetRatingDiscardTimer()  const;
        void LoadBattleMastersEntry();
        BattlegroundTypeId GetBattleMasterBG(uint32 entry) const
        {
            BattleMastersMap::const_iterator itr = mBattleMastersMap.find(entry);
            if (itr != mBattleMastersMap.end())
                return itr->second;
            return BATTLEGROUND_WS;
        }

    private:
        bool CreateBattleground(CreateBattlegroundData& data);
        uint32 CreateClientVisibleInstanceId(BattlegroundTypeId bgTypeId, BattlegroundBracketId bracket_id);
        static bool IsArenaType(BattlegroundTypeId bgTypeId);
        BattlegroundTypeId GetRandomBG(BattlegroundTypeId id);

        typedef std::map<BattlegroundTypeId, BattlegroundData> BattlegroundDataContainer;
        BattlegroundDataContainer bgDataStore;

        BattlegroundQueue m_BattlegroundQueues[MAX_BATTLEGROUND_QUEUE_TYPES];

        typedef std::map<BattlegroundTypeId, uint8> BattlegroundSelectionWeightMap; // TypeId and its selectionWeight
        BattlegroundSelectionWeightMap m_ArenaSelectionWeights;
        BattlegroundSelectionWeightMap m_BGSelectionWeights;
        std::vector<uint64> m_QueueUpdateScheduler;
        uint32 m_NextRatedArenaUpdate;
        bool   m_ArenaTesting;
        bool   m_Testing;
        BattleMastersMap mBattleMastersMap;
};

#define sBattlegroundMgr ACE_Singleton<BattlegroundMgr, ACE_Null_Mutex>::instance()
#endif
