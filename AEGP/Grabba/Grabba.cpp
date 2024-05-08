#include "Grabba.h"
#include "windows.h"
#include "Python.h"
#include <Pybind11/pybind11.h>
#include <Pybind11/embed.h>
#include "AETK/AEGP/Core/PyFx.hpp"

namespace py = pybind11;

AEGP_PluginID myID = 3927L;

void saveFrame(int i, LayerRenderOptionsPtr layerRenderOptions) {
	LayerRenderOptionsSuite().setTime(layerRenderOptions, FramesToTime(i)); // Set the time of the layer render options
	AsyncRenderManager rmanager; // Create an instance of the AsyncRenderManager class
	rmanager.renderAsync(layerRenderOptions, [i](WorldPtr world) { // Call the renderAsync method with a lambda function
		if (world) {
			std::string folder = "C:\\Users\\tjerf\\Downloads\\pdf_output\\New folder\\";
			auto data = Image::data(world); // Get the image data from the world
			Image::saveImage(folder + "\\frame" + std::to_string(i) + ".png", "png", data); // Save the image to disk
		}
		});
}

void GrabbaCommand::execute() {

    try {
        std::thread t([]() {
            try {
                py::gil_scoped_acquire acquire;

				//run this; C:\Users\tjerf\source\repos\AETK\AETK\test.py
				py::eval_file("C:\\Users\\tjerf\\source\\repos\\AETK\\AETK\\test.py");

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
            });
        t.detach();
    }
	catch (py::error_already_set const& e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception const& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}


void GrabbaCommand::updateMenu() {
	SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_EnableCommand(getCommand());
}

void Grabba::onInit()
{
	addCommand(std::make_unique<GrabbaCommand>());
	registerCommandHook();
	registerUpdateMenuHook();
	registerIdleHook();
}

void Grabba::onDeath()
{

}

void Grabba::onIdle()
{
	ae::TaskScheduler::GetInstance().ExecuteTask();
}

DECLARE_ENTRY(Grabba, myID)
