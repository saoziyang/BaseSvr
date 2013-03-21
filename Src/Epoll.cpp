/* 
 * File:   Epoll.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 12, 2012, 9:04 PM
 */

#include "Epoll.h"

int CEpoll::Create(int type, int id) {
    if ((m_efd = epoll_create1(0)) < 0)
        return errno;

    fcntl(m_efd, F_SETFD, FD_CLOEXEC);
    m_evList = (epoll_event *) calloc(m_maxEvents, sizeof (struct epoll_event));
    if (!m_evList)
        return errno;

    m_type = type;
    m_id = id;
    return 0;
}

bool CEpoll::IsOpen()
{
	return (m_efd != -1);
}

void CEpoll::Close() {
	if (m_efd != -1)
		close(m_efd);
    m_efd = -1;
}

int CEpoll::AddEvent(int fd, epoll_event *pEv) {
    if (!epoll_ctl(m_efd, EPOLL_CTL_ADD, fd, pEv))
        return 0;

    if (errno == EEXIST) {
        if (!epoll_ctl(m_efd, EPOLL_CTL_MOD, fd, pEv))
            return 0;
    }
    return errno;
}

void CEpoll::Run(const callback_t &cb) {
    while (1) {
        int nEvent;
        nEvent = epoll_wait(m_efd, m_evList, m_maxEvents, -1);
        if (-1 == nEvent) {
            printf("Error: epoll_wait (type=%d, id=%d): %d.\n", m_type, m_id, errno);
        }

        for (int i = 0; i < nEvent; ++i) {
        	/*
            if (m_evList[i].events & EPOLLERR || m_evList[i].events & EPOLLHUP) {
                close(m_evList[i].data.fd);
                continue;
            }
            */

            cb(m_evList[i]);
        }

    }
}
