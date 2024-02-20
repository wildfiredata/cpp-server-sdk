#ifndef CPP_WILDFIRE_ANALYTICS_API_H
#define CPP_WILDFIRE_ANALYTICS_API_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/timeb.h>

#include <mutex>
#include "TDConsumer.h"
#include "TDUtils.h"

/**
 * \mainpage
 * # WildfireData SDK for C++ server
 * 

 * ---
 */

namespace wildfireDataAnalytics {

    class TDAnalytics {
        
    private:
        TDConsumer& m_consumer;
        bool m_enableUUID;
        TDPropertiesNode m_supperProperties;
        std::mutex m_mutex;

    public:
        explicit TDAnalytics(TDConsumer &consumer);
        /**
         * Construct
         * @param consumer Data consumer
         * @param enableUUID Whether the event automatically carries a uuid
         */
        TDAnalytics(TDConsumer &consumer, bool enableUUID);

        /**
         * Report normal event
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param eventName event name
         * @param properties event properties
         */
        void track(const std::string &accountId, const std::string &distinctId, const std::string &eventName, const TDPropertiesNode &properties);

        /**
         * Report first event
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param eventName event name
         * @param properties event properties
         */
        void track_first(const std::string &accountId, const std::string &distinctId, const std::string &eventName, const TDPropertiesNode &properties);

        /**
         * Report updatable event
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param eventName event name
         * @param eventId event ID
         * @param properties event properties
         */
        void track_update(const std::string &accountId, const std::string &distinctId, const std::string &eventName, const std::string &eventId, const TDPropertiesNode &properties);


        /**
         * Report overwrite event
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param eventName event name
         * @param eventId event ID
         * @param properties event properties
         */
        void track_overwrite(const std::string &accountId, const std::string &distinctId, const std::string &eventName, const std::string &eventId, const TDPropertiesNode &properties);

        /**
         * Set the user attribute. If the attribute already exists, it is overwritten; otherwise, the newly created user attribute
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param properties event properties
         */
        void user_set(const std::string &accountId, const std::string &distinctId, const TDPropertiesNode &properties);

        /**
         * Set the user attribute. If the attribute already exists, the operation has no effect.
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param properties event properties
         */
        void user_setOnce(const std::string &accountId, const std::string &distinctId, const TDPropertiesNode &properties);

        /**
         * User attribute modification, only supports the interface for adding digital attributes
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param properties event properties
         */
        void user_add(const std::string &accountId, const std::string &distinctId, const TDPropertiesNode &properties);

        /**
         * The user's array type attribute append
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param properties event properties
         */
        void user_append(const std::string &accountId, const std::string &distinctId, const TDPropertiesNode &properties);

        /**
         * The attribute of the user's array type is deduplicated and appended
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param properties event properties
         */
        void user_uniqAppend(const std::string &accountId, const std::string &distinctId, const TDPropertiesNode &properties);

        /**
         * Delete user-specified attributes
         * @param accountId Account ID
         * @param distinctId visitor ID
         * @param properties event attribute, the value corresponding to the key is set to 0, that is, the key attribute of the user is deleted
         */
        void user_unset(const std::string &accountId, const std::string &distinctId, const TDPropertiesNode &properties);

        /**
         * Delete a user, this operation is irreversible
         * @param accountId Account ID
         * @param distinctId visitor ID
         */
        void user_del(const std::string &accountId, const std::string &distinctId);

        /**
         * Immediately report data to the receiving end
         */
        void flush();

        /**
         * Close and exit all threads of sdk, all local data will be cleared before stopping
         */
        void close();

        /**
         * Set static public properties
         * @param supperProperties static public properties
         */
        void setSupperProperties(const TDPropertiesNode &supperProperties);

        /**
         * Clear public event attributes
         */
        void clearSuperProperties();

    private:
        void add(const std::string &accountId, const std::string &distinctId, const std::string &eventType, const std::string &eventName, const std::string &eventId, const TDJsonObject& properties);

        static bool transferWithStringMap(const std::string &key, TDJsonObject &sourceProperties, TDJsonObject &destinationProperties);
    };


}

#endif //CPP_WILDFIRE_ANALYTICS_API_H
