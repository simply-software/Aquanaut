#include <exception>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "air_temperature_ranges.h"
#include "file_data_source.h"
#include "filter_records.h"
#include "for_each.h"
#include "observation.h"
#include "parse_csv_record.h"
#include "partition.h"
#include "station_and_date_partition.h"
#include "stdin_data_source.h"
#include "weather_station_and_date_filter.h"

int main(int, char*[]) {
    // Depending on what is going to be done with the data, it may not even be necessary to store
    // the whole dataset in memory at once as it could be quite large.  It would be preferable not to
    // store it in memory.
    //
    // But since we *are* storing it, some thought needs to be made on the dataset size and choice of
    // container.  vector<> isn't exactly the best, if it needs to resize, but in case it does, I've
    // made Observation movable so the performance penalty is "minimized".  But deque<> is arguably
    // worse since it uses a fixed-length block size, and given sizeof(Observation), we will fit very
    // few observations into a single block and thus performance of deque<> will be only slightly
    // better than that of list<>.
    //
    std::vector<aqua::observation> observations;
    observations.reserve(1024 * 1024); // Memory is cheap I guess?

    //aqua::stdin_data_source input_source;
    aqua::file_data_source input_source("test_file.csv");
    aqua::parse_csv_record  record_parser;
    while(input_source) {
        if (record_parser.parse_record(input_source())) {
            observations.resize(observations.size() + 1);
            try {
                observations.back().populate_from(record_parser);
            } catch (const std::exception& exc) { // This record is invalid
                std::cerr << exc.what() << std::endl;
                observations.resize(observations.size() - 1);
            }
        }
    }

    std::set<aqua::station_and_date_partition> partitions = aqua::partition<aqua::station_and_date_partition>(observations);
    for (const aqua::station_and_date_partition& partition : partitions) {
        std::cout << partition.m_weather_station << " for " << to_string(partition.m_date) << std::endl;
        auto filter = aqua::make_record_filter(observations, aqua::weather_station_and_date_filter(partition.m_weather_station, partition.m_date));
        aqua::air_temperature_ranges temp_ranges;
        aqua::for_each(filter.begin(), filter.end(), temp_ranges);
        std::cout << "  start: " << temp_ranges.m_start_of_day_temp << ", end: " << temp_ranges.m_end_of_day_temp << ", high: "
            << temp_ranges.m_high_temp << ", low: " << temp_ranges.m_low_temp << std::endl;
    }

    return 0;
}

