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

#ifndef TRINITYCORE_ERRORS_H
#define TRINITYCORE_ERRORS_H

#include "Common.h"
#include "Log.h"
#include <ace/Stack_Trace.h>
#include <ace/OS_NS_unistd.h>

#define WPAssert( assertion ) { if (!(assertion)) { ACE_Stack_Trace st; sLog->outError( "\n%s:%i in %s ASSERTION FAILED:\n  %s\n%s\n", __FILE__, __LINE__, __FUNCTION__,  #assertion, st.c_str()); assert( #assertion &&0 ); ((void(*)())NULL)();} }
#define WPError( assertion, errmsg ) if ( ! (assertion) ) { sLog->outError( "%\n%s:%i in %s ERROR:\n  %s\n", __FILE__, __LINE__, __FUNCTION__, (char *)errmsg ); assert( false ); }
#define WPWarning( assertion, errmsg ) if ( ! (assertion) ) { sLog->outError( "\n%s:%i in %s WARNING:\n  %s\n", __FILE__, __LINE__, __FUNCTION__, (char *)errmsg ); }
#define WPFatal( assertion, errmsg ) if ( ! (assertion) ) { sLog->outError( "\n%s:%i in %s FATAL ERROR:\n  %s\n", __FILE__, __LINE__, __FUNCTION__, (char *)errmsg ); ACE_OS::sleep(10); assert( #assertion &&0 ); abort(); }

#define ASSERT WPAssert
#endif
