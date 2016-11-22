#include "ScriptPCH.h"
#include "grim_batol.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum Texts
{
    SAY_BOMBING_1,
    SAY_BOMBING_2,
    SAY_SUMMON,
    SAY_KILL_1,
    SAY_KILL_2,
    EMOTE_BLITZ = 6,
    EMOTE_GROUND_SIEGE,
    EMOTE_FRENZY
};

enum Creatures
{
    NPC_UMBRISS         = 39625,
    NPC_MALIGNANT_TROGG = 39984,
    NPC_TROGG_DWELLER   = 45467,
    NPC_TRIGGER_BLITZ = 40040,
};

enum Spells
{
    BLEEDING_WOUND          = 74846,
    BLEEDING_WOUND_H        = 91937,
    GROUND_SIEGE            = 74634,
    GROUND_SIEGE_H          = 90249,

    BLITZ_TRIGGER           = 74668,

    BLITZ                   = 74670,
    BLITZ_H                 = 90250,
    FRENZY                  = 74853,
    //Adds
    CLAW_PUNCTURE           = 76507,
    CLAW_PUNCTURE_H         = 90212,
    MODGUD_MALICE           = 74699,
    MODGUD_MALICE_H         = 90169,
	MODGUD_MALICE_ADDDAMAGE = 90170,
	MODGUD_MALICE_DAMAGE    = 74837,
	MODGUD_MALICE_DAMAGE_H  = 90179,
};

struct Locations
{
    float x, y, z, o;
};

static Locations SpawnPosition[]=
{
    {-722.15f, -442.53f, 268.77f, 0.54f},
    {-702.22f, -450.9f, 268.77f, 1.34f}
};

class boss_general_umbriss : public CreatureScript
{
    public:

        boss_general_umbriss() : CreatureScript("boss_general_umbriss")
        {
        }

        struct boss_general_umbrissAI : public ScriptedAI
        {
            boss_general_umbrissAI(Creature *c) : ScriptedAI(c)
            {
                pInstance = c->GetInstanceScript();
            }

            void Reset()
            {
                woundTimer = 12000;
                groundTimer = 30000;
                blitzTimer = 20000;
                addTimer = 5000;
               // groundTimer2 = 300000;
                //tempGUID = 0;
               // isMalignantSpawn = false;
                enrage = false;
                //me->RemoveAurasDueToSpell(DUNGEON_MODE(MODGUD_MALICE,MODGUD_MALICE_H));
				me->RemoveAurasDueToSpell(MODGUD_MALICE_ADDDAMAGE);
                me->RemoveAurasDueToSpell(FRENZY);
                me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
            }

            void EnterCombat(Unit* pWho)
            {
                Talk(0);
            }

            void JustDied(Unit* pKiller)
            {
                Talk(5);
                if (pInstance)
                {
                    pInstance->SetData(DATA_GENERAL_UMBRISS_EVENT, DONE);
					if (IsHeroic() && me->HasAura(MODGUD_MALICE_ADDDAMAGE))
                        pInstance->DoCompleteAchievement(ACHIEV_UMBRAGE_FOR_UMBRISS);
                }
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(RAND(SAY_KILL_1, SAY_KILL_2));
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (woundTimer <= uiDiff)
                {
                    DoCastVictim(DUNGEON_MODE(BLEEDING_WOUND,BLEEDING_WOUND_H));
                    woundTimer = 25000;
                }else woundTimer -= uiDiff;

                if (groundTimer <= uiDiff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    {
						//if (Creature* c = me->SummonCreature(40030, *target, TEMPSUMMON_TIMED_DESPAWN, 5000))
						if (Creature* stalker = me->SummonCreature(40030, *target, TEMPSUMMON_TIMED_DESPAWN, 5000))
                        {
							me->SetOrientation(me->GetAngle(stalker));
							me->SetControlled(true, UNIT_STATE_ROOT);
							me->DisableRotate(true);
							me->SetFacingTo(me->GetAngle(stalker));
							me->SendMovementFlagUpdate();
							DoCast(stalker, DUNGEON_MODE(GROUND_SIEGE, GROUND_SIEGE_H));
							me->AttackStop();
							Talk(EMOTE_GROUND_SIEGE);
							groundTimer2 = 5000;
                        }
                    }
                    groundTimer = 30000;
                }else groundTimer -= uiDiff;

                if (groundTimer2 <= uiDiff)
                {
					me->SetControlled(false, UNIT_STATE_ROOT);
					me->DisableRotate(false);
                }
                else groundTimer2 -= uiDiff;

                if (blitzTimer <= uiDiff)
                {
                    //if (Unit* unit = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    {
						if (Creature* blitz = me->SummonCreature(NPC_TRIGGER_BLITZ, *target, TEMPSUMMON_TIMED_DESPAWN, 5000))
						{ 
						Talk(EMOTE_BLITZ, blitz->GetGUID());
						DoCast(blitz, DUNGEON_MODE(74670, 90250));
						}
                    }
                    blitzTimer = 25000;
                }else blitzTimer -= uiDiff;

                if(!enrage)
                {
                    if(addTimer <= uiDiff)
                    {
                        Talk(SAY_SUMMON);
                        SpawnMalignant();
                        SpawnAdd();
                        addTimer = 35000;

                    } else addTimer -= uiDiff;

                    if (HealthBelowPct(30))
                    {
                        enrage = true;
                        Talk(EMOTE_FRENZY);
                        DoCast(FRENZY);
                    }
                }

                DoMeleeAttackIfReady();
            }

