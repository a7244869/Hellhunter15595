#include "ScriptPCH.h"

/************************
**npc 39708 
*************************/

#define spell_call_flames 76325 // »ðÑæºô»½
#define spell_blast_wave 76473 // ³å»÷²¨

class mob_twilight_tlame_caller : public CreatureScript
{
public:
	mob_twilight_tlame_caller() : CreatureScript("mob_twilight_tlame_caller") {}

	struct mob_twilight_tlame_callerAI : public ScriptedAI
	{
		mob_twilight_tlame_callerAI(Creature *c) : ScriptedAI(c) {}

		uint32 call_flames_time;
		uint32 blast_wave_time;

		void Reset()
		{
			call_flames_time = 11000;
			blast_wave_time = 6000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (call_flames_time <= diff)
			{
				DoCastVictim(spell_call_flames);
				call_flames_time = 12000;
			}
			else call_flames_time -= diff;

			if (blast_wave_time <= diff)
			{
				DoCastVictim(spell_blast_wave);
				blast_wave_time = 8000;
			}
			else blast_wave_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_twilight_tlame_callerAI(pCreature);
	}

};

/************************
**npc 39980
*************************/

#define spell_heart_seeker_blade 76502 // Ñ°ÐÄÕßÖ®ÈÐ
#define spell_inflict_pain 76497 // Ôì³ÉÉËº¦
#define spell_sinister_strike 76500 //Ð°¶ñ¹¥»÷

class mob_twilight_sadist : public CreatureScript
{
public:
	mob_twilight_sadist() : CreatureScript("mob_twilight_sadist") {}

	struct mob_twilight_sadistAI : public ScriptedAI
	{
		mob_twilight_sadistAI(Creature *c) : ScriptedAI(c) {}

		uint32 heart_seeker_blade_time;
		uint32 inflict_pain_time;
		uint32 sinister_strike_time;

		void Reset()
		{
			heart_seeker_blade_time = 3000;
			inflict_pain_time = 10000;
			sinister_strike_time = urand(6000,8000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (heart_seeker_blade_time <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15, true))
					DoCast(target, spell_heart_seeker_blade);
				heart_seeker_blade_time = 6000;
			}
			else heart_seeker_blade_time -= diff;

			if (inflict_pain_time <= diff)
			{
				DoCastVictim(spell_inflict_pain);
				inflict_pain_time = 12000;
			}
			else inflict_pain_time -= diff;

			if (sinister_strike_time <= diff)
			{
				DoCastVictim(spell_sinister_strike);
				sinister_strike_time = 8000;
			}
			else sinister_strike_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_twilight_sadistAI(pCreature);
	}

};

/************************
**npc 39985
*************************/

#define spell_mad_enrage 8599 // ¼¤Å­
#define spell_head_crack 77568 // ÁÑÂ­
#define spell_infected_wound 76512 //¸ÐÈ¾Ö®ÉË

class mob_mad_prisoner : public CreatureScript
{
public:
	mob_mad_prisoner() : CreatureScript("mob_mad_prisoner") {}

	struct mob_mad_prisonerAI : public ScriptedAI
	{
		mob_mad_prisonerAI(Creature *c) : ScriptedAI(c) {}

		uint32 head_crack_time;
		uint32 infected_wound_time;

		void Reset()
		{
			head_crack_time = 8000;
			infected_wound_time = 10000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (head_crack_time <= diff)
			{
				DoCastVictim(spell_head_crack);
				head_crack_time = 18000;
			}
			else head_crack_time -= diff;

			if (infected_wound_time <= diff)
			{
				DoCastVictim(spell_infected_wound);
				infected_wound_time = 20000;
			}
			else infected_wound_time -= diff;

			if (HealthBelowPct(55))
			{
				if (!me->HasAura(spell_mad_enrage))
				{
					DoCast(spell_mad_enrage);
					Talk(0);
				}
			}

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_mad_prisonerAI(pCreature);
	}

};

/************************
**npc 39978
*************************/

#define spell_redhot_poker 76478 // »ð¾æ»¨
#define spell_shackles 76484 // Êø¸¿
#define spell_wild_beatdown 76487 //¿ñ±©ÃÍ»÷

class mob_twilight_torturer : public CreatureScript
{
public:
	mob_twilight_torturer() : CreatureScript("mob_twilight_torturer") {}

	struct mob_twilight_torturerAI : public ScriptedAI
	{
		mob_twilight_torturerAI(Creature *c) : ScriptedAI(c) {}

		uint32 redhot_poker_time;
		uint32 shackles_time;
		uint32 wild_beatdown_time;

