#pragma once

#include <stdexcept>
#include "date.h"
#include "time.h"

namespace aqua {
   
    class datetime_t final {
    public:
        // Default constructor initializes to the beginning of the epoch 
        explicit datetime_t(const date_t& date = date_t(), const time_t& time = time_t()) :
            m_date(date), m_time(time) {}
        
        datetime_t(const datetime_t&) = default;
        datetime_t(datetime_t&&) = default;
        datetime_t& operator=(const datetime_t&) = default;
        datetime_t& operator=(datetime_t&&) = default;
        ~datetime_t() = default;
            
    public: // Totally ordered
        friend bool operator!=(const datetime_t& lhs, const datetime_t& rhs) {
            return lhs.m_date != rhs.m_date || lhs.m_time != rhs.m_time;
        }
            
        friend bool operator==(const datetime_t& lhs, const datetime_t& rhs) {
            return !(lhs != rhs);
        }

        friend bool operator<(const datetime_t& lhs, const datetime_t& rhs) {
            return
                lhs.m_date < rhs.m_date ||
                (lhs.m_date == rhs.m_date && lhs.m_time < rhs.m_time);
        }

        friend bool operator>(const datetime_t& lhs, const datetime_t& rhs) {
            return rhs < lhs;
        }

        friend bool operator<=(const datetime_t& lhs, const datetime_t& rhs) {
            return !(lhs > rhs);
        }

        friend bool operator>=(const datetime_t& lhs, const datetime_t& rhs) {
            return !(lhs < rhs);
        }

    public: // Access
        date_t get_date() const noexcept {
            return m_date;
        }
        
        time_t get_time() const noexcept {
            return m_time;
        }
        
    private:
        date_t m_date;
        time_t m_time;
    }; // class datetime_t

    // The format parsed by this function is: "01/01/2016 11:00:00 PM" (month/day/year)
    inline void convert_from_string(datetime_t& to, const std::string& from) {
        if (from.length() < sizeof("01/01/2016 ") - 1) {
            throw std::invalid_argument("'" + from + "' is too short");
        }
        
        std::string::size_type space = from.find(' ');
        if (space == std::string::npos) {
            throw std::invalid_argument("'" + from + "' is missing a space between the date and time");
        }
        
        date_t to_date;
        time_t to_time;
        
        convert_from_string(to_date, from.substr(0, space));
        convert_from_string(to_time, from.substr(space + 1));
        
        to = datetime_t(to_date, to_time);
    }
            
} // namespace aqua