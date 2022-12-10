#ifndef __INETCHANNELINFO_H__
#define __INETCHANNELINFO_H__

namespace Valve
{
class IDemoRecorder;
class INetMessage;
class bf_write;
class bf_read;
class INetChannelHandler;
class INetChannelInfo;
typedef struct netpacket_s netpacket_t;
typedef struct netadr_s	netadr_t;

class INetChannel
{
public:
	virtual	~INetChannel( void ) {};

	virtual void SetDataRate(float rate) = 0;
	virtual bool RegisterMessage(INetMessage *msg) = 0;
	virtual bool StartStreaming( unsigned int challengeNr ) = 0;
	virtual void ResetStreaming( void ) = 0;
	virtual void SetTimeout(float seconds) = 0;
	virtual void SetDemoRecorder(IDemoRecorder *recorder) = 0;
	virtual void SetChallengeNr(unsigned int chnr) = 0;
	
	virtual void Reset( void ) = 0;
	virtual void Clear( void ) = 0;
	virtual void Shutdown(const char *reason) = 0;
	
	virtual void ProcessPlayback( void ) = 0;
	virtual bool ProcessStream( void ) = 0;
	virtual void ProcessPacket( struct netpacket_s* packet, bool bHasHeader ) = 0;
			
	virtual bool SendNetMsg(INetMessage &msg, bool bForceReliable = false) = 0;
	virtual bool SendData(bf_write &msg, bool bReliable = true) = 0;
	virtual bool SendFile(const char *filename, unsigned int transferID) = 0;
	virtual void DenyFile(const char *filename, unsigned int transferID) = 0;
	virtual void RequestFile_OLD(const char *filename, unsigned int transferID) = 0;	// get rid of this function when we version the 
	virtual void SetChoked( void ) = 0;
	virtual int SendDatagram(bf_write *data) = 0;		
	virtual bool Transmit(bool onlyReliable = false) = 0;

	virtual const netadr_t	&GetRemoteAddress( void ) const = 0;
	virtual INetChannelHandler *GetMsgHandler( void ) const = 0;
	virtual int GetDropNumber( void ) const = 0;
	virtual int GetSocket( void ) const = 0;
	virtual unsigned int GetChallengeNr( void ) const = 0;
	virtual void GetSequenceData( int &nOutSequenceNr, int &nInSequenceNr, int &nOutSequenceNrAck ) = 0;
	virtual void SetSequenceData( int nOutSequenceNr, int nInSequenceNr, int nOutSequenceNrAck ) = 0;
		
	virtual void UpdateMessageStats( int msggroup, int bits) = 0;
	virtual bool CanPacket( void ) const = 0;
	virtual bool IsOverflowed( void ) const = 0;
	virtual bool IsTimedOut( void ) const  = 0;
	virtual bool HasPendingReliableData( void ) = 0;

	virtual void SetFileTransmissionMode(bool bBackgroundMode) = 0;
	virtual void SetCompressionMode( bool bUseCompression ) = 0;
	virtual unsigned int RequestFile(const char *filename) = 0;
	virtual float GetTimeSinceLastReceived( void ) const = 0;	// get time since last received packet in seconds

	virtual void SetMaxBufferSize(bool bReliable, int nBytes) = 0;
};

#define CLASSNAME INetChannelInfo
	class INetChannelInfo
	{
	public:

		enum {
			GENERIC = 0,	// must be first and is default group
			LOCALPLAYER,	// bytes for local player entity update
			OTHERPLAYERS,	// bytes for other players update
			ENTITIES,		// all other entity bytes
			SOUNDS,			// game sounds
			EVENTS,			// event messages
			USERMESSAGES,	// user messages
			ENTMESSAGES,	// entity messages
			VOICE,			// voice data
			STRINGTABLE,	// a stringtable update
			MOVE,			// client move cmds
			STRINGCMD,		// string command
			SIGNON,			// various signondata
			TOTAL,			// must be last and is not a real group
		};
		
		VFUNCR0( GetName, Index2Offset( 0 ), const char* );						// get channel name
		VFUNCR0( GetAddress, Index2Offset( 1 ), const char* );					// get channel IP address as string
		VFUNCR0( GetTime, Index2Offset( 2 ), float );							// current net time
		VFUNCR0( GetTimeConnected, Index2Offset( 3 ), float );					// get connection time in seconds
		VFUNCR0( GetBufferSize, Index2Offset( 4 ), int );						// netchannel packet history size
		VFUNCR0( GetDataRate, Index2Offset( 5 ), int );							// send data rate in byte/sec
		VFUNCR0( IsLoopback, Index2Offset( 6 ), bool );							// true if loopback channel
		VFUNCR0( IsTimingOut, Index2Offset( 7 ), bool );						// true if timing out
		VFUNCR0( IsPlayback, Index2Offset( 8 ), bool );							// true if demo playback
		VFUNCR1( GetLatency, Index2Offset( 9 ), float, int );					// current latency (RTT), more accurate but jittering
		VFUNCR1( GetAvgLatency, Index2Offset( 10 ), float, int );				// average packet latency in seconds
		VFUNCR1( GetAvgLoss, Index2Offset( 11 ), float, int );					// avg packet loss[0..1]
		VFUNCR1( GetAvgChoke, Index2Offset( 12 ), float, int );					// avg packet choke[0..1]
		VFUNCR1( GetAvgData, Index2Offset( 13 ), float, int );					// data flow in bytes/sec
		VFUNCR1( GetAvgPackets, Index2Offset( 14 ), float, int );				// avg packets/sec
		VFUNCR1( GetTotalData, Index2Offset( 15 ), int, int );					// total flow in/out in bytes
		VFUNCR1( GetSequenceNr, Index2Offset( 16 ), int, int );					// last send seq number
		VFUNCR2( IsValidPacket, Index2Offset( 17 ), bool, int, int );			// true if packet was not lost/dropped/chocked/flushed
		VFUNCR2( GetPacketTime, Index2Offset( 18 ), float, int, int );			// time when packet was send
		VFUNCR3( GetPacketBytes, Index2Offset( 19 ), int, int, int, int );		// group size of this packet
		VFUNCR3( GetStreamProgress, Index2Offset( 20 ), bool, int, int, int );	// TCP progress if transmitting

		inline float GetPing( )
		{
			return GetLatency( 0 ) + GetLatency( 1 );
		}
	};
};

#endif //__INETCHANNELINFO_H__