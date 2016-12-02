/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2006-2016 MaNGOS.
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

#ifndef THREADING_H
#define THREADING_H

#include <ace/Thread.h>
#include <ace/TSS_T.h>
#include <ace/Atomic_Op.h>
#include <assert.h>

namespace ACE_Based
{

    class Runnable
    {
        public:
            virtual ~Runnable() {}
            virtual void run() = 0;

            void incReference() { ++m_refs; }
            void decReference()
            {
                if (!--m_refs)
                    delete this;
            }
        private:
            ACE_Atomic_Op<ACE_Thread_Mutex, long> m_refs;
    };

    enum Priority
    {
        Idle,
        Lowest,
        Low,
        Normal,
        High,
        Highest,
        Realtime,
    };

#define MAXPRIORITYNUM (Realtime + 1)

    class ThreadPriority
    {
        public:
            ThreadPriority();
            int getPriority(Priority p) const;

        private:
            int m_priority[MAXPRIORITYNUM];
    };

    class Thread
    {
        public:
            Thread();
            explicit Thread(Runnable* instance);
            ~Thread();

            bool start();
            bool wait();
            void destroy();

            void suspend();
            void resume();

            void setPriority(Priority type);

            static void Sleep(unsigned long msecs);
            static ACE_thread_t currentId();
            static ACE_hthread_t currentHandle();
            static Thread * current();

        private:
            Thread(const Thread&);
            Thread& operator=(const Thread&);

            static ACE_THR_FUNC_RETURN ThreadTask(void * param);

            ACE_thread_t m_iThreadId;
            ACE_hthread_t m_hThreadHandle;
            Runnable* m_task;

            typedef ACE_TSS<Thread> ThreadStorage;
            //global object - container for Thread class representation of every thread
            static ThreadStorage m_ThreadStorage;
            //use this object to determine current OS thread priority values mapped to enum Priority{}
            static ThreadPriority m_TpEnum;
    };

}
#endif
