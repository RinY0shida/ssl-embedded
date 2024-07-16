/**
 * @file main.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief robotを動かすための処理を書くfile
 * @date 2024-07-02 
 */
#include "main.h"
#include "can_communication.h"
#include "motor_control.h"
#include "pid_controller.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <array>
#include <thread>

const std::string can_interface_name = "can0";

std::unique_ptr<CanCommunication> can_communication = std::make_unique<CanCommunication>(can_interface_name);
std::unique_ptr<PidController> pid_controller = std::make_unique<PidController>(0.1, 0.01, 0.01);
std::unique_ptr<MotorControl> motor_control = std::make_unique<MotorControl>(std::move(pid_controller), 50);
int main(){
    while(true){
        maintask();
    }
}

void maintask(){
    //pid_velocity_controller->PidControl(0, 10, 0.01);
    
    // 一旦buildcheck用に書いている。
    //uint16_t can_id = 200;
    // uint8_t data[8] = {0};
    // uint32_t can_id;
    // //std::array<uint8_t, 8> data;
    // uint8_t size;
    // int err = 0;
    //can_communication->socketCanSend(can_id, data, 8);
//     err = can_communication->socketCanReceive(can_id, data, size);
//     std::cout << "can_id: " << can_id << std::endl;
//     for (int i = 0; i < size; i++){
//         std::cout << "data[" << i << "]: " << static_cast<int>(data[i]) << std::endl;
//     }
 }