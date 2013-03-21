/* 
 * File:   WaitChannelManager.h
 * Author: ke
 *
 * Created on November 14, 2012, 6:33 PM
 */

#ifndef WAITCHANNELMANAGER_H
#define	WAITCHANNELMANAGER_H

#include "WaitChannel.h"

class CWaitChannelManager {
	typedef std::vector<CWaitChannel *> waitChannelVec_t;
public:
    CWaitChannelManager(): m_nWaitChannel(0){}
    ~CWaitChannelManager(){}

	void Init(int n);
	void Push(const int &fd);
	bool GetSock(int idx, int &fd);
	void Stop();

private:
	waitChannelVec_t m_channelVec;	
	int 			 m_nWaitChannel;
};

extern CWaitChannelManager WaitChannelManager;

#endif	/* WAITCHANNELMANAGER_H */

