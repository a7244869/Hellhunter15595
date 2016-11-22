#include "ScriptPCH.h"

/************************
**Gardien de la Nuée Azur
*************************/

#define spell_impregnation_des_arcanes 76378 // Impregnation_des_Arcanes
#define spell_malediction_de_la_nuee_azur 90659 // Malediction_de_la_Nuee_Azur

class mob_gardien_de_la_nuee_azur: public CreatureScript
{
public:
    mob_gardien_de_la_nuee_azur() : CreatureScript("mob_gardien_de_la_nuee_azur") {}

    struct mob_gardien_de_la_nuee_azurAI : public ScriptedAI
    {
        mob_gardien_de_la_nuee_azurAI(Creature *c) : ScriptedAI(c) {}

        uint32 impregnation_des_arcanes;
        uint32 malediction_de_la_nuee_azur;

        void Reset()
        {
			impregnation_des_arcanes = urand(5000, 8000);
			malediction_de_la_nuee_azur = urand(10000, 15000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (impregnation_des_arcanes<= diff)
            {
                DoCastVictim(spell_impregnation_des_arcanes);
                impregnation_des_arcanes = 15000;
            } else impregnation_des_arcanes-= diff;

            if (malediction_de_la_nuee_azur<= diff)
            {
                DoCastVictim(spell_malediction_de_la_nuee_azur);
                malediction_de_la_nuee_azur = 15000;
            } else malediction_de_la_nuee_azur-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_gardien_de_la_nuee_azurAI(pCreature);
    }

};

/*****************************
 **Gardien de la Nuée Cramoisie
 ******************************/

#define spell_charge_cramoisie 76404 // Charge_Cramoisie
#define spell_onde_de_choc_cramoisie 76409 // Onde_de_Choc_Cramoisie

class mob_gardien_de_la_nuee_cramoisie: public CreatureScript
{
public:
    mob_gardien_de_la_nuee_cramoisie() : CreatureScript("mob_gardien_de_la_nuee_cramoisie") { }

    struct mob_gardien_de_la_nuee_cramoisieAI : public ScriptedAI
    {
        mob_gardien_de_la_nuee_cramoisieAI(Creature *c) : ScriptedAI(c) {}

        uint32 charge_cramoisie;
        uint32 onde_de_choc_cramoisie;

        void Reset()
        {
            charge_cramoisie = 15000;
            onde_de_choc_cramoisie = 23000;
        }

		void EnterCombat(Unit* /*who*/)
		{
			DoCastVictim(spell_charge_cramoisie);
		}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (charge_cramoisie<= diff)
            {
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 30, true))
					DoCast(pTarget, spell_charge_cramoisie);
                charge_cramoisie = 8000;
            } else charge_cramoisie-= diff;

            if (onde_de_choc_cramoisie<= diff)
            {
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 20, true))
					DoCast(pTarget, spell_onde_de_choc_cramoisie);
                onde_de_choc_cramoisie = 10000;
            } else onde_de_choc_cramoisie-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_gardien_de_la_nuee_cramoisieAI(pCreature);
    }

};

/******************************
 **Prophète de la Nuée Cramoisie
 *******************************/

#define spell_bouclier_du_crepuscule_flamboyant 90308 // Bouclier_du_Crepuscule_Flamboyant
#define spell_flamme_corrompue 90653 // Flamme_Corrompue

class mob_prophete_de_la_nuee_cramoisie: public CreatureScript
{
public:
    mob_prophete_de_la_nuee_cramoisie() : CreatureScript("mob_prophete_de_la_nuee_cramoisie") {}

    struct mob_prophete_de_la_nuee_cramoisieAI : public ScriptedAI
    {
        mob_prophete_de_la_nuee_cramoisieAI(Creature *c) : ScriptedAI(c) {}

        uint32 bouclier_du_crepuscule_flamboyant;
        uint32 flamme_corrompue;

        void Reset()
        {
            bouclier_du_crepuscule_flamboyant = 30000;
            flamme_corrompue = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (bouclier_du_crepuscule_flamboyant<= diff)
            {
                DoCast(me, spell_bouclier_du_crepuscule_flamboyant);
                bouclier_du_crepuscule_flamboyant = 30000;
            } else bouclier_du_crepuscule_flamboyant-= diff;

            if (flamme_corrompue<= diff)
            {
                DoCastVictim(spell_flamme_corrompue);
                flamme_corrompue = 10000;
            } else flamme_corrompue-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_prophete_de_la_nuee_cramoisieAI(pCreature);
    }

};

/*************************
 **Prophète de la Nuée Azur
 **************************/

#define spell_arcanes_distordues 90844 // Arcanes_Distordues
#define spell_crepuscule_deforme 90300 // Crépuscule_Déform?
#define spell_eclair_crepusculaire 90303 // Eclair_Crépusculaire

class mob_prophete_de_la_nuee_azur: public CreatureScript
{
public:
    mob_prophete_de_la_nuee_azur() : CreatureScript("mob_prophete_de_la_nuee_azur") {}

