/**
 * @file can_communication.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief m2006とubuntuがcan通信を行うためのクラス
 * @date 2024-07-01
 */

#include "can_communication.h"

CanCommunication::CanCommunication(const std::string can_interface_name) : can_interface_name_(can_interface_name){
    socket_can_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    strcpy(ifr_.ifr_name, can_interface_name_.c_str());
    ioctl(socket_can_, SIOCGIFINDEX, &ifr_);
    memset(&addr_, 0, sizeof(addr_));
    addr_.can_family = AF_CAN;
    addr_.can_ifindex = ifr_.ifr_ifindex;
    bind(socket_can_, (struct sockaddr *)&addr_, sizeof(addr_));
}

CanCommunication::~CanCommunication(){
    close(socket_can_);
}

int8_t CanCommunication::socketCanSend(const uint16_t can_id, const uint8_t *can_data, const uint8_t size){
    frame_.can_id = can_id;
    frame_.can_dlc = size;
    for (int i = 0; i < size; i++){
        frame_.data[i] = can_data[i];
    }
    int8_t write_err_check = write(socket_can_, &frame_, sizeof(struct can_frame));
    return write_err_check;
}

