/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
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

#ifndef _M_DELAY_EXECUTOR_H
#define _M_DELAY_EXECUTOR_H

#include <ace/Task.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h>

class DelayExecutor : protected ACE_Task_Base
{
    public:

        DelayExecutor();
        virtual ~DelayExecutor();

        static DelayExecutor* instance();

        int execute(ACE_Method_Request* new_req);

        int activate(int num_threads = 1, ACE_Method_Request* pre_svc_hook = NULL, ACE_Method_Request* post_svc_hook = NULL);

        int deactivate();

        bool activated();

        virtual int svc();

    private:

        ACE_Activation_Queue queue_;
        ACE_Method_Request* pre_svc_hook_;
        ACE_Method_Request* post_svc_hook_;
        bool activated_;

        void activated(bool s);
};

#endif // _M_DELAY_EXECUTOR_H