    struct mob_prophete_de_la_nuee_azurAI : public ScriptedAI
    {
        mob_prophete_de_la_nuee_azurAI(Creature *c) : ScriptedAI(c) {}

        uint32 arcanes_distordues;
        uint32 crepuscule_deforme;
        uint32 eclair_crepusculaire;

        void Reset()
        {
            crepuscule_deforme = 15000;
			eclair_crepusculaire = 6000;

			if (!me->HasAura(spell_arcanes_distordues))
			{
				DoCast(me, spell_arcanes_distordues);
				return;
			}
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

/*            if (arcanes_distordues<= diff)
            {
                DoCast(me, spell_arcanes_distordues);
                arcanes_distordues = 15000;
            } else arcanes_distordues-= diff*/;

			if (!me->HasAura(spell_arcanes_distordues))
			{
				DoCast(me, spell_arcanes_distordues);
			}

            if (crepuscule_deforme<= diff)
            {
                DoCastVictim(spell_crepuscule_deforme);
                crepuscule_deforme = 15000;
            } else crepuscule_deforme-= diff;

            if (eclair_crepusculaire<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_eclair_crepusculaire);
                eclair_crepusculaire = 10000;
            } else eclair_crepusculaire-= diff;


            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_prophete_de_la_nuee_azurAI(pCreature);
    }

};

/****************************
 **Brise-Tempête du Crépuscule
 *****************************/

#define spell_carapace_deau 90522 // Carapace_D'eau
#define spell_invocation_dun_esprit_de_leau 74561 // Invocation_d'un_Esprit_de_l'Eau
#define spell_trait_deau 90491 // Trait_d'Eau

class mob_brise_tempete_du_crepuscule: public CreatureScript
{
public:
    mob_brise_tempete_du_crepuscule() : CreatureScript("mob_brise_tempete_du_crepuscule") {}

    struct mob_brise_tempete_du_crepusculeAI : public ScriptedAI
    {
        mob_brise_tempete_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 carapace_deau;
        uint32 trait_deau;

        void Reset()
        {

            carapace_deau = 13000;
            trait_deau = 5000;

			DoCast(spell_invocation_dun_esprit_de_leau);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (carapace_deau<= diff)
            {
                DoCast(me, spell_carapace_deau);
                carapace_deau = 15000;
            } else carapace_deau-= diff;


            if (trait_deau<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_trait_deau);
                trait_deau = 5000;
            } else trait_deau-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_brise_tempete_du_crepusculeAI(pCreature);
    }

};

/************************
 **Esprit de l'Eau Asservi
 *************************/

#define spell_trait_deau2 90490 // Trait_d'Eau

class  mob_esprit_de_leau_asservi: public CreatureScript
{
public:
    mob_esprit_de_leau_asservi() : CreatureScript("mob_esprit_de_leau_asservi") {}

    struct mob_esprit_de_leau_asserviAI : public ScriptedAI
    {
        mob_esprit_de_leau_asserviAI(Creature *c) : ScriptedAI(c) {}

        uint32 trait_deau;

        void Reset()
        {
            trait_deau = 3000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (trait_deau<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_trait_deau2);
                trait_deau = 3000;
            } else trait_deau-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_esprit_de_leau_asserviAI(pCreature);
    }

};

/****************************
 **Maître d'Arme du Crépuscule
 *****************************/

#define spell_deluge_de_coups 76729 // Déluge_de_Coups
#define spell_frappe_mortelle 90526 // Frappe_Mortelle

class mob_maitre_darmes_du_crepuscule: public CreatureScript
{
public:
    mob_maitre_darmes_du_crepuscule() : CreatureScript("mob_maitre_darmes_du_crepuscule") {}

    struct mob_maitre_darmes_du_crepusculeAI : public ScriptedAI
    {
        mob_maitre_darmes_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 deluge_de_coups;
        uint32 frappe_mortelle;

