#pragma once

#include <utility>

namespace aqua {

    // A very limited version of boost::optional, since I don't have boost installed.
    template <typename T>
    class optional final {
    public:
        optional() : m_has_value(false) {}
        
        optional(const T& value) : m_has_value(true) {
            new (m_data) T(value);
        }
        optional(T&& value) : m_has_value(true) {
            new (m_data) T(std::forward<T>(value));
        }

        ~optional() {
            if (m_has_value) {
                static_cast<T*>(m_data)->~T();            
            }
        }
        
        optional& operator=(const T& value) {
            if (m_has_value) {
                m_has_value = false;
                static_cast<T*>(m_data)->~T();
            }
            
            new (m_data) T(value);
            m_has_value = true;
            return *this;
        }
        
        optional& operator=(T&& value) {
            if (m_has_value) {
                m_has_value = false;
                static_cast<T*>(m_data)->~T();
            }
            
            new (m_data) T(std::forward<T>(value));
            m_has_value = true;
            return *this;            
        }
        
        explicit operator bool() const noexcept {
            return m_has_value;
        }
        
    private:
        char m_data[sizeof(T)];
        bool m_has_value;        
    }; // class optional
    
} // namespace aqua