		void Reset()
		{
			redhot_poker_time = 6000;
			shackles_time = 10000;
			wild_beatdown_time = 13000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (redhot_poker_time <= diff)
			{
				DoCastVictim(spell_redhot_poker);
				redhot_poker_time = 6000;
			}
			else redhot_poker_time -= diff;

			if (shackles_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
					DoCast(pTarget,spell_shackles);
				shackles_time = 10000;
			}
			else shackles_time -= diff;

			if (wild_beatdown_time <= diff)
			{
				DoCastVictim(spell_wild_beatdown);
				wild_beatdown_time = 20000;
			}
			else wild_beatdown_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_twilight_torturerAI(pCreature);
	}

};

/************************
**npc 40401
*************************/

#define spell_ground_rupture 75347 // µØÕðËéÁÑ
#define spell_burrow_visual 75379 // µØÕðÐ§¹û

class mob_one_quake : public CreatureScript
{
public:
	mob_one_quake() : CreatureScript("mob_one_quake") {}

	struct mob_one_quakeAI : public ScriptedAI
	{
		mob_one_quakeAI(Creature *c) : ScriptedAI(c) {}

		uint32 ground_rupture_time;

		void Reset()
		{
			//ground_rupture_time = 4000;
			DoCast(spell_burrow_visual);
			DoZoneInCombat(me);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			//if (ground_rupture_time <= diff)
			//{
			//	DoCast(spell_ground_rupture);
			//	ground_rupture_time = 1200000;
			//}
			//else ground_rupture_time -= diff;


		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_one_quakeAI(pCreature);
	}

};

/************************
**npc 39987
*************************/

#define spell_blood_of_the_evolved 76574 // ³É³¤×ÅÖ¹Ñª
#define spell_force_blast 76522 // ±¬Õ¨Ö®Á¦
#define spell_grievous_whirl 76524 //ÖØ´´»ØÕ¶
#define spell_shadow_strike 82362 //°µÓ°´ò»÷
#define spell_gravity_strike 76561 //ÖØÁ¦´ò»÷

class mob_evolved_twilight_zealot : public CreatureScript
{
public:
	mob_evolved_twilight_zealot() : CreatureScript("mob_evolved_twilight_zealot") {}

	struct mob_evolved_twilight_zealotAI : public ScriptedAI
	{
		mob_evolved_twilight_zealotAI(Creature *c) : ScriptedAI(c) {}

		uint32 force_blast_time;
		uint32 grievous_whirl_time;
		uint32 shadow_strike_time;
		uint32 gravity_strike_time;

		void Reset()
		{
			me->AddAura(spell_blood_of_the_evolved, me);
			force_blast_time = 10000;
			grievous_whirl_time = 8000;
			shadow_strike_time = urand(13000,15000);
			gravity_strike_time = urand(10500, 12500);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (force_blast_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 60, true))
					DoCast(pTarget, spell_force_blast);

				force_blast_time = 12000;
			}
			else force_blast_time -= diff;

			if (grievous_whirl_time <= diff)
			{
				DoCastVictim(spell_grievous_whirl);

				grievous_whirl_time = 16000;
			}
			else grievous_whirl_time -= diff;

			if (shadow_strike_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					DoCast(pTarget, spell_shadow_strike);

				shadow_strike_time = 20000;
			}
			else shadow_strike_time -= diff;

			if (gravity_strike_time <= diff)
			{
				DoCastVictim(spell_gravity_strike);

				gravity_strike_time = 15000;
			}
			else gravity_strike_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_evolved_twilight_zealotAI(pCreature);
	}

};

/************************
**npc 39994
*************************/

#define spell_heat_exhaustion 76617 // ÖÐÊî
#define spell_immolate 76618 // Ï×¼À

class mob_conflagration : public CreatureScript
{
public:
	mob_conflagration() : CreatureScript("mob_conflagration") {}

	struct mob_conflagrationAI : public ScriptedAI
	{
		mob_conflagrationAI(Creature *c) : ScriptedAI(c) {}

		uint32 heat_exhaustion_time;
		uint32 immolate_time;

		void Reset()
		{
			heat_exhaustion_time = 8000;
			immolate_time = 6000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (immolate_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
					DoCast(pTarget,spell_immolate);
				immolate_time = 10000;
			}
			else immolate_time -= diff;

			if (heat_exhaustion_time <= diff)
			{
				DoCast(spell_heat_exhaustion);
				heat_exhaustion_time = 10000;
			}
			else heat_exhaustion_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_conflagrationAI(pCreature);
	}

};

/************************
**npc 40084
*************************/

#define spell_sunder1_armor 76622 // ÆÆ¼×

class mob_bellows_slave : public CreatureScript
{
public:
	mob_bellows_slave() : CreatureScript("mob_bellows_slave") {}

	struct mob_bellows_slaveAI : public ScriptedAI
	{
		mob_bellows_slaveAI(Creature *c) : ScriptedAI(c) {}

		uint32 sunder1_armor_time;

		void Reset()
		{
			sunder1_armor_time = urand(4000,8000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (sunder1_armor_time <= diff)
			{
				DoCastVictim(spell_sunder1_armor);
				sunder1_armor_time = 7500;
			}
			else sunder1_armor_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_bellows_slaveAI(pCreature);
	}

};

/************************
**npc 40021
*************************/

#define spell_final_volley 76718 // ÖÕ¼«Ñ×¼ý
#define spell_fireball1 76719 // »ðÇòÊõ

class mob_incendiary_spark : public CreatureScript
{
public:
	mob_incendiary_spark() : CreatureScript("mob_incendiary_spark") {}

