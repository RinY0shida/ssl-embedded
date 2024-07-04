/**
 * @file motor_control.h
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief ロボットの4輪制御用のクラス
 * @date 2024-07-02
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H 

#include <cstdint>

class MotorControl{
public:
    MotorControl();
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
    int8_t velocityControl(double degree, uint32_t velocity, uint8_t *motor_transmit_data, uint8_t *motor_receive_data);

private:

};

#endif //MOTOR_CONTROL_H