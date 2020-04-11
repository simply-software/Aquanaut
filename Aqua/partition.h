#pragma once

#include <set>

namespace aqua {

    template <typename UniqueKey, typename InputType> 
    std::set<UniqueKey> partition(const InputType& container) {
        std::set<UniqueKey> partitions;
        
        for (const auto& element : container) {
            partitions.insert(UniqueKey(element));
        }

        return partitions;
    }
    
} // namespace aqua