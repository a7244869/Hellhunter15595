#include "ScriptPCH.h"

/************************
**npc 41096
*************************/

#define spell_healing_wave 76813 // ÖÎÁÆ²¨
#define spell_hex 76820 // ÑýÊõ
#define spell_wrath 76815 // ·ßÅ­

class mob_nazjar_spiritmender : public CreatureScript
{
public:
	mob_nazjar_spiritmender() : CreatureScript("mob_nazjar_spiritmender") {}

	struct mob_nazjar_spiritmenderAI : public ScriptedAI
	{
		mob_nazjar_spiritmenderAI(Creature *c) : ScriptedAI(c) {}

		uint32 healing_wave_time;
		uint32 hex_time;

		void Reset()
		{
			healing_wave_time = 9000;
			hex_time = 5000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			if (healing_wave_time <= diff)
			{
				me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
				me->InterruptSpell(CURRENT_MELEE_SPELL);
				me->InterruptSpell(CURRENT_GENERIC_SPELL);

				if (Unit* target = DoSelectLowestHpFriendly(40.0f))
					DoCast(target,spell_healing_wave);
				healing_wave_time = 10000;
			}
			else healing_wave_time -= diff;

			if (hex_time <= diff)
			{
				me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
				me->InterruptSpell(CURRENT_MELEE_SPELL);
				me->InterruptSpell(CURRENT_GENERIC_SPELL);

				if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 50, true))
					DoCast(pTarget, spell_hex);
				hex_time = 8000;
			}
			else hex_time -= diff;

			DoSpellAttackIfReady(spell_wrath);
			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_nazjar_spiritmenderAI(pCreature);
	}

};

/************************
**npc 39616
*************************/

#define spell_bubble_shield 76790 // Ë®ÅÝ»¤¶Ü
#define spell_lacerate 76807 // ¸îÁÑ

class mob_nazjar_nvader : public CreatureScript
{
public:
	mob_nazjar_nvader() : CreatureScript("mob_nazjar_nvader") {}

	struct mob_nazjar_nvaderAI : public ScriptedAI
	{
		mob_nazjar_nvaderAI(Creature *c) : ScriptedAI(c) {}

		uint32 bubble_shield_time;
		uint32 lacerate_time;

		void Reset()
		{
			bubble_shield_time = 8000;
			lacerate_time = urand(4000,6000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (bubble_shield_time <= diff)
			{
				DoCast(spell_bubble_shield);
					bubble_shield_time = 16500;
			}
			else bubble_shield_time -= diff;

			if (lacerate_time <= diff)
			{
				DoCastVictim(spell_lacerate);
				lacerate_time = 8000;
			}
			else lacerate_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_nazjar_nvaderAI(pCreature);
	}

};

/************************
**npc 40577
*************************/

#define spell_waterlogged 76721 // ½þÊª

class mob_nazjar_sentinel : public CreatureScript
{
public:
	mob_nazjar_sentinel() : CreatureScript("mob_nazjar_sentinel") {}

	struct mob_nazjar_sentinelAI : public ScriptedAI
	{
		mob_nazjar_sentinelAI(Creature *c) : ScriptedAI(c) {}

		uint32 waterlogged_time;

		void Reset()
		{
			waterlogged_time = 8000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (waterlogged_time <= diff)
			{
				DoCastVictim(spell_waterlogged);
				waterlogged_time = 8000;
			}
			else waterlogged_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_nazjar_sentinelAI(pCreature);
	}

};

void AddSC_mob_throne_of_the_tides()
{
	new mob_nazjar_spiritmender();
	new mob_nazjar_nvader();
	new mob_nazjar_sentinel();
}