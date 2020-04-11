#pragma once

#include <iostream>
#include <string>

namespace aqua {

    // This class acts as a Python data generator class that sources data from stdin.  Its main responsibility
    // is to provide, via its function call operator, a single complete record each time it is called.
    class stdin_data_source {
    public:
        stdin_data_source() {
            get_next_line();
        }
        
        explicit operator bool() const noexcept {
            return !m_at_end;
        }
    
        std::string operator()() noexcept {
            std::string return_value = m_next_line;
            get_next_line();
            return return_value;
        }
        
    private:
        void get_next_line() {
            std::getline(std::cin, m_next_line);
            m_at_end = std::cin.eof();            
        }
        
    private:
        bool m_at_end; 
        std::string m_next_line;
    }; // class stdin_data_source

} // nameespace aqua
