/* FastEmbedded Microcontroller Library
 * Copyright (c) 2018 Gene Kong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef FASTEMBEDDED_SERVICE_IMPL_H__
#define FASTEMBEDDED_SERVICE_IMPL_H__

#include <Arduino.h>
#include <algorithm>

namespace FEmbed {

/**
 * ServiceBroadcast Base class for service.
 */
struct ServiceBroadcast {
    uint32_t bc_no;        //   broadcast normal number.
};

/**
 * ServiceBroadcastListener Base class for service.
 */
class ServiceBroadcastListener {
 public:
    virtual ~ServiceBroadcastListener() {};
    virtual void onBroadcast(uint32_t type, ServiceBroadcast *bc) = 0 ;
};

/**
 * Service
 *
 * Service is component which user can extends it's function and global used.
 */
template <typename T>
class Service : public std::enable_shared_from_this<T>
{
    public:
        static std::shared_ptr<T> &get() {
            static std::shared_ptr<T> instance = nullptr;
            if(!instance)
            {
                instance.reset(new T());
                assert(instance);
            }
            return instance;
        }

        /**
         * Register Service Broadcast Listener
         *
         * @param listen object which want get broadcast from service.
         * @return register OK return true else false.
         */
        bool registerServiceBroadcastListener(ServiceBroadcastListener *listen)
        {
            auto it = std::find(m_listeners.begin(), m_listeners.end(), listen);
            if (it == m_listeners.end()) {
                m_listeners.push_back(listen);
                return true;
            }
            return false;
        }

        /**
         * Unregister Service Broadcast Listener
         * @param listen  object which want get broadcast from service.
         */
        void unregisterServiceBroadcastListener(ServiceBroadcastListener *listen)
        {
            m_listeners.remove(listen);
        }

        /**
         * Service must manual deliver broadcast to all listener
         *
         * @param bc broadcast object.
         */
        void deliverBroadcast(uint32_t type, ServiceBroadcast *bc)
        {
            for(auto it = std::begin(m_listeners); it != std::end(m_listeners); ++it )
            {
                (*it)->onBroadcast(type, bc);
            }
        }
    protected:
        std::list<ServiceBroadcastListener *> m_listeners;
    };
}
#endif
