#ifndef STATISTICS_MANAGER
#define STATISTICS_MANAGER

#include "../common/statistics.hpp"

class Statistics_Manager
{
    Statistics statistics;

public:
    Statistics_Manager(unsigned int resources);

    virtual unsigned int get_resources();
    virtual void add_resources(unsigned int amount);
    virtual void subtract_resources(unsigned int amount);
};

#endif // STATISTICS_MANAGER
