#include "Main.h"
#include "Macro.h"

Macro g_Macro;

void Macro::SaveMacro( CRecord* movement, Vector *DrawPath, int &TickEnd, const char* filename )
{
	FILE* fp = fopen( filename, /*wb+*/XorStr<0x14,4,0x56313A91>("\x63\x77\x3D"+0x56313A91).s );
	if( fp != NULL )
	{
		fwrite( &TickEnd, sizeof( int ), 1, fp );
		fwrite( DrawPath, sizeof( Vector ), TickEnd--, fp );
		fwrite( movement, sizeof( CRecord ), TickEnd--, fp );
		fclose( fp );
	}
	else
		MessageBoxA( 0, /*Failed to save macro*/XorStr<0x6E,21,0xCFD21F4C>("\x28\x0E\x19\x1D\x17\x17\x54\x01\x19\x57\x0B\x18\x0C\x1E\x5C\x10\x1F\x1C\xF2\xEE"+0xCFD21F4C).s, /*MovementRecorder*/XorStr<0x3F,17,0xC27DDFA9>("\x72\x2F\x37\x27\x2E\x21\x2B\x32\x15\x2D\x2A\x25\x39\x28\x28\x3C"+0xC27DDFA9).s, 0 );
		//printf( "Failed to save macro\n" );
}

void Macro::ReadMacro( CRecord* movement, Vector *DrawPath, int &TickEnd, const char* filename )
{
	FILE* fp = fopen( filename, /*rb+*/XorStr<0xF0,4,0x6F3A6A40>("\x82\x93\xD9"+0x6F3A6A40).s );
	if( fp != NULL )
	{
		fread( &TickEnd, sizeof( int ), 1, fp );
		fread( DrawPath, sizeof( Vector ), TickEnd--, fp );
		fread( movement, sizeof( CRecord ), TickEnd--, fp );
		fclose( fp );
	}
	else
		MessageBoxA( 0, /*Failed to load macro*/XorStr<0xA1,21,0xCD5C5B8F>("\xE7\xC3\xCA\xC8\xC0\xC2\x87\xDC\xC6\x8A\xC7\xC3\xCC\xCA\x8F\xDD\xD0\xD1\xC1\xDB"+0xCD5C5B8F).s, /*MovementRecorder*/XorStr<0x12,17,0xBA7F759B>("\x5F\x7C\x62\x70\x7B\x72\x76\x6D\x48\x7E\x7F\x72\x6C\x7B\x45\x53"+0xBA7F759B).s, 0 );
		//printf( "Failed to load macro, maybe wrong filename?\n" );
}

void Macro::ReadMacro2( SRecord* movement, int &tick_count, Vector &StartPosition, const char* filename )
{
	FILE* fp = fopen( filename, /*rb+*/XorStr<0xFD,4,0x0CD0031B>("\x8F\x9C\xD4"+0x0CD0031B).s );
	if( fp != NULL )
	{
		fread( &tick_count, sizeof( int ), 1, fp );//Header Tick_count
		fread( &StartPosition, sizeof( Vector ), 1, fp );//Header Start Position
		fread( movement, sizeof( SRecord ), tick_count--, fp );
		fclose( fp );
	}
	else
		MessageBoxA( 0, /*Failed to load macro*/XorStr<0x69,21,0xBC49DB9A>("\x2F\x0B\x02\x00\x08\x0A\x4F\x04\x1E\x52\x1F\x1B\x14\x12\x57\x15\x18\x19\x09\x13"+0xBC49DB9A).s, /*MovementRecorder*/XorStr<0x5F,17,0x92AC5303>("\x12\x0F\x17\x07\x0E\x01\x0B\x12\x35\x0D\x0A\x05\x19\x08\x08\x1C"+0x92AC5303).s, 0 );
		//printf( "Failed to load macro, maybe wrong filename?\n" );
}