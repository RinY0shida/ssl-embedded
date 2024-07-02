/**
 * @file main.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief robotを動かすための処理を書くfile
 * @date 2024-07-02 
 */
#include "main.h"
#include "can_communication.h"

#include <cstdint>
#include <memory>

const std::string can_interface_name = "can0";

std::unique_ptr<CanCommunication> can_communication = std::make_unique<CanCommunication>(can_interface_name);

int main(){
    while(true){
        maintask();
    }
}

void maintask(){
    // 一旦buildcheck用に書いている。
    uint16_t can_id = 200;
    uint8_t data[8] = {0};
    can_communication->socketCanSend(can_id, data, 8);
}