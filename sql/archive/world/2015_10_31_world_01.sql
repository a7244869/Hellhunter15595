insert  into `playercreateinfo_spell`(`race`,`class`,`Spell`,`Note`) values  (7,1,86106,'Decontamination'),(7,2,86106,'Decontamination'),(7,3,86106,'Decontamination'),(7,4,86106,'Decontamination'),(7,5,86106,'Decontamination'),(7,6,86106,'Decontamination'),(7,7,86106,'Decontamination'),(7,8,86106,'Decontamination'),(7,9,86106,'Decontamination');

UPDATE `quest_template` SET `Details` = 'You''ve been down here in Gnomeregan for a long time, $N, and it''s amazing that you''ve survived and kept your wits so long! We need to get you out.$B$BBefore we can send you to the surface to join the rest of the gnomes, you have to go through the decontamination process. Just head into the next room and board the Sanitron 500 using your Racial Ability Decontamination.It will do the rest! It shouldn''t even hurt... much.$B$BWhen you''re all done, check in with Technician Braggle and he''ll make sure you get some suitable gear.' WHERE `Id` = 27635;

