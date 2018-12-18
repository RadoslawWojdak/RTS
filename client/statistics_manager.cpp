#include "statistics_manager.hpp"

Statistics_Manager::Statistics_Manager(unsigned int resources)
{
    statistics.resources = resources;
}

unsigned int Statistics_Manager::get_resources()
{
    return statistics.resources;
}

void Statistics_Manager::add_resources(unsigned int amount)
{
    statistics.resources += amount;
}

void Statistics_Manager::subtract_resources(unsigned int amount)
{
    if (statistics.resources > amount)
    {
        statistics.resources -= amount;
    }
}
