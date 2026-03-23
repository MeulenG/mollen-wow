#ifndef __CDATASTORE_HPP
#define __CDATASTORE_HPP
#include <cstdint>

class CDataStore {
	uint8_t* m_buffer;
	uint32_t m_base;		// base offset
	uint32_t m_capacity;	// allocated buffer size
	uint32_t m_size;		// current data length
	uint32_t m_readPos;		// read cursor

public:
	bool ValidateRead(uint32_t pos, int numBytes);
	uint8_t GetInt8();
	uint16_t GetInt16();
	uint32_t GetInt32();
	uint64_t GetInt64();
	const uint8_t* GetBuffer(int numBytes);
};

#endif

