#pragma once

namespace aqua {

    // This algorithm differs from the std::for_each algorithm in that it allows the predicate
    // to be stateful.
    //
    template<typename InputIter, typename Predicate>
    void for_each(InputIter first, InputIter last, Predicate& predicate) {
        while (first != last) {
            predicate(*first++);
        }
    }
    
} // namespace aqua