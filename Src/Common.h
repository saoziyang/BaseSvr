/* 
 * File:   Common.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 8, 2012, 4:44 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#include <stdio.h>
#include <vector>
#include <queue>

#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

typedef boost::mutex                        mutex_t;
typedef boost::mutex::scoped_lock           mutex_locker_t;
typedef boost::condition                    wait_t;
typedef boost::shared_mutex             	locker_t;
typedef boost::shared_lock<locker_t> 		read_locker_t;
typedef boost::unique_lock<locker_t> 		write_locker_t;

typedef std::vector<uint8_t>              	dataBuffer_t;
typedef boost::shared_ptr<dataBuffer_t>   	dataBufferPtr_t;
 
#define BIND boost::bind
#define LOCK_READ_SECTION()  read_locker_t  _lk(m_lock);
#define LOCK_WRITE_SECTION() write_locker_t _lk(m_lock);
#define WAIT_SECTION()                      m_wait.wait(_lk);
#define NOTIFY_SECTION()                    m_wait.notify_one();

enum DATA_PARSE_RESULT {
    DPR_UNKNOWN, DPR_EMPTY, DPR_INVALID, DPR_NOT_COMPLETE, DPR_GOOD_PACKET
};

namespace DATA_SEND_RESULT {
	enum {
		NO_DATA, SEND_PARTIAL, SEND_COMPLETE, SEND_ERROR
	};
}

#endif	/* COMMON_H */

