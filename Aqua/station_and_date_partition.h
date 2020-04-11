#pragma once

#include <string>
#include "date.h"
#include "observation.h"

namespace aqua {

    struct station_and_date_partition {
    public:
        explicit station_and_date_partition(const observation& ob) :
            m_weather_station(ob.m_weather_station), m_date(ob.m_time_of_observation.get_date()) {}
        
        bool operator<(const station_and_date_partition& rhs) const noexcept {
            return 
                m_date < rhs.m_date ||
                (m_date == rhs.m_date && m_weather_station < rhs.m_weather_station);
        }

        std::string m_weather_station;
        date_t m_date;
    }; // struct station_and_date_partition
    
} // namespace aqua