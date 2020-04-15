#pragma once

#include <algorithm>
#include "observation.h"

namespace aqua {

    struct air_temperature_ranges {
        using temperature_t = observation::temperature_t;
        
        void operator()(const observation& ob) noexcept {
            using std::min;
            using std::max;
            
            if (m_first_record) {
                m_low_temp = m_high_temp = m_start_of_day_temp = m_end_of_day_temp = ob.m_air_temperature;
                m_earliest_record_of_day = m_latest_record_of_day = ob.m_time_of_observation.get_time();
                m_first_record = false;
            } else {
                m_low_temp = min(m_low_temp, ob.m_air_temperature);
                m_high_temp = max(m_high_temp, ob.m_air_temperature);
                if (ob.m_time_of_observation.get_time() < m_earliest_record_of_day) {
                    m_earliest_record_of_day = ob.m_time_of_observation.get_time();
                    m_start_of_day_temp = ob.m_air_temperature;
                } else if (ob.m_time_of_observation.get_time() > m_latest_record_of_day) {
                    m_latest_record_of_day = ob.m_time_of_observation.get_time();
                    m_end_of_day_temp = ob.m_air_temperature;                    
                }
            }
        }        
           
        bool m_first_record = true;
        time_t m_earliest_record_of_day;
        time_t m_latest_record_of_day;
        temperature_t m_start_of_day_temp; 
        temperature_t m_end_of_day_temp;
        temperature_t m_low_temp;
        temperature_t m_high_temp;        
    }; // struct air_temperature_ranges
    
} // namespace aqua