        void Reset()
        {
			deluge_de_coups = urand(11000, 15000);
			frappe_mortelle = urand(6000, 9000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (deluge_de_coups<= diff)
            {
                DoCastVictim(spell_deluge_de_coups);
				deluge_de_coups = urand(11000, 15000);
            } else deluge_de_coups-= diff;

            if (frappe_mortelle<= diff)
            {
                DoCastVictim(spell_frappe_mortelle);
				frappe_mortelle = urand(6000, 9000);
            } else frappe_mortelle-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_maitre_darmes_du_crepusculeAI(pCreature);
    }

};

/*****************************
 **Elementaire de Roche Asservi
 ******************************/

#define spell_bouclier_rocheux_dentele 76014 // Bouclier_Rocheux_Dentele

class mob_elementaire_de_roche_asservi: public CreatureScript
{
public:
    mob_elementaire_de_roche_asservi() : CreatureScript("mob_elementaire_de_roche_asservi") {}

    struct mob_elementaire_de_roche_asserviAI : public ScriptedAI
    {
        mob_elementaire_de_roche_asserviAI(Creature *c) : ScriptedAI(c) {}

        uint32 bouclier_rocheux_dentele;

        void Reset()
        {
            bouclier_rocheux_dentele = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (bouclier_rocheux_dentele<= diff)
            {
                DoCast(me, spell_bouclier_rocheux_dentele);
                bouclier_rocheux_dentele = 12000;
            } else bouclier_rocheux_dentele-= diff;

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_elementaire_de_roche_asserviAI(pCreature);
    }

};

/****************************
 **Sculpte-Terre du Crépuscule
 *****************************/

#define spell_invocation_dun_elementaire_de_roche 74552 // Invocation_d'un_Elementaire_de Roche
#define spell_peau_de_pierre 90486 // Peau_de_Pierre
#define spell_pointe_de_terre 90487 // Pointe_de_Terre

class mob_sculpte_terre_du_crepuscule: public CreatureScript
{
public:
    mob_sculpte_terre_du_crepuscule() : CreatureScript("mob_sculpte_terre_du_crepuscule") {}

    struct mob_sculpte_terre_du_crepusculeAI : public ScriptedAI
    {
        mob_sculpte_terre_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 peau_de_pierre;
        uint32 pointe_de_terre;

        void Reset()
        {

			peau_de_pierre = urand(13000, 18000);
			pointe_de_terre = urand(6000, 10000);
			DoCast(spell_invocation_dun_elementaire_de_roche);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (peau_de_pierre<= diff)
            {
                DoCast(me, spell_peau_de_pierre);
                peau_de_pierre = urand(13000,18000);
            } else peau_de_pierre-= diff;

            if (pointe_de_terre<= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
                    DoCast(target, spell_pointe_de_terre);
				pointe_de_terre = urand(6000, 10000);
            } else pointe_de_terre-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_sculpte_terre_du_crepusculeAI(pCreature);
    }

};

/*************************
 **Massacreur du Crépuscule
 **************************/

#define spell_broyeur_a_viande 90665 // Broyeur_a_Viande
#define spell_pris_de_vertige 90666 // Pris_de_Vertige

class mob_massacreur_du_crepuscule: public CreatureScript
{
public:
    mob_massacreur_du_crepuscule() : CreatureScript("mob_massacreur_du_crepuscule") {}

    struct mob_massacreur_du_crepusculeAI : public ScriptedAI
    {
        mob_massacreur_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 broyeur_a_viande;
        uint32 pris_de_vertige;

        void Reset()
        {
            broyeur_a_viande = 10000;
			pris_de_vertige  = 14000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (broyeur_a_viande<= diff)
            {
				DoCast(spell_broyeur_a_viande);
                broyeur_a_viande = 20000;
            } else broyeur_a_viande-= diff;

			if (pris_de_vertige <= diff)
			{
				DoCast(spell_pris_de_vertige);
				pris_de_vertige = 20000;
			}
			else pris_de_vertige -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_massacreur_du_crepusculeAI(pCreature);
    }

};

/***********************
 **Chercheflamme Rehauss? ************************/

#define spell_feu_eruptif 90693 // Feu_Eruptif
#define spell_flammes_deconcertantes 76514 // Flammes_Déconcertantes

class mob_chercheflamme_rehausse: public CreatureScript
{
public:
    mob_chercheflamme_rehausse() : CreatureScript("mob_chercheflamme_rehausse") {}

    struct mob_chercheflamme_rehausseAI : public ScriptedAI
    {
        mob_chercheflamme_rehausseAI(Creature *c) : ScriptedAI(c) {}

        uint32 feu_eruptif;
        uint32 flammes_deconcertantes;

		void Reset()
        {
            feu_eruptif = 8000;
            flammes_deconcertantes = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (feu_eruptif<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_feu_eruptif);
                feu_eruptif = 10000;
            } else feu_eruptif-= diff;

