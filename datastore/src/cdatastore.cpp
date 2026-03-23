#include "../include/cdatastore.hpp"
#include <cstdint>

bool CDataStore::ValidateRead(uint32_t pos, int numBytes) {
	if (pos + numBytes > m_size) {
		// Mark as overflowed
		m_readPos = m_size + 1;
		return false;
	}
	return true;
}

uint8_t CDataStore::GetInt8() {
	uint8_t val = 0;
	if (ValidateRead(m_readPos, 1)) {
		val = m_buffer[m_readPos - m_base];
		m_readPos += 1;
	}
	return val;
}

uint16_t CDataStore::GetInt16() {
	uint16_t val = 0;
	if (ValidateRead(m_readPos, 2)) {
		val = *reinterpret_cast<uint16_t*>(&m_buffer[m_readPos - m_base]);
		m_readPos += 2;
	}
	return val;
}

uint32_t CDataStore::GetInt32() {
	uint32_t val = 0;
	if (ValidateRead(m_readPos, 4)) {
		val = *reinterpret_cast<uint32_t*>(&m_buffer[m_readPos - m_base]);
		m_readPos += 4;
	}
	return val;
}

uint64_t CDataStore::GetInt64() {
	uint64_t val = 0;
	if (ValidateRead(m_readPos, 8)) {
		val = *reinterpret_cast<uint64_t*>(&m_buffer[m_readPos - m_base]);
		m_readPos += 8;
	}
	return val;
}

const uint8_t* CDataStore::GetBuffer(int numBytes) {
	const uint8_t* ptr = nullptr;
	if (ValidateRead(m_readPos, numBytes)) {
		ptr = &m_buffer[m_readPos - m_base];
		m_readPos += numBytes;
	}
	return ptr;
}

