#pragma once

#include <string>
#include "observation.h"

namespace aqua {

    struct weather_station_filter {
        explicit weather_station_filter(const std::string& name) : m_name(name) {}
        
        bool operator()(const observation& observation) const noexcept {
            return observation.m_weather_station == m_name;
        }
        
    private:
        std::string m_name;
    }; // struct weather_station_filter
            
} // namespace aqua