/**
 * @file motor_control.h
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief ロボットの4輪制御用のクラス
 * @date 2024-07-02
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H 

#include <cstdint>
#include <vector>
#include <memory>

#include "pid_controller.h"

class MotorControl{
public:
    MotorControl(std::unique_ptr<PidController> pid_controller_, const uint32_t wheel_diameter);
    ~MotorControl();

    /**
     * @brief ロボットの速度制御をする関数
     * @details 将来的にはモータの受信データからm/sを導出するようにしてフィードバックをかける
     * @param degree 走行方向　0が正面　90が右　-90が左
     * @param velocity 速度
     * @return int8_t
     * @retval 0: 正常終了
     * @retval -1: 速度値の上限を超えた　-10,000 ~ 10,000
     */
    int8_t VelocityControl(double degree, uint32_t velocity, uint8_t *motor_transmit_data, std::vector<uint8_t> motor_receive_data);

private:
    double motor_fwd_right_velocity_target_;
    double motor_back_right_velocity_target_;
    double motor_back_left_velocity_target_;
    double motor_fwd_left_velocity_target_;

    //PidController *pid_controller;
    std::unique_ptr<PidController> pid_controller;
    const uint32_t wheel_diameter_;
};

#endif //MOTOR_CONTROL_H