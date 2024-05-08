#include "Utility.hpp"
#include "Types.hpp"
#include "AETK/AEGP/Util/TaskScheduler.hpp"

double TimeToSeconds(const A_Time &time)
{
    // Scale the value to move the decimal two places to the right
    double scaledValue = static_cast<double>(time.value) * 100.0 / static_cast<double>(time.scale);

    // Round the scaled value to the nearest integer
    double rounded = std::round(scaledValue);

    // Scale the rounded value back down
    return rounded / 100.0;
} // Will find active comp and convert using frame rate

A_Time SecondsToTime(double seconds)
{
    auto future = ae::ScheduleOrExecute([seconds]() {
        AEGP_CompH comp;
        double frameRate;
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetMostRecentlyUsedComp(&comp);
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFramerate(comp, &frameRate);
        A_u_long scale = static_cast<A_u_long>(frameRate);
        return A_Time{static_cast<A_long>(std::round(seconds * scale)), scale};
    });
    return future.get();
}

int TimeToFrames(const A_Time &time)
{
    auto future = ae::ScheduleOrExecute([time]() {
        AEGP_CompH comp;
        double frameRate;
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetMostRecentlyUsedComp(&comp);
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFramerate(comp, &frameRate);
        return static_cast<int>(std::round(TimeToSeconds(time) * frameRate));
    });
    return future.get();
}

A_Time FramesToTime(int frames)
{
    auto future = ae::ScheduleOrExecute([frames]() {
        AEGP_CompH comp;
        double frameRate;
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetMostRecentlyUsedComp(&comp);
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFramerate(comp, &frameRate);
        A_u_long scale = static_cast<A_u_long>(frameRate);
        return A_Time{frames, scale};
    });
    return future.get();
}