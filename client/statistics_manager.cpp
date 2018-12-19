#include "statistics_manager.hpp"

Statistics_Manager::Statistics_Manager(unsigned int resources, unsigned int max_units_capacity)
{
    statistics.resources = resources;
    statistics.current_units_number = 0;
    statistics.max_units_capacity = max_units_capacity;
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

unsigned int Statistics_Manager::get_max_units_capacity()
{
    return statistics.max_units_capacity;
}

void Statistics_Manager::increase_max_units_capacity(unsigned int amount)
{
    statistics.max_units_capacity += amount;
}

void Statistics_Manager::decrease_max_units_capacity(unsigned int amount)
{
    if (statistics.max_units_capacity - amount > 0)
    {
        statistics.max_units_capacity -= amount;
    }
    else
    {
        statistics.max_units_capacity = 0;
    }
}

unsigned int Statistics_Manager::get_current_units_number()
{
    return statistics.current_units_number;
}

void Statistics_Manager::increase_current_units_number(unsigned int amount)
{
    statistics.current_units_number += amount;
}

void Statistics_Manager::decrease_current_units_number(unsigned int amount)
{
    if (statistics.current_units_number - amount > 0)
    {
        statistics.current_units_number -= amount;
    }
    else
    {
        statistics.current_units_number = 0;
    }
}
