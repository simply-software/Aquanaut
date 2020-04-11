#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

namespace aqua {

    typedef uint8_t hour_t;
    typedef uint8_t minute_t;
    typedef uint8_t second_t;
    
    class time_t final {
    public:
        // Default constructor initializes to midnight (00:00:00)
        explicit time_t(hour_t hour = hour_t(), minute_t minute = minute_t(), second_t second = second_t()) :
            m_hour(hour), m_minute(minute), m_second(second) {}
        
        time_t(const time_t&) = default;
        time_t(time_t&&) = default;
        time_t& operator=(const time_t&) = default;
        time_t& operator=(time_t&&) = default;
        ~time_t() = default;
            
    public: // Totally ordered
        friend bool operator!=(const time_t& lhs, const time_t& rhs) noexcept {
            return lhs.m_hour != rhs.m_hour || lhs.m_minute != rhs.m_minute || lhs.m_second != rhs.m_second;
        }
        
        friend bool operator==(const time_t& lhs, const time_t& rhs) noexcept {
            return !(lhs != rhs);
        }
        
        friend bool operator<(const time_t& lhs, const time_t& rhs) noexcept {
            return
                lhs.m_hour < rhs.m_hour ||
                (lhs.m_hour == rhs.m_hour && lhs.m_minute < rhs.m_minute) ||
                (lhs.m_hour == rhs.m_hour && lhs.m_minute == rhs.m_minute && lhs.m_second < rhs.m_second);
        }

        friend bool operator>(const time_t& lhs, const time_t& rhs) noexcept {
            return rhs < lhs;
        }
        
        friend bool operator<=(const time_t& lhs, const time_t& rhs) noexcept {
            return !(lhs > rhs);
        }

        friend bool operator>=(const time_t& lhs, const time_t& rhs) noexcept {
            return !(lhs < rhs);
        }
       
    private: // Stored in military time for easy comparison
        hour_t m_hour; // 0-23
        minute_t m_minute; // 0-59
        second_t m_second; // 0-60; 60 is used for leap second
    }; // class time_t

    // The format parsed by this function is: "11:00:00 PM"
    inline void convert_from_string(time_t& to, const std::string& from) {
        uint16_t hour, minute, second;
        char am_or_pm;
        
        if (sscanf(from.c_str(), "%hu:%hu:%hu %c", &hour, &minute, &second, &am_or_pm) != 4) {
            throw std::invalid_argument("'" + from + "' is not correctly formatted as hh:mm::ss PM");
        }

        if (am_or_pm == 'A') {
            hour %= 12; // 12 => 0, rest unchanged
        } else if (am_or_pm == 'P') {
            hour = 12 + (hour % 12); // 12 => 12, everything else is 13...23
        } else {
            throw std::invalid_argument("'" + from + "' does not end in 'AM' or 'PM'");
        }
        
        to = time_t(hour_t(hour), minute_t(minute), second_t(second));
    }

} // namespace aqua