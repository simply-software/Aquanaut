Filters
-------

The idea of a filter is to take a dataset as input and output a subset of that dataset that meet user-specified
criteria.  Using a filter on a dataset will filter out records that do not match the criteria and will return 
only records that do match, preserving their order from the original dataset.

The template class filter_records<> is the class that does the filtering; the other files in this directory
are specific filters.  filter_records<> is intended to be used as a container and thus provides iterator access
to its elements.  Only forward iteration is supported at this time, and only const_iterators are provided.

When filter_records<> is instantiated, it is given an input container and a filter.  The input container is
iterated at construction time and an intermediate container of iterators to the original container is built.  
Iterator stability of the original container is required during the lifetime of a filter applied to it.
