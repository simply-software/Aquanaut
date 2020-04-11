#pragma once

#include "date.h"
#include "observation.h"

namespace aqua {

    struct date_filter {
        explicit date_filter(date_t date) : m_date(date) {}
        
        bool operator()(const observation& observation) const noexcept {
            return observation.m_time_of_observation.get_date() == m_date;
        }
        
    private:
        date_t m_date;
    }; // struct date_filter
    
} // namespace aqua