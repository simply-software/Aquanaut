#pragma once

#include <algorithm>
#include <string>
#include "convert_from_string.h"
#include "datetime.h"
#include "parse_csv_record.h"

namespace aqua {

    struct observation final {
        using temperature_t = double;
        
        observation() = default;
        observation(const observation&) = default;
        observation(observation&&) = default;
        
        observation& operator=(observation rhs) noexcept {
            this->swap(rhs);
            return *this;
        }
        
        observation& operator=(observation&& rhs) = default;
        
        void swap(observation& that) noexcept {
            using std::swap;
            
            swap(m_weather_station, that.m_weather_station);
            swap(m_time_of_observation, that.m_time_of_observation);
            swap(m_air_temperature, that.m_air_temperature);
        }
        
        void populate_from(parse_csv_record& csv) {
            convert_from_string(m_weather_station, csv(0));
            convert_from_string(m_time_of_observation, csv(1));
            convert_from_string(m_air_temperature, csv(2));
        }

    public:        
        std::string m_weather_station;
        datetime_t  m_time_of_observation;
        temperature_t m_air_temperature;
    }; // struct observation
    
    inline void swap(observation& first, observation& second) noexcept {
        first.swap(second);
    }    
    
} // namespace aqua
