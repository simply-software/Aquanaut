#pragma once

#include <iterator>
#include <type_traits>
#include <vector>

namespace aqua {

    template <typename InputType, typename Filter>
    struct filter_records {
    private:
        using input_type = typename std::remove_reference<InputType>::type;
        using container_type = std::vector<typename input_type::const_iterator>;
    private:
        
        container_type m_matching_elements;

    public: // STL container requirements to interoperate with algorithms:
        using value_type = typename input_type::value_type;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        
        class const_iterator final : public std::iterator<std::forward_iterator_tag, const value_type> {
        public:
            const_iterator() noexcept {}
            const_iterator(const const_iterator&) = default;

            const_iterator& operator++() noexcept { // prefix
                ++m_current;
                return *this;
            }

            const_iterator operator++(int) noexcept { // postfix
                const_iterator tmp(*this);
                ++m_current;
                return tmp;
            }

            const_iterator& operator=(const const_iterator& rhs) noexcept {
                m_current = rhs.m_current;
                m_end = rhs.m_end;
                return *this;
            }

            const_reference operator*() const noexcept {
                return **m_current;
            }

            const_pointer operator->() const noexcept {
                return &**m_current;
            }

            bool operator==(const const_iterator& rhs) const noexcept {
                return m_current == rhs.m_current;
            }

            bool operator!=(const const_iterator& rhs) const noexcept {
                return m_current != rhs.m_current;
            }

        protected:
            friend class filter_records;

            const_iterator(typename container_type::const_iterator current, typename container_type::const_iterator end) :
                m_current(current), m_end(end) {}

        private:
            typename container_type::const_iterator m_current;
            typename container_type::const_iterator m_end;
        };
        
    public:
        filter_records(const InputType& input, const Filter& filter) {
            for (typename input_type::const_iterator it = input.begin(); it != input.end(); ++it) {
                if (filter(*it)) {
                    m_matching_elements.push_back(it);
                }
            }
        }
            
        const_iterator begin() const noexcept {
            return const_iterator(m_matching_elements.begin(), m_matching_elements.end());
        }
        
        const_iterator cbegin() const noexcept {
            return const_iterator(m_matching_elements.begin(), m_matching_elements.end());            
        }
        
        const_iterator end() const noexcept {
            return const_iterator(m_matching_elements.end(), m_matching_elements.end());            
        }

        const_iterator cend() const noexcept {
            return const_iterator(m_matching_elements.end(), m_matching_elements.end());                        
        }
    }; // struct filter_records
        
    template <typename InputType, typename Filter>
    filter_records<InputType, Filter> make_record_filter(InputType&& dataset, Filter&& filter) {
        return filter_records<InputType, Filter>(std::forward<InputType>(dataset), std::forward<Filter>(filter));
    }
    
} // namespace aqua