            void SpawnAdd()
            {
                for(int i = 0; i < 3; i ++)
					SummonCreatureWithRandomTarget(NPC_TROGG_DWELLER, SpawnPosition[0].x, SpawnPosition[0].y, SpawnPosition[0].z, SpawnPosition[0].o);
            }

            void SpawnMalignant()
            {
                //if (!isMalignantSpawn && !enrage)
				if (!enrage)
                {
					SummonCreatureWithRandomTarget(NPC_MALIGNANT_TROGG, SpawnPosition[1].x, SpawnPosition[1].y, SpawnPosition[1].z, SpawnPosition[1].o);
                    //isMalignantSpawn = true;
                }
            }

            void SummonCreatureWithRandomTarget(uint32 creatureId, float x, float y, float z, float o)
            {
                Creature* Summoned = me->SummonCreature(creatureId, x, y, z, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);
                if (Summoned)
                {
                    Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (pTarget)
                    {
                        Summoned->AddThreat(pTarget, 1.0f);
                        Summoned->AI()->AttackStart(pTarget);
                    }
                }
            }


            bool isMalignantSpawn;
        private :
            uint32 blitzTimer;
            uint32 groundTimer;
            uint32 groundTimer2;
            uint32 woundTimer;
            uint32 addTimer;
            bool enrage;
            uint64 tempGUID;
            InstanceScript* pInstance;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_general_umbrissAI(pCreature);
        }
};

class npc_malignant : public CreatureScript
{
    public:

        npc_malignant() : CreatureScript("npc_malignant")
        {
        }

        struct npc_malignantAI : public ScriptedAI
        {
            npc_malignantAI(Creature *c) : ScriptedAI(c)
            {
            }

			void Reset()
			{
				clawTime = 5000;
			}

			void JustDied(Unit* pKiller)
			{
				me->CastSpell(me,DUNGEON_MODE(MODGUD_MALICE_DAMAGE, MODGUD_MALICE_DAMAGE_H));
				if (me->GetMap()->IsHeroic())
				{
					if (Creature* umbriss = me->FindNearestCreature(NPC_UMBRISS, 100.0f))
					{
						if (me->GetDistance2d(umbriss->GetPositionX(), umbriss->GetPositionY()) < 8.0f)
							me->AddAura(MODGUD_MALICE_ADDDAMAGE, umbriss);
					}
					if (Creature* dweller = me->FindNearestCreature(NPC_TROGG_DWELLER, 100.0f))
					{
						if (me->GetDistance2d(dweller->GetPositionX(), dweller->GetPositionY()) < 8.0f)
							me->AddAura(MODGUD_MALICE_H, dweller);
					}
				}
			}

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                //DoSpellAttackIfReady(DUNGEON_MODE(CLAW_PUNCTURE,CLAW_PUNCTURE_H));
				if (clawTime <= uiDiff)
				{
					DoCastVictim(DUNGEON_MODE(CLAW_PUNCTURE, CLAW_PUNCTURE_H));
					clawTime = 5000;
				}else clawTime -= uiDiff;

				DoMeleeAttackIfReady();
            }

		private:
			uint32 clawTime;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_malignantAI(pCreature);
        }
};

class npc_trogg_dweller : public CreatureScript
{
    public:

        npc_trogg_dweller() : CreatureScript("npc_trogg_dweller")
        {
        }

        struct npc_trogg_dwellerAI : public ScriptedAI
        {
            npc_trogg_dwellerAI(Creature *c) : ScriptedAI(c) {}

			void Reset()
			{
				clawTime = urand(3000, 5000);
			}

			void JustDied(Unit* pKiller)
			{
					if (me->HasAura(MODGUD_MALICE_H))
					{
						if (Creature* umbriss = me->FindNearestCreature(NPC_UMBRISS, 100.0f))
						{
							if (me->GetDistance2d(umbriss->GetPositionX(), umbriss->GetPositionY()) < 8.0f)
								me->AddAura(MODGUD_MALICE_ADDDAMAGE, umbriss);
						}
						me->CastSpell(me, MODGUD_MALICE_DAMAGE_H);
					}
				
			}

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

				if (clawTime <= uiDiff)
				{
					DoCastVictim(DUNGEON_MODE(CLAW_PUNCTURE, CLAW_PUNCTURE_H));
					clawTime = urand(3000, 5000);
				}else clawTime -= uiDiff;

				DoMeleeAttackIfReady();
			}

		private:
			uint32 clawTime;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_trogg_dwellerAI(pCreature);
        }
};

class spell_bleeding_wound : public SpellScriptLoader
{
public:
    spell_bleeding_wound() : SpellScriptLoader("spell_bleeding_wound") { }

    class spell_bleeding_wound_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_bleeding_wound_AuraScript);

        void HandlePeriodic(AuraEffect const* /*aurEff*/)
        {
            if (GetUnitOwner()->HealthAbovePct(90))
            {
                PreventDefaultAction();
                Remove(AURA_REMOVE_BY_ENEMY_SPELL);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_bleeding_wound_AuraScript::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_bleeding_wound_AuraScript();
    }
};

class spell_ground_siege : public SpellScriptLoader
{
public:
    spell_ground_siege() : SpellScriptLoader("spell_ground_siege") { }

    class spell_ground_siege_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ground_siege_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return false;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ground_siege_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ground_siege_SpellScript();
    }
};

void AddSC_boss_general_umbriss()
{
    new boss_general_umbriss();
    new npc_malignant();
    new npc_trogg_dweller();
    new spell_bleeding_wound();
    new spell_ground_siege();
}
