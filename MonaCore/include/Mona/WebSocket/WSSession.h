/*
Copyright 2014 Mona
mathieu.poux[a]gmail.com
jammetthomas[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/TCPSession.h"
#include "Mona/WebSocket/WSWriter.h"
#include "Mona/StringReader.h"


namespace Mona {


class WSSession : public TCPSession, public virtual Object {
public:

	WSSession(const SocketAddress& peerAddress, SocketFile& file, Protocol& protocol, Invoker& invoker);

	bool			buildPacket(PoolBuffer& pBuffer,PacketReader& packet);
	void			packetHandler(PacketReader& packet);
	void			flush() { if (_pPublication) _pPublication->flush(); Session::flush(); }
	void			manage();


protected:
	WSWriter&		wsWriter() { return _writer; }
	void			kill(UInt32 type=NORMAL_DEATH);
	Publication*	_pPublication;
	Listener*		_pListener;

	/// \brief Read message and call method if needed
	/// \param packet Content message to read
	void			readMessage(Exception& ex, DataReader& reader, UInt8 responseType=0);
	
private:
	void			closeSusbcription();
	void			closePublication();

	WSWriter		_writer;
};


} // namespace Mona
