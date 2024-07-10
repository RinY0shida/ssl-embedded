/**
 * @file pid_controller.h
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief PID制御を行うクラス 
 * @date 2024-07-07
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <cstdint>

class PidController{
public:
    PidController(const double p_gain, const double i_gain, const double d_gain) 
     : p_gain_(p_gain),
       i_gain_(i_gain), 
       d_gain_(d_gain){
    }

    ~PidController(){
    }

    /**
     * @brief PID制御を行う関数
     * @param target_value 目標値
     * @param current_value 現在値
     * @param control_cycle 制御周期
     * @return int16_t
     * @retval 制御値
     */
    double PidControl(double target_value, double current_value, double control_cycle){
        double error = target_value - current_value;
        double differential = (error - pre_error_) / control_cycle;
        integral_ += (error + pre_error_) * control_cycle / 2;
        pre_error_ = error;
        if (pre_target_value_ != target_value){
            integral_ = 0;
        }
        if (target_value == current_value){
            integral_ = 0; // TODO 範囲を大きくしてもいい
        }
        pre_target_value_ = target_value;
        return p_gain_ * error + i_gain_ * integral_ + d_gain_ * differential;
    }

private:
    const double p_gain_;
    const double i_gain_;
    const double d_gain_;
    double pre_error_;
    double pre_target_value_;
    double integral_;
};
#endif //PID_CONTROLLER_H