            if (flammes_deconcertantes<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_flammes_deconcertantes);
                flammes_deconcertantes = 15000;
            } else flammes_deconcertantes-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_chercheflamme_rehausseAI(pCreature);
    }

};

/*********************
**Marche-Vent Rehauss
**********************/

#define spell_marche_vent 76557 // Marche_Vent
#define spell_water_infused_blades 76036     //Water Infused Blades

class mob_marche_vent_rehausse: public CreatureScript
{
public:
    mob_marche_vent_rehausse() : CreatureScript("mob_marche_vent_rehausse") {}

    struct mob_marche_vent_rehausseAI : public ScriptedAI
    {
        mob_marche_vent_rehausseAI(Creature *c) : ScriptedAI(c) {}

        uint32 marche_vent;
		uint32 water_infused_blades;

        void Reset()
        {
            marche_vent = 15000;
			water_infused_blades = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (marche_vent<= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, spell_marche_vent);
                marche_vent = 15000;
            } else marche_vent-= diff;

			if (water_infused_blades <= diff)
			{
				me->AddAura(spell_water_infused_blades, me);
				water_infused_blades = 30000;
			}
			else water_infused_blades -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_marche_vent_rehausseAI(pCreature);
    }

};

/*******************************
 **Tisseur D'Ombre du Crépuscule
 ********************************/

#define spell_invocation_dun_chasseur_corrompu 76418 // Invocation_d'un_Chasseur_Corrompu
#define spell_tisse_ombre 90673 // Tisse_Ombre
#define spell_trait_de_lombre 90668 // Trait_de_l'Ombre

class mob_tisseur_dombre_du_crepuscule: public CreatureScript
{
public:
    mob_tisseur_dombre_du_crepuscule() : CreatureScript("mob_tisseur_dombre_du_crepuscule") {}

    struct mob_tisseur_dombre_du_crepusculeAI : public ScriptedAI
    {
        mob_tisseur_dombre_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 invocation_dun_chasseur_corrompu;
        uint32 tisse_ombre;
        uint32 trait_de_lombre;

        void Reset()
        {
            tisse_ombre = 10000;
            trait_de_lombre = 4000;
			DoCast(spell_invocation_dun_chasseur_corrompu);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (tisse_ombre<= diff)
            {
                DoCastVictim(spell_tisse_ombre);
                tisse_ombre = 12000;
            } else tisse_ombre-= diff;

            if (trait_de_lombre<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_trait_de_lombre);
                trait_de_lombre = 5000;
            } else trait_de_lombre-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_tisseur_dombre_du_crepusculeAI(pCreature);
    }

};

/*****************************
 **Seigneur de Guerre Nuée Azur
 ******************************/

#define spell_deflagration_azur 90697 // Déflagration_Azur
#define spell_invocation_dun_visage_tordu 90695 // Invocation_d'un_Visage_Tordu

class mob_seigneur_de_guerre_de_la_nuee_azur: public CreatureScript
{
public:
    mob_seigneur_de_guerre_de_la_nuee_azur() : CreatureScript("mob_seigneur_de_guerre_de_la_nuee_azur") {}

    struct mob_seigneur_de_guerre_de_la_nuee_azurAI : public ScriptedAI
    {
        mob_seigneur_de_guerre_de_la_nuee_azurAI(Creature *c) : ScriptedAI(c) {}

        uint32 deflagration_azur;
        uint32 invocation_dun_visage_tordu;

        void Reset()
        {
            deflagration_azur = 20000;
            invocation_dun_visage_tordu = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (deflagration_azur<= diff)
            {
                DoCast(spell_deflagration_azur);
                deflagration_azur = 17000;
            } else deflagration_azur-= diff;

            if (invocation_dun_visage_tordu<= diff)
            {
				DoCast(spell_invocation_dun_visage_tordu);
                invocation_dun_visage_tordu = 30000;
            } else invocation_dun_visage_tordu-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_seigneur_de_guerre_de_la_nuee_azurAI(pCreature);
    }

};

/****************************************
 **Seigneur de Guerre de la Nuee Cramoisie
 *****************************************/

#define spell_brasier_desarmant 90705 // Brasier_Desarmant
#define spell_renforcement_du_crepuscule 90704 // Renforcement_du_Crepuscule

class mob_seigneur_de_guerre_de_la_nuee_cramoisie: public CreatureScript
{
public:
    mob_seigneur_de_guerre_de_la_nuee_cramoisie() : CreatureScript("mob_seigneur_de_guerre_de_la_nuee_cramoisie") {}

    struct mob_seigneur_de_guerre_de_la_nuee_cramoisieAI : public ScriptedAI
    {
        mob_seigneur_de_guerre_de_la_nuee_cramoisieAI(Creature *c) : ScriptedAI(c) {}

