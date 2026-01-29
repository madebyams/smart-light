//
// Created by Amsakan on 28.01.26.
//

#ifndef DETECTIONMODULE_MQTT_HPP
#define DETECTIONMODULE_MQTT_HPP
namespace net {
    namespace mqtt {
        void init();
        void reconnect();
        bool is_connected();
        void write(std::string message);
    }
}
#endif //DETECTIONMODULE_MQTT_HPP