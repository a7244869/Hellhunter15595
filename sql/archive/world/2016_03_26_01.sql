-- DELETE --
DELETE FROM `creature_text` WHERE `entry` IN (1535,1536,1537,1538,1539,1540,1934);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (1535,1536,1537,1538,1539,1540,1934,39086,39087);

-- Texts for Scarlet Members in Trisfal Glades --
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
('1535', '0', '0', 'The light condemns all who harbor evil. Now you will die!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 1'),
('1536', '0', '0', 'The light condemns all who harbor evil. Now you will die!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 1'),
('1537', '0', '0', 'The light condemns all who harbor evil. Now you will die!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 1'),
('1538', '0', '0', 'The light condemns all who harbor evil. Now you will die!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 1'),
('1539', '0', '0', 'The light condemns all who harbor evil. Now you will die!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 1'),
('1540', '0', '0', 'The light condemns all who harbor evil. Now you will die!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 1'),
('1535', '0', '1', 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 2'),
('1536', '0', '1', 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 2'),
('1537', '0', '1', 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 2'),
('1538', '0', '1', 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 2'),
('1539', '0', '1', 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 2'),
('1540', '0', '1', 'The Scarlet Crusade shall smite the wicked and drive evil from these lands!', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 2'),
('1535', '0', '2', 'There is no escape for you. The Crusade shall destroy all who carry the scourge''s taint.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 3'),
('1536', '0', '2', 'There is no escape for you. The Crusade shall destroy all who carry the scourge''s taint.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 3'),
('1537', '0', '2', 'There is no escape for you. The Crusade shall destroy all who carry the scourge''s taint.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 3'),
('1538', '0', '2', 'There is no escape for you. The Crusade shall destroy all who carry the scourge''s taint.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 3'),
('1539', '0', '2', 'There is no escape for you. The Crusade shall destroy all who carry the scourge''s taint.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 3'),
('1540', '0', '2', 'There is no escape for you. The Crusade shall destroy all who carry the scourge''s taint.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 3'),
('1535', '0', '3', 'You carry the taint of the scourge. Prepare to enter the twisting nether.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 4'),
('1536', '0', '3', 'You carry the taint of the scourge. Prepare to enter the twisting nether.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 4'),
('1537', '0', '3', 'You carry the taint of the scourge. Prepare to enter the twisting nether.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 4'),
('1538', '0', '3', 'You carry the taint of the scourge. Prepare to enter the twisting nether.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 4'),
('1539', '0', '3', 'You carry the taint of the scourge. Prepare to enter the twisting nether.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 4'),
('1540', '0', '3', 'You carry the taint of the scourge. Prepare to enter the twisting nether.', '0', '0', '0', '0', '0', '0', 'Scarlet Member (Trisfal Glades) Say 4'),
('1934', '0', '0', 'Get back, $R!', '0', '0', '0', '0', '0', '0', 'Trisfal Farmer Say 1'),
('1934', '0', '1', 'Get out of my kitchen!', '0', '0', '0', '0', '0', '0', 'Trisfal Farmer Say 2'),
('1934', '0', '2', 'No, no, no... you took my family, but you won''t take my land!', '0', '0', '0', '0', '0', '0', 'Trisfal Farmer Say 3'),
('1934', '0', '3', 'Why won''t you leave us alone?', '0', '0', '0', '0', '0', '0', 'Trisfal Farmer Say 4');

-- Update template of Scarlet Members in Trisfal Glades --
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (1535,1536,1537,1538,1539,1540,1934);

-- SAI for Scarlet Members in Trisfal Glades --
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1535, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Warrior - Text'),
(1535, 0, 1, 0, 0, 0, 100, 0, 3000, 3000, 3500, 3500, 11, 57846, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Warrior - Heroic Strike'),
(1536, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Missionary - Text'),
(1536, 0, 1, 0, 0, 0, 100, 0, 3000, 3000, 3500, 3500, 11, 9053, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Missionary - Fireball'),
(1537, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Zealot - Text'),
(1537, 0, 1, 0, 2, 0, 100, 0, 48, 52, 10000, 10000, 11, 84535, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Zealot - Zealotry'),
(1538, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Friar - Text'),
(1538, 0, 1, 0, 0, 0, 100, 0, 3000, 3000, 20000, 20000, 11, 75967, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Friar - Whirlwind'),
(1539, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Neophyte - Text'),
(1539, 0, 1, 0, 16, 0, 100, 0, 12544, 1, 2000, 2000, 11, 12544, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Neophyte - Frost Armor'),
(1539, 0, 2, 0, 0, 0, 100, 0, 3000, 3000, 3500, 3500, 11, 13322, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Neophyte - Frostbolt'),
(1540, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Vanguard - Text'),
(1540, 0, 1, 0, 1, 0, 100, 0, 0, 0, 299900, 299900, 11, 7164, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Vanguard - Defensive Stance'),
(1540, 0, 2, 0, 0, 0, 100, 0, 3000, 3000, 8000, 8000, 11, 11972, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Vanguard - Shield Bash'),
(1934, 0, 0, 0, 4, 0, 15, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Trisfal Farmer - Text');

-- Slain Scarlet Zealot and Friar - update creature --
UPDATE `creature` SET `MovementType` = '0' WHERE `id` IN (39086,39087);

-- Slain Scarlet Zealot and Friar - update template --
UPDATE `creature_template` SET `unit_flags` = '131718', `dynamicflags` = '32', `questItem1` = '0', `questItem2` = '0', `AIName`='SmartAI', `flags_extra` = '2' WHERE `entry` IN (39086,39087);

-- Slain Scarlet Zealot and Friar - SAI and more SAI --
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(39086, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slain Scarlet Zealot - stop autoatack :P'),
(39086, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 81238, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slain Scarlet Zealot - dead state'),
(39086, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 73304, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slain Scarlet Zealot - shadow aura (Lilian Voss killed him/her)'),
(39087, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slain Scarlet Friar - stop autoatack :P'),
(39087, 0, 1, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 81238, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slain Scarlet Friar - dead state'),
(39087, 0, 2, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 73304, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slain Scarlet Friar - shadow aura (Lilian Voss killed him/her)');