        uint32 brasier_desarmant;
        uint32 renforcement_du_crepuscule;

        void Reset()
        {
            brasier_desarmant = 10000;
            renforcement_du_crepuscule = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (brasier_desarmant<= diff)
            {
                DoCastVictim(spell_brasier_desarmant);
                brasier_desarmant = 15000;
            } else brasier_desarmant-= diff;

            if (renforcement_du_crepuscule<= diff)
            {
                DoCast(me, spell_renforcement_du_crepuscule);
                renforcement_du_crepuscule = 20000;
            } else renforcement_du_crepuscule-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_seigneur_de_guerre_de_la_nuee_cramoisieAI(pCreature);
    }
};

/************************
 **Imposteur du Crépuscule
 *************************/

#define spell_duperie 90719 // Duperie
#define spell_esprit_enchaine 90715 // Esprit_Enchain?
#define spell_explosion_trompeuse 90712 // Explosion_Trompeuse

class mob_imposteur_du_crepuscule: public CreatureScript
{
public:
    mob_imposteur_du_crepuscule() : CreatureScript("mob_imposteur_du_crepuscule") {}

    struct mob_imposteur_du_crepusculeAI : public ScriptedAI
    {
        mob_imposteur_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 esprit_enchaine;
        uint32 explosion_trompeuse;

        void Reset()
        {
            esprit_enchaine = 17000;
            explosion_trompeuse = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (esprit_enchaine<= diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,100,true), spell_esprit_enchaine);
                esprit_enchaine = 17000;
            } else esprit_enchaine-= diff;

            if (explosion_trompeuse<= diff)
            {
               DoCastVictim(spell_explosion_trompeuse);
                explosion_trompeuse = 3000;
            } else explosion_trompeuse-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_imposteur_du_crepusculeAI(pCreature);
    }

};

/*********************
 **Brute Gronn Asservie
 **********************/

#define spell_broie_armure 90710 // Broie_Armure

class mob_brute_gronn_asservie: public CreatureScript
{
public:
    mob_brute_gronn_asservie() : CreatureScript("mob_brute_gronn_asservie") {}

    struct mob_brute_gronn_asservieAI : public ScriptedAI
    {
        mob_brute_gronn_asservieAI(Creature *c) : ScriptedAI(c) {}

        uint32 broie_armure;

        void Reset()
        {
            broie_armure = 8000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (broie_armure<= diff)
            {
				DoCastVictim(spell_broie_armure);
                broie_armure = 8000;

            } else broie_armure-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_brute_gronn_asservieAI(pCreature);
    }

};

/****************************
 **Esprit du Tonnerre Asservie
 *****************************/

#define spell_appel_declair 90852 // Appel_d'Eclair

class mob_esprit_du_tonnerre_asservie: public CreatureScript
{
public:
    mob_esprit_du_tonnerre_asservie() : CreatureScript("mob_esprit_du_tonnerre_asservie") {}

    struct mob_esprit_du_tonnerre_asservieAI : public ScriptedAI
    {
        mob_esprit_du_tonnerre_asservieAI(Creature *c) : ScriptedAI(c) {}

        uint32 appel_declair;

        void Reset()
        {
            appel_declair = 8000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (appel_declair<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 30, true))
                    DoCast(pTarget, spell_appel_declair);
                appel_declair = 8000;
            } else appel_declair-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_esprit_du_tonnerre_asservieAI(pCreature);
    }

};

/*****************************
 **Mande Tonnerre du Crépuscule
 ******************************/

#define spell_chaine_declairs 90856 // Chaines_D'éclairs
#define spell_invocation_dun_esprit_du_tonnerre 75096 // Invocation_d'un_Esprit_du_Tonnerre
#define spell_surcharger 90858 // Surcharger

class mob_mande_tonnerre_du_crepuscule: public CreatureScript
{
public:
    mob_mande_tonnerre_du_crepuscule() : CreatureScript("mob_mande_tonnerre_du_crepuscule") {}

    struct mob_mande_tonnerre_du_crepusculeAI : public ScriptedAI
    {
        mob_mande_tonnerre_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 chaine_declairs;
        uint32 surcharger;

        void Reset()
        {
            chaine_declairs = 10000;
            surcharger = 5000;

			DoCast(spell_invocation_dun_esprit_du_tonnerre);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (chaine_declairs<= diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,30,true), spell_chaine_declairs);
                chaine_declairs = 13000;
            } else chaine_declairs-= diff;


