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

#ifndef __REALMSOCKET_H__
#define __REALMSOCKET_H__

#include <ace/Synch_Traits.h>
#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/Message_Block.h>
#include <ace/Basic_Types.h>
#include "Common.h"

class RealmSocket : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
private:
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> Base;

public:
    class Session
    {
    public:
        Session(void);
        virtual ~Session(void);

        virtual void OnRead(void) = 0;
        virtual void OnAccept(void) = 0;
        virtual void OnClose(void) = 0;
    };

    RealmSocket(void);
    virtual ~RealmSocket(void);

    size_t recv_len(void) const;
    bool recv_soft(char *buf, size_t len);
    bool recv(char *buf, size_t len);
    void recv_skip(size_t len);

    bool send(const char *buf, size_t len);

    const std::string& getRemoteAddress(void) const;

    uint16 getRemotePort(void) const;

    virtual int open(void *);

    virtual int close(int);

    virtual int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
    virtual int handle_output(ACE_HANDLE = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = ACE_Event_Handler::ALL_EVENTS_MASK);

    void set_session(Session* session);

private:
    ssize_t noblk_send(ACE_Message_Block &message_block);

    ACE_Message_Block input_buffer_;
    Session* session_;
    std::string _remoteAddress;
    uint16 _remotePort;
};

#endif /* __REALMSOCKET_H__ */
