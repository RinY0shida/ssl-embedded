/**
 * @file motor_control.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief ロボットの4輪制御用のクラス
 * @date 2024-07-02
 */

#include "motor_control.h"
#include <math.h>
#include <iostream>

MotorControl::MotorControl(){
}

MotorControl::~MotorControl(){
}

int8_t MotorControl::velocityControl(double degree, uint32_t velocity, uint8_t *motor_transmit_data, uint8_t *motor_receive_data){
    if (velocity >= 10000 && velocity < 0) return -1;

    double motor_fwd_right = sinf((degree - 45.0) * M_PI / 180);
    double motor_back_right = sinf((degree - 135.0) * M_PI / 180);
    double motor_back_left = sinf((degree - 225.0) * M_PI / 180);
    double motor_fwd_left = sinf((degree - 315.0) * M_PI / 180);

    double motor_max_power = 0;
    motor_max_power = fmax(fabs(motor_fwd_right), fabs(motor_back_right));
    motor_max_power = fmax(fabs(motor_back_left), motor_max_power);
    motor_max_power = fmax(fabs(motor_fwd_left), motor_max_power);

    motor_fwd_right = (motor_fwd_right / motor_max_power) * velocity;
    motor_back_right = (motor_back_right  / motor_max_power) * velocity;
    motor_back_left = (motor_back_left / motor_max_power) * velocity;
    motor_fwd_left = (motor_fwd_left  / motor_max_power) * velocity;

     // 上位ビットと下位ビットに分けて送信用の配列に代入
    motor_transmit_data[0] = (static_cast<int16_t>(motor_fwd_right) >> 8) & 0xff;
    motor_transmit_data[1] = static_cast<int16_t>(motor_fwd_right) & 0xff;
    motor_transmit_data[2] = (static_cast<int16_t>(motor_back_right) >> 8) & 0xff;
    motor_transmit_data[3] = static_cast<int16_t>(motor_back_right) & 0xff;
    motor_transmit_data[4] = (static_cast<int16_t>(motor_back_left) >> 8) & 0xff;
    motor_transmit_data[5] = static_cast<int16_t>(motor_back_left) & 0xff;
    motor_transmit_data[6] = (static_cast<int16_t>(motor_fwd_left) >> 8) & 0xff;
    motor_transmit_data[7] = static_cast<int16_t>(motor_fwd_left) & 0xff;
    return 0;
}