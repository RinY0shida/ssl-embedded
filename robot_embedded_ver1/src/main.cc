/**
 * @file main.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief robotを動かすための処理を書くfile
 * @date 2024-07-02 
 */
#include "main.h"
#include "can_communication.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <array>

const std::string can_interface_name = "can0";

std::unique_ptr<CanCommunication> can_communication = std::make_unique<CanCommunication>(can_interface_name);

int main(){
    while(true){
        maintask();
    }
}

void maintask(){
    // 一旦buildcheck用に書いている。
    //uint16_t can_id = 200;
    uint8_t data[8] = {0};
    uint32_t can_id;
    //std::array<uint8_t, 8> data;
    uint8_t size;
    int err = 0;
    //can_communication->socketCanSend(can_id, data, 8);
    err = can_communication->socketCanReceive(can_id, data, size);
    std::cout << "can_id: " << can_id << std::endl;
    for (int i = 0; i < size; i++){
        std::cout << "data[" << i << "]: " << static_cast<int>(data[i]) << std::endl;
    }
}