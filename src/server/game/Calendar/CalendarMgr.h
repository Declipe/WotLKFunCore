/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
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

#ifndef TRINITY_CALENDARMGR_H
#define TRINITY_CALENDARMGR_H

#include <ace/Singleton.h>
#include "Calendar.h"

class CalendarMgr
{
        friend class ACE_Singleton<CalendarMgr, ACE_Null_Mutex>;

        CalendarMgr();
        ~CalendarMgr();

    public:
        void LoadFromDB();

        CalendarInvite* GetInvite(uint64 inviteId);
        CalendarEvent* GetEvent(uint64 eventId);

        CalendarInviteIdList const& GetPlayerInvites(uint64 guid);
        CalendarEventIdList const& GetPlayerEvents(uint64 guid);

        uint32 GetPlayerNumPending(uint64 guid);
        uint64 GetFreeEventId();
        uint64 GetFreeInviteId();

        void AddAction(CalendarAction const& action);

        void SendCalendarEvent(CalendarEvent const& calendarEvent, CalendarSendEventType type);
        void SendCalendarEventInvite(CalendarInvite const& invite, bool pending);
        void SendCalendarEventInviteAlert(CalendarEvent const& calendarEvent, CalendarInvite const& invite);
        void SendCalendarEventInviteRemove(uint64 guid, CalendarInvite const& invite, uint32 flags);
        void SendCalendarEventInviteRemoveAlert(uint64 guid, CalendarEvent const& calendarEvent, CalendarInviteStatus status);
        void SendCalendarEventUpdateAlert(uint64 guid, CalendarEvent const& calendarEvent, CalendarSendEventType type);
        void SendCalendarEventStatus(uint64 guid, CalendarEvent const& calendarEvent, CalendarInvite const& invite);
        void SendCalendarEventRemovedAlert(uint64 guid, CalendarEvent const& calendarEvent);
        void SendCalendarEventModeratorStatusAlert(CalendarInvite const& invite);

    private:
        CalendarEvent* CheckPermisions(uint64 eventId, Player* player, uint64 inviteId, CalendarModerationRank minRank);

        bool AddEvent(CalendarEvent const& calendarEvent);
        bool RemoveEvent(uint64 eventId);
        bool AddPlayerEvent(uint64 guid, uint64 eventId);
        bool RemovePlayerEvent(uint64 guid, uint64 eventId);

        bool AddInvite(CalendarInvite const& invite);
        uint64 RemoveInvite(uint64 inviteId);
        bool AddPlayerInvite(uint64 guid, uint64 inviteId);
        bool RemovePlayerInvite(uint64 guid, uint64 inviteId);

        CalendarEventMap _events;
        CalendarInviteMap _invites;
        CalendarPlayerInviteIdMap _playerInvites;
        CalendarPlayerEventIdMap _playerEvents;

        uint64 _eventNum;
        uint64 _inviteNum;
};

#define sCalendarMgr ACE_Singleton<CalendarMgr, ACE_Null_Mutex>::instance()

#endif
