#include "TaskScheduler.h"
#include "windows.h"

AEGP_PluginID myID = 827044L;

void TaskSchedulerCommand::execute() {
	std::thread t([]() {
		// Schedule a task to obtain a CompItem asynchronously
		auto compFuture = ae::TaskScheduler::GetInstance().ScheduleTask<CompItem>([]() {
			return CompItem::mostRecent();
			});

		compFuture.wait();
		// Wait for the task to complete and get the result
		CompItem compItem = compFuture.get();

		// Schedule another task to use compItem
		ae::TaskScheduler::GetInstance().ScheduleTask([compItem]() mutable {
			auto name = compItem.name();
			App::Alert(name);
			});
		});
	t.detach(); // Detach the thread to allow it to run independently
}

void TaskSchedulerCommand::updateMenu() {
	if (CompItem::activeItem()) {
		enableCommand(true);
		setCommandName("Schedule " + CompItem::activeItem()->name() + " Task");
	}
	else {
		enableCommand(false);
	}
}

void TaskScheduler::onInit()
{
	addCommand(std::make_unique<TaskSchedulerCommand>());
	registerCommandHook();
	registerUpdateMenuHook();
	registerIdleHook();

}

void TaskScheduler::onDeath()
{

}

void TaskScheduler::onIdle()
{
	try {
		ae::TaskScheduler::GetInstance().ExecuteTask();
	}
	catch (const std::exception& e) {
		App::Alert(e.what());
	}
}

DECLARE_ENTRY(TaskScheduler, myID)
