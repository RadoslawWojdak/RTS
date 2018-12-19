#ifndef STATISTICS_MANAGER
#define STATISTICS_MANAGER

#include "../common/statistics.hpp"

class Statistics_Manager
{
    Statistics statistics;

public:
    Statistics_Manager(unsigned int resources, unsigned int max_units_capacity);

    virtual unsigned int get_resources();
    virtual void add_resources(unsigned int amount);
    virtual void subtract_resources(unsigned int amount);

    virtual unsigned int get_max_units_capacity();
    virtual void increase_max_units_capacity(unsigned int amount);
    virtual void decrease_max_units_capacity(unsigned int amount);

    virtual unsigned int get_current_units_number();
    virtual void increase_current_units_number(unsigned int amount);
    virtual void decrease_current_units_number(unsigned int amount);
};

#endif // STATISTICS_MANAGER
