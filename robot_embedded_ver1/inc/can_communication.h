/**
 * @file can_communication.h
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief m2006とubuntuがcan通信を行うためのヘッダファイル
 * @date 2024-07-01
 */

#ifndef CAN_COMMUNICATION_H
#define CAN_COMMUNICATION_H

#include <iostream>
#include <cstdint>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

class CanCommunication{
public:
    CanCommunication(const string can_interface_name);
    ~CanCommunication();

    /**
     * @brief CAN通信を行うための関数
     * @param can_id
     * @param can_data 
     */
    void socketCanSend(const uint16_t can_id, const uint8_t *can_data);

public:
    string can_interface_name_; // CANインターフェース名
    int socket_can_; // CAN raw socket
    struct sockaddr_can addr_;
    struct can_frame frame_;
    struct ifreq ifr_;
};

#endif // CAN_COMMUNICATION_H