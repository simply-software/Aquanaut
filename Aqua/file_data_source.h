#pragma once

#include <fstream>

namespace aqua {

    // This class acts as a Python data generator class that sources data from a file.  Its main responsibility
    // is to provide, via its function call operator, a single complete record each time it is called.
    class file_data_source {
    public:
        file_data_source(const std::string& filename) : m_file(filename.c_str()) {
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
            std::getline(m_file, m_next_line);
            m_at_end = m_file.eof();            
        }
        
    private:
        std::ifstream m_file;
        bool m_at_end = false;
        std::string m_next_line;
    }; // class file_data_source
    
} // namespace aqua