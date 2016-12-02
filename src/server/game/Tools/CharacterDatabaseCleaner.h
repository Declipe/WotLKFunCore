/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2005-2016 MaNGOS.
*
* ==== Start of GNU GPL ====
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* ==== End of GNU GPL ====
*/

#ifndef CHARACTERDATABASECLEANER_H
#define CHARACTERDATABASECLEANER_H

namespace CharacterDatabaseCleaner
{
    enum CleaningFlags
    {
        CLEANING_FLAG_ACHIEVEMENT_PROGRESS  = 0x1,
        CLEANING_FLAG_SKILLS                = 0x2,
        CLEANING_FLAG_SPELLS                = 0x4,
        CLEANING_FLAG_TALENTS               = 0x8,
        CLEANING_FLAG_QUESTSTATUS           = 0x10
    };

    void CleanDatabase();

    void CheckUnique(const char* column, const char* table, bool (*check)(uint32));

    bool AchievementProgressCheck(uint32 criteria);
    bool SkillCheck(uint32 skill);
    bool SpellCheck(uint32 spell_id);
    bool TalentCheck(uint32 talent_id);

    void CleanCharacterAchievementProgress();
    void CleanCharacterSkills();
    void CleanCharacterSpell();
    void CleanCharacterTalent();
    void CleanCharacterQuestStatus();
}

#endif
