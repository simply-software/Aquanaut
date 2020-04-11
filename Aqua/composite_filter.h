#pragma once

#include <utility>

// Filters are used to run through a dataset and filter out records that do not meet certain, user-defined
// criteria.
//

namespace aqua {

    namespace detail {

        template <typename... Filters>
        struct composite_and_filter_helper {
            composite_and_filter_helper() = default;
            
            template<typename T>
            bool operator()(const T&) const noexcept {
                return true;
            }        
        }; // composite_and_filter_helper<>

        template <typename Filter, typename... RemainingFilters>
        struct composite_and_filter_helper : composite_and_filter_helper<RemainingFilters...> {
            using Base = composite_and_filter_helper<RemainingFilters...>;
            
            composite_and_filter_helper(const Filter& filter, RemainingFilters&&... remaining) :
                Base(remaining...), m_filter(filter) {}
                
            template<typename T>
            bool operator()(const T& t) const noexcept {
                return m_filter(t) && Base::operator()(t);
            }
            
        private:
            const Filter& m_filter;
        }; // composite_and_filter_helper<Filter, ...>
        

        template <typename... Filters>
        struct composite_or_filter_helper {
            composite_or_filter_helper() = default;
            
            template<typename T>
            bool operator()(const T&) const noexcept {
                return true;
            }        
        }; // composite_or_filter_helper<>

        template <typename Filter, typename... RemainingFilters>
        struct composite_or_filter_helper : composite_or_filter_helper<RemainingFilters...> {
            using Base = composite_or_filter_helper<RemainingFilters...>;
            
            composite_or_filter_helper(const Filter& filter, RemainingFilters&&... remaining) :
                Base(remaining...), m_filter(filter) {}
                
            template <typename T>
            bool operator()(const T& t) const noexcept {
                return m_filter(t) || Base::operator()(t);
            }
            
        private:
            const Filter& m_filter;
        }; // composite_or_filter_helper<Filter, ...>
        
    } // namespace detail
    
    template <typename... Filters>
    struct composite_and_filter : detail::composite_and_filter_helper<Filters...> {
        using Base = detail::composite_and_filter_helper<Filters...>;
        
        composite_and_filter(Filters&&... filters) : Base(std::forward<Filters>(filters)...) {}
        
        template <typename T>
        bool operator()(const T& t) const noexcept {
            return Base::operator()(t);
        }
    }; // struct composite_and_filter

    template<typename... Filters>
    struct composite_or_filter : detail::composite_or_filter_helper<Filters...> {
        using Base = detail::composite_or_filter_helper<Filters...>;
        
        composite_or_filter(Filters&&... filters) : Base(std::forward<Filters>(filters)...) {}
        
        template <typename T>
        bool operator()(const T& t) const noexcept {
            return Base::operator()(t);
        }
    }; // struct composite_or_filter
    

    // API
    template<typename... Filters>
    composite_and_filter<Filters...> and_filter(Filters&... filters) {
        return composite_and_filter<Filters...>(std::forward<Filters>(filters)...);
    }

    template<typename... Filters>
    composite_or_filter<Filters...> or_filter(Filters&... filters) {
        return composite_or_filter<Filters...>(std::forward<Filters>(filters)...);
    }
    
} // namespace aqua