//
// Created by nikita on 11/30/19.
//

#include <algorithm>
#include "ScheduleProcessor.h"

std::vector<Schedule> ScheduleProcessor::process(std::vector<Schedule> schedules) {
    std::sort(schedules.begin(), schedules.end(), [](const Schedule &a, const Schedule &b) {
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        if (a.departureTime != b.departureTime)
            return a.departureTime > b.departureTime;
        return a.company->priority > b.company->priority;
    });

    for (unsigned i = 0; i < schedules.size(); i++) {
        if(schedules[i].arrivalTime - schedules[i].departureTime < Time(60*60)){
            schedules.erase(std::next(schedules.begin(), i));
            i--;
            continue;
        }

        while (i + 1 < schedules.size() && schedules[i + 1].departureTime <= schedules[i].departureTime)
            schedules.erase(std::next(schedules.begin(), i + 1));
    }

    return std::move(schedules);
}