/* 
 * File:   SocketInfo.h
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 13, 2012, 12:11 AM
 */

#ifndef SOCKETINFO_H
#define	SOCKETINFO_H

struct sockInfo_t {
public:
	int      Sock;
    uint32_t IP;
    uint16_t Port;

	sockInfo_t(int s, uint32_t ip, uint16_t port): Sock(s), IP(ip), Port(port){}

    bool operator<(const sockInfo_t &info) const {
        if (IP < info.IP) {
            return true;
        } else if (IP == info.IP) {
            if (Port < info.Port) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const sockInfo_t &info) const {
        return (IP == info.IP) && (Port == info.Port); 
    }
};

#endif	/* SOCKETINFO_H */

