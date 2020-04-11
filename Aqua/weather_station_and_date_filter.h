#pragma once

#include <string>
#include "date.h"
#include "observation.h"

namespace aqua {

    struct weather_station_and_date_filter {
        explicit weather_station_and_date_filter(const std::string& name, const date_t& date) : m_name(name), m_date(date) {}
        
        bool operator()(const observation& observation) const noexcept {
            return observation.m_weather_station == m_name && observation.m_time_of_observation.get_date() == m_date;
        }
        
    private:
        std::string m_name;
        date_t m_date;
    }; // struct weather_station_and_date_filter
            
} // namespace aqua