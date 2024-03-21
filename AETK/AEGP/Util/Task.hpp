/*****************************************************************/ /**
                                                                     * \file
                                                                     *Task.hpp
                                                                     * \brief  A
                                                                     *class for
                                                                     *creating
                                                                     *and
                                                                     *managing
                                                                     *threads
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/
#ifndef TASK_HPP
#define TASK_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

/**
 * @class TaskScheduler
 * @brief Manages the scheduling and execution of tasks.
 */
class TaskScheduler
{
  public:
    /**
     * @brief Gets the singleton instance of the TaskScheduler.
     * @return TaskScheduler& The singleton instance.
     */
    static TaskScheduler &GetInstance()
    {
        static TaskScheduler instance;
        return instance;
    }

    /**
     * @brief Schedules a task with no return value.
     * @param task The task to be scheduled.
     * @param callIdle Flag indicating whether to call idle routines for quicker
     * response.
     */
    inline void ScheduleTask(std::function<void()> task, bool callIdle = TRUE)
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasksQueue.push(std::move(task));
        if (callIdle)
        {
            UtilitySuite6().causeIdleRoutinesToBeCalled();
        }
    }

    /**
     * @brief Schedules a task with a return value.
     * @tparam ReturnType The return type of the task.
     * @param task The task to be scheduled.
     * @param callIdle Flag indicating whether to call idle routines for quicker
     * response.
     * @return std::future<ReturnType> A future object representing the result
     * of the task.
     */
    template <typename ReturnType>
    inline std::future<ReturnType>
    ScheduleTask(std::function<ReturnType()> task, bool callIdle = TRUE)
    {
        auto promise = std::make_shared<std::promise<ReturnType>>();
        auto future = promise->get_future();

        // Wrap the user's task to handle the promise/future mechanism
        std::function<void()> taskWrapper = [promise, task]() {
            try
            {
                promise->set_value(task());
            }
            catch (...)
            {
                try
                {
                    // Attempt to re-throw the caught exception
                    throw;
                }
                catch (...)
                {
                    // Store any exception in the promise
                    promise->set_exception(std::current_exception());
                }
            }
        };

        ScheduleTask(taskWrapper, callIdle); // Schedule the wrapped task
        return future;
    }

    /**
     * @brief Executes the next scheduled task.
     */
    inline void ExecuteTask()
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!tasksQueue.empty())
        {
            auto task = tasksQueue.front();
            tasksQueue.pop();
            task(); // Execute the task
        }
    }

  private:
    std::mutex queueMutex;
    std::queue<std::function<void()>> tasksQueue;
};

/**
 * @brief Schedules a task with a return value.
 * @tparam ReturnType The return type of the task.
 * @param task The task to be scheduled.
 * @param callIdle Flag indicating whether to call idle routines for quicker
 * response.
 * @return std::future<ReturnType> A future object representing the result of
 * the task.
 */
template <typename ReturnType>
inline std::future<ReturnType> ScheduleTask(std::function<ReturnType()> task,
                                            bool callIdle = TRUE)
{
    return TaskScheduler::GetInstance().ScheduleTask(task, callIdle);
}

/**
 * @brief Schedules a task with no return value.
 * @param task The task to be scheduled.
 * @param callIdle Flag indicating whether to call idle routines for quicker
 * response.
 */
inline void ScheduleTask(std::function<void()> task, bool callIdle = FALSE)
{
    TaskScheduler::GetInstance().ScheduleTask(task, callIdle);
}

#endif // TASK_HPP