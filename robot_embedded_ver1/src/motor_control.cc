/**
 * @file motor_control.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief ロボットの4輪制御用のクラス
 * @date 2024-07-02
 */

#include <math.h>
#include <iostream>

#include "motor_control.h"

MotorControl::MotorControl(PidController pid_controller)
 : pid_controller_(pid_controller){
}

MotorControl::~MotorControl(){
}

int8_t MotorControl::velocityControl(double degree, uint32_t velocity, uint8_t *motor_transmit_data, std::vector<uint8_t> motor_receive_data){
    if (velocity >= 10000 && velocity < 0) return -1;

     // rpmの値を取得
    double motor_fwd_right_velocity = (static_cast<uint16_t>(motor_receive_data[0]) << 8) | motor_receive_data[1]; // [rpm]
    double motor_back_right_velocity = (static_cast<uint16_t>(motor_receive_data[2]) << 8) | motor_receive_data[3]; // [rpm]
    double motor_back_left_velocity = (static_cast<uint16_t>(motor_receive_data[4]) << 8) | motor_receive_data[5]; // [rpm]
    double motor_fwd_left_velocity = (static_cast<uint16_t>(motor_receive_data[6]) << 8) | motor_receive_data[7]; // [rpm]

     // rpmをm/sに変換
    motor_fwd_right_velocity_ = (motor_fwd_right_velocity * wheel_diameter_ * M_PI) / 60; // [m/s]
    motor_back_right_velocity_ = (motor_back_right_velocity * wheel_diameter_ * M_PI) / 60; // [m/s]
    motor_back_left_velocity_ = (motor_back_left_velocity * wheel_diameter_ * M_PI) / 60; // [m/s]
    motor_fwd_left_velocity_ = (motor_fwd_left_velocity * wheel_diameter_ * M_PI) / 60; // [m/s]

    double motor_fwd_right_vector = sinf((degree - 45.0) * M_PI / 180);
    double motor_back_right_vector = sinf((degree - 135.0) * M_PI / 180);
    double motor_back_left_vector = sinf((degree - 225.0) * M_PI / 180);
    double motor_fwd_left_vector = sinf((degree - 315.0) * M_PI / 180);

    double motor_max_vector = 0;
    motor_max_vector = fmax(fabs(motor_fwd_right_vector), fabs(motor_back_right_vector));
    motor_max_vector = fmax(fabs(motor_back_left_vector), motor_max_vector);
    motor_max_vector = fmax(fabs(motor_fwd_left_vector), motor_max_vector);

    motor_fwd_right_velocity_target_ = (motor_fwd_right_vector / motor_max_vector) * velocity; // [m/s]
    motor_back_right_velocity_target_ = (motor_back_right_vector  / motor_max_vector) * velocity; // [m/s]
    motor_back_left_velocity_target_ = (motor_back_left_vector / motor_max_vector) * velocity; // [m/s]
    motor_fwd_left_velocity_target_ = (motor_fwd_left_vector  / motor_max_vector) * velocity; // [m/s]

    motor_fwd_right_velocity_pid = pid_controller->pidControl(motor_fwd_right_velocity_target_, motor_fwd_right_velocity_, 0.01);
    motor_back_right_velocity_pid = pid_controller->pidControl(motor_back_right_velocity_target_, motor_back_right_velocity_, 0.01);
    motor_back_left_velocity_pid = pid_controller->pidControl(motor_back_left_velocity_target_, motor_back_left_velocity_, 0.01);
    motor_fwd_left_velocity_pid = pid_controller->pidControl(motor_fwd_left_velocity_target_, motor_fwd_left_velocity_, 0.01);

     // 上位ビットと下位ビットに分けて送信用の配列に代入
    motor_transmit_data[0] = (static_cast<int16_t>(motor_fwd_right_velocity_pid) >> 8) & 0xff;
    motor_transmit_data[1] = static_cast<int16_t>(motor_fwd_right_velocity_pid) & 0xff;
    motor_transmit_data[2] = (static_cast<int16_t>(motor_back_right_velocity_pid) >> 8) & 0xff;
    motor_transmit_data[3] = static_cast<int16_t>(motor_back_right_velocity_pid) & 0xff;
    motor_transmit_data[4] = (static_cast<int16_t>(motor_back_left_velocity_pid) >> 8) & 0xff;
    motor_transmit_data[5] = static_cast<int16_t>(motor_back_left_velocity_pid) & 0xff;
    motor_transmit_data[6] = (static_cast<int16_t>(motor_fwd_left_velocity_pid) >> 8) & 0xff;
    motor_transmit_data[7] = static_cast<int16_t>(motor_fwd_left_velocity_pid) & 0xff;
    return 0;
}