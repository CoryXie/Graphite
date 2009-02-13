// Jonathan Eastep, Charles Gruenwald, Jason Miller
//
// FIXME: this is a hack. 
//
// Includes temporary hooks for the syscall server. Otherwise, this is
// the syscall server. The runSyscallServer hook function is to be 
// manually inserted in main thread of the user app. It calls the code
// the implements the real server. Putting the hook in the user code's 
// main thread gives the server a place to run; we avoid having to spawn 
//
// a thread or something in the simulator to house the server code.  
#ifndef SYSCALL_SERVER_H
#define SYSCALL_SERVER_H

#include <iostream>
#include "packetize.h"
#include "transport.h"
#include "fixed_types.h"
#include "network.h"

class SyscallServer {
   public:
      SyscallServer(Network &network, 
            UnstructuredBuffer &send_buff_, UnstructuredBuffer &recv_buff_,
            const UInt32 SERVER_MAX_BUFF,
            char *scratch_);

      ~SyscallServer();

      void handleSyscall(UInt32 core_id);

   private:
      void marshallOpenCall(UInt32 core_id);
      void marshallReadCall(UInt32 core_id);
      void marshallWriteCall(UInt32 core_id);
      void marshallCloseCall(UInt32 core_id);
      void marshallAccessCall(UInt32 core_id);

   //Note: These structures are shared with the MCP
   private:
      Network & m_network;
      UnstructuredBuffer & m_send_buff;
      UnstructuredBuffer & m_recv_buff;
      const UInt32 m_SYSCALL_SERVER_MAX_BUFF;
      char * const m_scratch;

};


#endif
