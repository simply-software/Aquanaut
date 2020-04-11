#pragma once

#include <algorithm>
#include <iosfwd>
#include <string>
#include <type_traits>
#include "type_traits.h"

namespace aqua {

    template <typename PodType, typename Tag, typename IsPod_ = std::is_arithmetic<PodType>>
    struct typesafe_pod; // <PodType, Tag, std::false_type> - specified type is not POD

    template <typename PodType, typename Tag>
    struct typesafe_pod<PodType, Tag, std::true_type> final {
    public:
        using value_type = PodType;

    private: // Prevent conversion from one type-safe value to another
        template<typename OtherTag, typename U, typename IsPod>
        typesafe_pod(typesafe_pod<OtherTag, U, IsPod>); /* Unimplemented and private */
            
    public: // Construction
        constexpr typesafe_pod() noexcept : m_value() {} // Zeroing constructor

        typesafe_pod(const typesafe_pod& rhs) = default;

        template<typename U> constexpr explicit
        typesafe_pod(U value, typename std::enable_if<std::is_same<PodType, U>::value, void*>::type = 0) noexcept : 
            m_value(value) {}
        
    public: // Assignment
        typesafe_pod& operator=(const typesafe_pod& rhs) = default;

        template<typename U> constexpr
        typename std::enable_if<std::is_same<PodType, U>::value, typesafe_integer&>::type
        operator=(U value) noexcept {
            m_value = value;
            return *this;
        }

    public: // Totally ordered
        friend constexpr bool operator==(typesafe_pod lhs, typesafe_pod rhs) noexcept {
            return lhs.m_value == rhs.m_value;
        }

        friend constexpr bool operator!=(typesafe_pod lhs, typesafe_pod rhs) noexcept {
            return !(lhs == rhs);
        }

        friend constexpr bool operator<(typesafe_pod lhs, typesafe_pod rhs) noexcept {
            return lhs.m_value < rhs.m_value;
        }

        friend constexpr bool operator>(typesafe_pod lhs, typesafe_pod rhs) noexcept {
            return rhs < lhs;
        }

        friend constexpr bool operator<=(typesafe_pod lhs, typesafe_pod rhs) noexcept {
            return !(lhs > rhs);
        }

        friend constexpr bool operator>=(typesafe_pod lhs, typesafe_pod rhs) noexcept {
            return !(lhs < rhs);
        }

    public: // Comparison against 0
        constexpr explicit operator bool() const noexcept {
            return m_value;
        }

        constexpr bool operator!() const noexcept {
            return !m_value;
        }

    public: // Conversion to intrinsic types
        constexpr value_type value() const noexcept {
            return m_value;
        }

    private:
        value_type m_value;            
    };
    
    // Conversion to string
    template<typename Tag, typename T, bool b = std::is_signed<T>::value>
    std::string to_string(typesafe_pod<Tag, T> value) {
        return b ?
            std::to_string(static_cast<int64_t>(value.value())) :
            std::to_string(static_cast<uint64_t>(value.value()));
    }

    // Streaming operators always output as integers, even in the 8-bit case
    template<typename Tag, typename T>
    std::ostream& operator<<(std::ostream& os, typesafe_pod<Tag, T> pod) {
        return os << pod.value();
    }

    template<typename Tag>
    std::ostream& operator<<(std::ostream& os, typesafe_pod<Tag, int8_t> int8) {
        return os << static_cast<int16_t>(int8.value());
    }

    template<typename Tag>
    std::ostream& operator<<(std::ostream& os, typesafe_pod<Tag, uint8_t> uint8) {
        return os << static_cast<uint16_t>(uint8.value());
    }

    template<typename Tag, typename T>
    std::istream& operator>>(std::istream& is, typesafe_pod<Tag, T>& pod) {
        T value;
        is >> value;
        pod = typesafe_pod<Tag, T>(value);
        return is;
    }

    template<typename Tag>
    std::istream& operator>>(std::istream& is, typesafe_pod<Tag, int8_t>& int8) {
        int16_t value;
        is >> value;
        int8 = typesafe_pod<Tag, int8_t>(static_cast<int8_t>(value));
        return is;
    }

    template<typename Tag>
    std::istream& operator>>(std::istream& is, typesafe_pod<Tag, uint8_t>& uint8) {
        uint16_t value;
        is >> value;
        uint8 = typesafe_pod<Tag, uint8_t>(static_cast<uint8_t>(value));
        return is;
    }

} // namespace aqua
    