            if (surcharger<= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
                    DoCast(target, spell_surcharger);
                surcharger = 5000;
            } else surcharger-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_mande_tonnerre_du_crepusculeAI(pCreature);
    }

};

/*************************
 **Grippe-Feu du Crépuscule
 **************************/

#define spell_conduit_de_flammes 90851 // Conduit_de_Flammes
#define spell_eclair_de_lave 90849 // Eclair_de_Lave
#define spell_invocation_de_braise_ardente 74551 // Invocation_de_Braise_Ardente

class mob_grippe_feu_du_crepuscule: public CreatureScript
{
public:
    mob_grippe_feu_du_crepuscule() : CreatureScript("mob_grippe_feu_du_crepuscule") {}

    struct mob_grippe_feu_du_crepusculeAI : public ScriptedAI
    {
        mob_grippe_feu_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 conduit_de_flammes;
        uint32 eclair_de_lave;

        void Reset()
        {
            conduit_de_flammes = 13000;
            eclair_de_lave = 4000;

			DoCast(spell_invocation_de_braise_ardente);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (conduit_de_flammes<= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0,25, true))
                    DoCast(target, spell_conduit_de_flammes);
                conduit_de_flammes = 20000;
            } else conduit_de_flammes-= diff;

            if (eclair_de_lave<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
                    DoCast(pTarget, spell_eclair_de_lave);
                eclair_de_lave = 5000;
            } else eclair_de_lave-= diff;


            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_grippe_feu_du_crepusculeAI(pCreature);
    }

};

/************************
 **Braise Ardente Asservie
 *************************/

#define spell_horion_de_flammes 90846 // Horion_de_Flammes

class mob_braise_ardente_asservie: public CreatureScript
{
public:
    mob_braise_ardente_asservie() : CreatureScript("mob_braise_ardente_asservie") {}

    struct mob_braise_ardente_asservieAI : public ScriptedAI
    {
        mob_braise_ardente_asservieAI(Creature *c) : ScriptedAI(c) {}

        uint32 horion_de_flammes;

        void Reset()
        {
            horion_de_flammes = 6000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (horion_de_flammes<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
                    DoCast(pTarget, spell_horion_de_flammes);
                horion_de_flammes = 8000;
            } else horion_de_flammes-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_braise_ardente_asservieAI(pCreature);
    }

};

/******************************
 **Flagellant Aquatique Rehauss? *******************************/

#define spell_geyser_focalise 90870 // Geyser_Focalis?
#define spell_jet_deau 90868 // Jet_d'Eau
#define spell_nuage_declairs 76097 // Nuage_d'Eclairs

class mob_flagellant_aquatique_rehausse: public CreatureScript
{
public:
    mob_flagellant_aquatique_rehausse() : CreatureScript("mob_flagellant_aquatique_rehausse") {}

    struct mob_flagellant_aquatique_rehausseAI : public ScriptedAI
    {
        mob_flagellant_aquatique_rehausseAI(Creature *c) : ScriptedAI(c) {}

        uint32 geyser_focalise;
        uint32 jet_deau;

        void Reset()
        {
            geyser_focalise = 12000;
            jet_deau = 8000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (geyser_focalise<= diff)
            {
				if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 25, true))
					DoCast(pTarget,spell_geyser_focalise);
                geyser_focalise = 20000;
            } else geyser_focalise-= diff;

            if (jet_deau<= diff)
            {
                DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,40,true), spell_jet_deau);
                jet_deau = 8000;
            } else jet_deau-= diff;

			if (!me->HasAura(spell_nuage_declairs))
			{
				if (HealthBelowPct(60))
				{
					me->AddAura(spell_nuage_declairs, me);
				}
			}

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_flagellant_aquatique_rehausseAI(pCreature);
    }

};

/*********************
 **Brise-Roche Rehauss? **********************/

#define spell_blessure_brulante 76093 // Blessure_Brulante
#define spell_choc_de_pierre 90866 // Choc_de_Pierre
#define spell_poings_ardents 76086 // Poings_Ardents

class mob_brise_roche_rehausse: public CreatureScript
{
public:
    mob_brise_roche_rehausse() : CreatureScript("mob_brise_roche_rehausse") {}

    struct mob_brise_roche_rehausseAI : ScriptedAI
    {
        mob_brise_roche_rehausseAI(Creature *c) : ScriptedAI(c) {}

        uint32 choc_de_pierre;

