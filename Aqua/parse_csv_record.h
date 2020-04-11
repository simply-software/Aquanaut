#pragma once

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace aqua {

    // This class parses a CSV record into an N-tuple of values which are
    // stored as strings.  This class knows nothing about the data it is
    // parsing.
    class parse_csv_record {
    public: // Construction, destruction and assignment
        parse_csv_record() = default;
        parse_csv_record(const parse_csv_record&) = default;
        parse_csv_record(parse_csv_record&&) = default;
        ~parse_csv_record() = default;

        explicit parse_csv_record(const std::string& header_row) {
            m_column_headers = parse_record_(header_row);
        }
        
    public: // Assignment
        parse_csv_record& operator=(const parse_csv_record&) = default;
        parse_csv_record& operator=(parse_csv_record&&) = default;
        
    public: // Parsing API
        // Returns true upon successful parse, false otherwise.  A record parses successfully
        // if all of the following are true:
        //   1) the record contains at least one column;
        //   2) the record contains the same number of columns as the header row OR the header row is empty
        //      (in this latter case we don't know how many columns to expect)
        //
        bool parse_record(const std::string& record) {
            m_current_record = parse_record_(record);
            return 
                !m_current_record.empty() &&
                ((m_current_record.size() == m_column_headers.size()) || m_column_headers.empty());
        }
  
    public:
        const std::vector<std::string>& get_column_names() const noexcept {
            return m_column_headers;           
        }
        
    public: // Value access API - by column position
        std::string operator()(size_t position) const {
            return m_current_record.at(position); // will throw if position is invalid
        }
        
    public: // Value access API - by column name 
        std::string operator()(const std::string& column) const {
            auto iter = std::find(m_column_headers.begin(), m_column_headers.end(), column);
            if (iter == m_column_headers.end()) {
                throw std::invalid_argument("Column '" + column + "' does not exist in the dataset");
            }
            
            return this->operator()(std::distance(m_column_headers.begin(), iter));
        }
        
    private:
        // boost::tokenizer would work great here, but I don't have boost installed, so
        // I'm hand-writing this.  I'm also using strtok() which is not thread-safe.  Goal
        // here is minimal code with reasonable speed.
        std::vector<std::string> parse_record_(const std::string& record) {
            // strtok will modify the input buffer.  Not recommended to edit std::strings without
            // using the std::string API.
            char buf[record.size() + 1];  // GCC extension
            strcpy(buf, record.c_str());
            
            std::vector<std::string> result; // Hoping for NRVO here to avoid a copy construction
            char* next_token = strtok(buf, ",");
            while (next_token != nullptr) {
                // Strip leading whitespace
                while (*next_token == ' ') {
                    ++next_token;
                }
                
                // Strip trailing whitespace
                size_t length = strlen(next_token);
                while (length && next_token[length - 1] == ' ') {
                    --length;
                }
                next_token[length] = '\0';
                                
                result.push_back(next_token);
                next_token = strtok(nullptr, ",");
            }
            
            return result;
        }
    
    private:
        std::vector<std::string> m_column_headers;
        std::vector<std::string> m_current_record;
    }; // class parse_csv_record
    
} // namespace aqua