/**
 * @file can_communication.h
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief ubuntuとペリフェラルがcan通信を行うためのヘッダファイル
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
    CanCommunication(const std::string can_interface_name);
    ~CanCommunication();

    /**
     * @brief CAN通信で送信を行うための関数
     * @param can_id
     * @param can_data 
     * @return int8_t
     * @retval 0: 正常終了
     * @retval 正: 正常終了　送信バイト数
     * @retval 負: 送信失敗
     */
    int8_t SocketCanSend(const uint32_t can_id, const uint8_t *can_data, const uint8_t size);

    /**
     * @brief CAN通信で受信を行うための関数
     * @param can_id 
     * @param can_data 
     * @param size
     * @return int8_t 
     * @retval 0: 正常終了
     * @retval 正: 正常終了　受信バイト数
     * @retval 負: 受信失敗
     */
    int8_t SocketCanReceive(uint32_t &can_id, uint8_t *can_data, uint8_t &size);

private:
    std::string can_interface_name_; // CANインターフェース名
    int socket_can_; // CAN raw socket
    struct sockaddr_can addr_;
    struct can_frame frame_;
    struct ifreq ifr_;
};

#endif // CAN_COMMUNICATION_H