        void Reset()
        {
            choc_de_pierre = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

			if (!me->HasAura(spell_poings_ardents))
			{
				if (HealthBelowPct(60))
				{
					DoCast(spell_poings_ardents);
				}
			}

            if (choc_de_pierre<= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 15, true))
					DoCast(target, spell_choc_de_pierre);
                choc_de_pierre = 12000;
            } else choc_de_pierre-= diff;


            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_brise_roche_rehausseAI(pCreature);
    }

};

/*************************
 **Mande-Wyrm du Crepuscule
 **************************/

#define spell_nourrir_le_familier 90872 // Nourrir_le_Familier
#define twilight_drake  39390         //Äº¹â·ÉÁú

class mob_mande_wyrm_du_crepuscule: public CreatureScript
{
public:
    mob_mande_wyrm_du_crepuscule() : CreatureScript("mob_mande_wyrm_du_crepuscule") {}

    struct mob_mande_wyrm_du_crepusculeAI : public ScriptedAI
    {
        mob_mande_wyrm_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 nourrir_le_familier;

		enum Yells
		{
			SAY_AGGARO = 0,
			SAY_HELP  = 1
		};
		

		void EnterCombat(Unit* /*who*/)
		{
			float myX = me->GetHomePosition().GetPositionX();
			float myY = me->GetHomePosition().GetPositionY();
			float myZ = me->GetHomePosition().GetPositionZ();
			me->SummonCreature(twilight_drake, myX, myY, myZ+20, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);

			Talk(SAY_AGGARO);
			Talk(SAY_HELP);
		}

        void Reset()
        {
            nourrir_le_familier = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

			if (nourrir_le_familier <= diff)
			{
				if (Creature* twilightdrake = me->FindNearestCreature(twilight_drake, 100.0f))
				{
					me->AddAura(spell_nourrir_le_familier, twilightdrake);
				}
				nourrir_le_familier = 20000;
			}else nourrir_le_familier -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_mande_wyrm_du_crepusculeAI(pCreature);
    }

};

/********************
 **Drake du Crepuscule
 *********************/

#define spell_flammes_du_crepuscule 75931 // Flammes_du_Crépuscule
#define spell_souffle_crepusculaire 90875 // Souffle_Crepusculaire

class mob_drake_du_crepuscule: public CreatureScript
{
public:
    mob_drake_du_crepuscule() : CreatureScript("mob_drake_du_crepuscule") {}

    struct mob_drake_du_crepusculeAI : public ScriptedAI
    {
        mob_drake_du_crepusculeAI(Creature *c) : ScriptedAI(c) {}

        uint32 souffle_crepusculaire;

        void Reset()
        {
            souffle_crepusculaire = 10000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (souffle_crepusculaire<= diff)
            {
                DoCastVictim(spell_souffle_crepusculaire);
                souffle_crepusculaire = 10000;
            } else souffle_crepusculaire-= diff;

            DoMeleeAttackIfReady();
        }
    };



    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_drake_du_crepusculeAI(pCreature);
    }

};

/***********************
 **Corrupteur Sans-Visage
 ************************/

#define spell_guerison_umbrale 91040 // Guerison_Umbrale
#define spell_siphon_dessence 91028 // Siphon_d'Essence

class mob_corrupteur_sans_visage: public CreatureScript
{
public:
    mob_corrupteur_sans_visage() : CreatureScript("mob_corrupteur_sans_visage") {}

    struct mob_corrupteur_sans_visageAI : public ScriptedAI
    {
        mob_corrupteur_sans_visageAI(Creature *c) : ScriptedAI(c) {}

        uint32 guerison_umbrale;
        uint32 siphon_dessence;

        void Reset()
        {
            guerison_umbrale = 15000;
            siphon_dessence = 8000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (guerison_umbrale<= diff)
            {
                DoCast(me, spell_guerison_umbrale);
                guerison_umbrale = 20000;
            } else guerison_umbrale-= diff;

            if (siphon_dessence<= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, spell_siphon_dessence);
                siphon_dessence = 12000;
            } else siphon_dessence-= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_corrupteur_sans_visageAI(pCreature);
    }

};

/***********************
**Crimsonborne Seer
************************/

#define spell_blazing_twilight_shield 76314 // blazing twilight shield
#define spell_corrupted_flame 76332 // Corrupted Flame

class mob_crimsonborne_seer : public CreatureScript
{
public:
	mob_crimsonborne_seer() : CreatureScript("mob_crimsonborne_seer") {}

	struct mob_crimsonborne_seerAI : public ScriptedAI
	{
		mob_crimsonborne_seerAI(Creature *c) : ScriptedAI(c) {}

		uint32 blazing_twilight_shield;
		uint32 corrupted_flame;

		void Reset()
		{
			blazing_twilight_shield = 13000;
			corrupted_flame = 5000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (corrupted_flame <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 30, true))
					DoCast(pTarget, spell_corrupted_flame);
				corrupted_flame = 15000;
			}
			else corrupted_flame -= diff;

