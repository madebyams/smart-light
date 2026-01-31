//
// Created by Amsakan on 28.01.26.
//

#ifndef DETECTIONMODULE_MQTT_HPP
#define DETECTIONMODULE_MQTT_HPP
#include <PubSubClient.h>

namespace net {
    class mqtt {
        PubSubClient* mqtt_client_;
    public:
        explicit mqtt(PubSubClient* mqtt_client);
        void init();
        void reconnect();
        bool is_connected();
        void write(std::string message);
    };
}
#endif //DETECTIONMODULE_MQTT_HPP