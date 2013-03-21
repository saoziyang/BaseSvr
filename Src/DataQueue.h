/* 
 * File:   DataQueue.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 2:42 PM
 */

#ifndef DATAQUEUE_H
#define	DATAQUEUE_H

#include <deque>
#include "Common.h"

class CDataQueue
{
	typedef boost::shared_ptr<CDataQueue> dataQueuePtr_t;
public:
	CDataQueue(){}
	~CDataQueue(){}

public:
	void Append(void *pData, int nLen) {
		m_data.insert(m_data.end(), (uint8_t *)pData, (uint8_t *)pData + nLen);
	}

	void Clear() {
		m_data.clear();
	}

	bool IsEmpty() {
		return m_data.empty();
	}

	int GetSize() {
		return m_data.size();
    }

	void PopFront(int nSize) {
		std::deque<uint8_t>::iterator cIt = m_data.begin();
		std::advance(cIt, nSize);
		m_data.erase(m_data.begin(), cIt);
	}

    void CopyTo(const dataBufferPtr_t & pPacket, int nSize) {
        std::deque<uint8_t>::iterator it = m_data.begin();
        std::advance(it, nSize);
        pPacket->insert(pPacket->begin(), m_data.begin(), it);
    }

    void CopyTo(void * pData, int nSize) {
        std::deque<uint8_t>::iterator it = m_data.begin();
        std::advance(it, nSize);
        dataBuffer_t vect;
        vect.insert(vect.begin(), m_data.begin(), it);
        memcpy(pData, &vect.front(), nSize);
    }

	int FindDelimiter(uint8_t * p, int nSize)
	{
		if (nSize < 1 || nSize > int(m_data.size()))
			return -1;
		int  pos;
		std::deque<uint8_t>::const_iterator cIt = m_data.begin();
		for (cIt += nSize - 1; cIt != m_data.end(); ++cIt) {
			for (pos = 0; pos < nSize; ++pos) {
				if (p[pos] != *(cIt - nSize + 1 + pos) )
					break;
			}
			if (pos == nSize)
				return (int)(cIt - m_data.begin() + 1);
		}
		return -1;
	}
	
private:
	std::deque<uint8_t> m_data;
};

typedef boost::shared_ptr<CDataQueue> dataQueuePtr_t;
typedef std::map<int, dataQueuePtr_t> dataQueueMap_t;

#endif	/* DATAQUEUE_H */