			if (blazing_twilight_shield <= diff)
			{
				if (Unit* target = DoSelectLowestHpFriendly(40.0f))
					DoCast(target, spell_blazing_twilight_shield);
				
				blazing_twilight_shield = 10000;
			}
			else blazing_twilight_shield -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_crimsonborne_seerAI(pCreature);
	}

};

/***********************
**Khaaphom
************************/

#define spell_spell_lock 24259 // spell lock

class mob_khaaphom : public CreatureScript
{
public:
	mob_khaaphom() : CreatureScript("mob_khaaphom") {}

	struct mob_khaaphomAI : public ScriptedAI
	{
		mob_khaaphomAI(Creature *c) : ScriptedAI(c) {}

		uint32 spell_lock_time;

		void Reset()
		{
			spell_lock_time = urand(6000, 10000);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (spell_lock_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, SpellTargetSelector(me, spell_spell_lock)))
					DoCast(pTarget, spell_spell_lock);
				spell_lock_time = urand(6000, 10000);
			}
			else spell_lock_time -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_khaaphomAI(pCreature);
	}

};

/***********************
**Twilight War-Mage
************************/

#define spell_ice_enchant 76823  //±ù¸½Ä§
#define spell_fire_enchant 76822  //»ð¸½Ä§
#define spell_polymorph  76826    //±äÐÎ

class mob_twilight_war_mage : public CreatureScript
{
public:
	mob_twilight_war_mage() : CreatureScript("mob_twilight_war_mage") {}

	struct mob_twilight_war_mageAI : public ScriptedAI
	{
		mob_twilight_war_mageAI(Creature *c) : ScriptedAI(c) {}

		uint32 spell_polymorph_time;

		void Reset()
		{
			spell_polymorph_time = urand(12000, 15000);
			DoCast(spell_fire_enchant);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (spell_polymorph_time <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 30, true))
					DoCast(pTarget, spell_polymorph);
				spell_polymorph_time = urand(12000, 15000);
			}
			else spell_polymorph_time -= diff;

			if (!me->HasAura(spell_ice_enchant))
			{
				if (HealthBelowPct(50))
				{
					DoCast(spell_ice_enchant);
				}
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mob_twilight_war_mageAI(pCreature);
	}

};

/***********************
**mop_spell_issure
************************/

#define spell_spell_issure 90863 //ÁÑÏ¶AOE

class mop_spell_issure : public CreatureScript
{
public:
	mop_spell_issure() : CreatureScript("mop_spell_issure") {}

	struct mop_spell_issureAI : public ScriptedAI
	{
		mop_spell_issureAI(Creature *c) : ScriptedAI(c) {}

		uint32 spell_spell_issure_time;

		void Reset()
		{
			spell_spell_issure_time = 1000;
			DoZoneInCombat();
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (spell_spell_issure_time <= diff)
			{
				DoCast(spell_spell_issure);
				spell_spell_issure_time = 1000;
			}
			else spell_spell_issure_time -= diff;

		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new mop_spell_issureAI(pCreature);
	}

};

void AddSC_mob_trash_grim_batol()
{
    new mob_gardien_de_la_nuee_azur();
    new mob_gardien_de_la_nuee_cramoisie();
    new mob_prophete_de_la_nuee_azur();
    new mob_brise_tempete_du_crepuscule();
    new mob_esprit_de_leau_asservi();
    new mob_maitre_darmes_du_crepuscule();
    new mob_elementaire_de_roche_asservi();
    new mob_sculpte_terre_du_crepuscule();
    new mob_massacreur_du_crepuscule();
    new mob_chercheflamme_rehausse();
    new mob_marche_vent_rehausse();
    new mob_tisseur_dombre_du_crepuscule();
    new mob_seigneur_de_guerre_de_la_nuee_azur();
    new mob_seigneur_de_guerre_de_la_nuee_cramoisie();
    new mob_imposteur_du_crepuscule();
    new mob_brute_gronn_asservie();
    new mob_esprit_du_tonnerre_asservie();
    new mob_mande_tonnerre_du_crepuscule();
    new mob_grippe_feu_du_crepuscule();
    new mob_braise_ardente_asservie();
    new mob_flagellant_aquatique_rehausse();
    new mob_brise_roche_rehausse();
    new mob_mande_wyrm_du_crepuscule();
    new mob_drake_du_crepuscule();
    new mob_corrupteur_sans_visage();
	new mob_crimsonborne_seer();
	new mob_khaaphom();
	new mob_twilight_war_mage();
	new mop_spell_issure();
}