	struct mob_incendiary_sparkAI : public ScriptedAI
	{
		mob_incendiary_sparkAI(Creature *c) : ScriptedAI(c) {}

		uint32 final_volley_time;
		uint32 fireball1_time;

		void Reset()
		{
			final_volley_time = 10000;
			fireball1_time = 2000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (final_volley_time <= diff)
			{
				DoCast(spell_final_volley);
				final_volley_time = 12000;
			}
			else final_volley_time -= diff;

			if (fireball1_time <= diff)
			{
				DoCastVictim(spell_fireball1);
				fireball1_time = 3000;
			}
			else fireball1_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_incendiary_sparkAI(pCreature);
	}

};

/************************
**npc 40019
*************************/

#define spell_bore1 76688 // ¹á´©
#define spell_shadow_prison 76686 // °µÓ°ÀÎÁý

class mob_twilight_obsidian_borer : public CreatureScript
{
public:
	mob_twilight_obsidian_borer() : CreatureScript("mob_twilight_obsidian_borer") {}

	struct mob_twilight_obsidian_borerAI : public ScriptedAI
	{
		mob_twilight_obsidian_borerAI(Creature *c) : ScriptedAI(c) {}

		uint32 bore1_time;
		uint32 shadow_prison_time;

		void Reset()
		{
			bore1_time = 8500;
			shadow_prison_time = 6000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (bore1_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 20, true))
					DoCast(pTarget, spell_bore1);
				bore1_time = 17000;
			}
			else bore1_time -= diff;

			if (shadow_prison_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
					DoCast(pTarget, spell_shadow_prison);
				shadow_prison_time = 10000;
			}
			else shadow_prison_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_twilight_obsidian_borerAI(pCreature);
	}

};

/************************
**npc 40017
*************************/

#define spell_chain_lightning 76680 // ÉÁµçÁ´
#define spell_fire_blast 76677 // »ðÑæ³å»÷
#define spell_frostbomb1 76682 // ±ùËªÖ®Çò

class mob_twilight_element_warden : public CreatureScript
{
public:
	mob_twilight_element_warden() : CreatureScript("mob_twilight_element_warden") {}

	struct mob_twilight_element_wardenAI : public ScriptedAI
	{
		mob_twilight_element_wardenAI(Creature *c) : ScriptedAI(c) {}

		uint32 chain_lightning_time;
		uint32 fire_blast_time;
		uint32 frostbomb1_time;

		void Reset()
		{
			chain_lightning_time = 6000;
			fire_blast_time = 4000;
			frostbomb1_time = 10000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (chain_lightning_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 30, true))
					DoCast(pTarget, spell_chain_lightning);
				chain_lightning_time = 6000;
			}
			else chain_lightning_time -= diff;

			if (fire_blast_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 20, true))
					DoCast(pTarget, spell_fire_blast);
				fire_blast_time = 5000;
			}
			else fire_blast_time -= diff;

			if (frostbomb1_time <= diff)
			{
				DoCastVictim(spell_frostbomb1);
				frostbomb1_time = 12000;
			}
			else frostbomb1_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_twilight_element_wardenAI(pCreature);
	}

};

/************************
**npc 40023
*************************/

#define spell_bludgeoning_strike 76716 // ÕòÏÅ´ò»÷
#define spell_meteor1 76717 // ÔÉÊ¯Êõ

class mob_defiled_earth_rager : public CreatureScript
{
public:
	mob_defiled_earth_rager() : CreatureScript("mob_defiled_earth_rager") {}

	struct mob_defiled_earth_ragerAI : public ScriptedAI
	{
		mob_defiled_earth_ragerAI(Creature *c) : ScriptedAI(c) {}

		uint32 bludgeoning_strike_time;
		uint32 meteor1_time;

		void Reset()
		{
			bludgeoning_strike_time = urand(6000,8000);
			meteor1_time = 15000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (meteor1_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 60, true))
					DoCast(pTarget, spell_meteor1);
				meteor1_time = 15000;
			}
			else meteor1_time -= diff;

			if (bludgeoning_strike_time <= diff)
			{
				DoCastVictim(spell_bludgeoning_strike);
				bludgeoning_strike_time = 10000;
			}
			else bludgeoning_strike_time -= diff;

			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_defiled_earth_ragerAI(pCreature);
	}

};

void AddSC_mob_blackrock_caverns()
{
	new mob_twilight_tlame_caller();
	new mob_twilight_sadist();
	new mob_mad_prisoner();
	new mob_twilight_torturer();
	new mob_one_quake();
	new mob_evolved_twilight_zealot();
	new mob_conflagration();
	new mob_bellows_slave();
	new mob_incendiary_spark();
	new mob_twilight_obsidian_borer();
	new mob_twilight_element_warden(); 
	new mob_defiled_earth_rager();
}