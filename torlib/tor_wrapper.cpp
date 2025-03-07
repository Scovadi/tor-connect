
/*-
* Copyright (c) 2021, Zano project, https://zano.org/
* Copyright (c) 2021, Mikhail Butolin, bml505@hotmail.com
* Copyright (c) 2009, Moxie Marlinspike
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 4. Neither the name of this program nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/

#include "tor_wrapper.h"
#include "torlib.h"

namespace tools
{
  namespace tor
  {

    tor_transport::tor_transport() :m_is_connected(false), m_ptransport(new TorLib())
    {
      m_ptransport->Init();
    }

    bool tor_transport::connect(const std::string& ip, int port, int timeout, int /*recev_timeout*/, const std::string& /*bind_ip*/)
    {
      int res = m_ptransport->Connect(ip, port, timeout);
      if (res == 0)
      {
        m_is_connected = true;
        return true;
      }
      return false;
    }
    bool tor_transport::disconnect()
    {
      return m_ptransport->Close();
    }
    bool tor_transport::is_connected()
    {
      return m_is_connected;
    }
    bool tor_transport::send(const void* data, size_t sz)
    {
      //todo: subject for future refactoring, extra copy operation
      std::string str((const char*)data, sz);
      return this->send(str);
    }
    bool tor_transport::send(const std::string& buff)
    {
      return m_ptransport->Send(buff);
    }

    bool tor_transport::recv_n(std::string& buff, int64_t sz)
    {
      //TODO
      return false;
    }

  }
}