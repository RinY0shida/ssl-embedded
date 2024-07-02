/**
 * @file main.cc
 * @author RinYoshida (tororo1219@gmail.com)
 * @brief robotを動かすための処理を書くfile
 * @date 2024-07-02 
 */

const string can_interface_name = "can0";

CanCommunication *can_communication = nullptr;
can_communication = new(CanCommunication(can_interface_name));


int main(){
    while(true){
        maintask();
    }
}

maintask(){
    // 一旦buildcheck用に書いている。
    uint16_t std_id = 201;
    uint8_t data[8] = {0};
    can_communication->socket_can_send(std_id, data, 8);
}