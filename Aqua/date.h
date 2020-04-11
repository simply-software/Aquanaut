#pragma once

#include <cstdio>
#include <stdexcept>
#include <string>

namespace aqua {

    typedef uint8_t day_t;
    typedef uint8_t month_t;
    typedef uint16_t year_t;
    
    class date_t final {
    public:
        // Default constructor initializes to beginning of epoch (1 Jan 1970)
        date_t() : m_month(1), m_day(1), m_year(1970u) {}
        
        date_t(month_t month, day_t day, year_t year) :
            m_month(month), m_day(day), m_year(year) {}
        
        date_t(const date_t&) = default;
        date_t(date_t&&) = default;
        date_t& operator=(const date_t&) = default;
        date_t& operator=(date_t&&) = default;
        ~date_t() = default;
            
    public: // Totally ordered
        friend bool operator!=(const date_t& lhs, const date_t& rhs) noexcept {
            return lhs.m_year != rhs.m_year || lhs.m_month != rhs.m_month || lhs.m_day != rhs.m_day;
        }
        
        friend bool operator==(const date_t& lhs, const date_t& rhs) noexcept {
            return !(lhs != rhs);
        }
        
        friend bool operator<(const date_t& lhs, const date_t& rhs) noexcept {
            return
                lhs.m_year < rhs.m_year ||
                (lhs.m_year == rhs.m_year && lhs.m_month < rhs.m_month) ||
                (lhs.m_year == rhs.m_year && lhs.m_month == rhs.m_month && lhs.m_day < rhs.m_day);
        }

        friend bool operator>(const date_t& lhs, const date_t& rhs) noexcept {
            return rhs < lhs;
        }
        
        friend bool operator<=(const date_t& lhs, const date_t& rhs) noexcept {
            return !(lhs > rhs);
        }

        friend bool operator>=(const date_t& lhs, const date_t& rhs) noexcept {
            return !(lhs < rhs);
        }

    public: // Access
        month_t month() const noexcept {
            return m_month;
        }
        
        std::string month_as_abbreviation() const noexcept {
            static const char* Months[] = {
                "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
            };
            
            return Months[m_month - 1];
        }
        
        std::string month_as_string() const noexcept {
            static const char* Months[] = {
                "January", "February", "March", "April", "May", "June",
                "July", "August", "September", "October", "November", "December"
            };
            
            return Months[m_month - 1];        
        }
        
        day_t day() const noexcept {
            return m_day;
        }

        year_t year() const noexcept {
            return m_year;           
        }
        
    private: 
        month_t m_month; // 1-based
        day_t m_day; // 1=based
        year_t m_year; // The actual year, eg, 2020
    }; // class date_t
    
    // The format parsed by this function is: "01/01/2016" (month/day/year)
    inline void convert_from_string(date_t& to, const std::string& from) {
        uint16_t month, day, year;
        
        if (sscanf(from.c_str(), "%hu/%hu/%hu", &month, &day, &year) != 3) {
            throw std::invalid_argument("'" + from + "' is not correctly formatted as mm/dd/yyyy");
        }
        
        to = date_t(month_t(month), day_t(day), year_t(year));
    }
    
    enum class DateFormat {
        MM_SLASH_DD_SLASH_YYYY
    };
    
    std::string to_string(const date_t& date, DateFormat format = DateFormat::MM_SLASH_DD_SLASH_YYYY) {
        char buf[50];
        
        switch (format) {
            default:
            case DateFormat::MM_SLASH_DD_SLASH_YYYY:
                sprintf(buf, "%02d/%02d/%04d", (int)date.month(), (int)date.day(), (int)date.year());
                break;
        }
        
        return buf;
    }
    
} // namespace aqua