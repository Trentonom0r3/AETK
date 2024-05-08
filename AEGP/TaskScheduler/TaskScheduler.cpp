#include "TaskScheduler.h"
#include "windows.h"
#include "PyFxCore.h"

AEGP_PluginID myID = 827044L;

void TaskSchedulerCommand::execute() {
	try {
		//new thread state
		py::gil_scoped_acquire acquire;
		py::module_ sys = py::module_::import("sys");
		py::object path = sys.attr("path");
		auto info = std::string(py::str(path));
		App::Alert(info);
	}
	catch (py::error_already_set const& e) {
		App::Alert(e.what());
	}
	catch (std::exception const& e) {
		App::Alert(e.what());
	}
	catch (...) {
		App::Alert("Unknown error");
	}

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
			for (auto layer : *compItem.layers()) {
				auto layerName = layer->getName();
				App::Alert(layerName);
			}
			});
		});
	t.detach(); // Detach the thread to allow it to run independently
}

void TaskSchedulerCommand::updateMenu() {
	try {
		if (CompItem::activeItem()) {
			enableCommand(true);
			setCommandName("Schedule " + CompItem::activeItem()->name() + " Task");
		}
		else {
			enableCommand(false);
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}



void TaskScheduler::onInit()
{
	//pyfx::InitializePython();
	addCommand(std::make_unique<TaskSchedulerCommand>());
	registerCommandHook();
	registerUpdateMenuHook();
	registerIdleHook();
	registerDeathHook();
}

void TaskScheduler::onDeath()
{
	//pyfx::FinalizePython();
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
