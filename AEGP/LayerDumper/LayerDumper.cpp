#include "LayerDumper.h"

AEGP_PluginID myID = 333237L;

void LayerDumperCommand::execute() {
	openWindow(); // Open a window to select a file
	clearLogFile(); // Clear the log file
	try {
		auto layer = Layer::activeLayer(); // Get the active layer
		process(layer); // Process the active layer
	}
	catch (...) {
		// Handle unexpected exceptions
		logOss << "Unexpected exception occurred\n";
		std::ofstream logFile(filePath, std::ios_base::app);
		logFile << logOss.str();
		logFile.close();
	}
}

void LayerDumperCommand::updateMenu() {
	if (!LayerSuite().GetActiveLayer()) {
		// Disable the menu item if there is no active layer
		enableCommand(false);
	}
	else {
		// Enable the menu item if there is an active layer
		enableCommand(true);
		std::string name = Layer::activeLayer()->getName();
		setCommandName("Dump Info for " + name);
	}
}

void LayerDumper::onInit()
{
	addCommand(std::make_unique<LayerDumperCommand>()); // Add the InfoDumperCommand to the plugin
	registerCommandHook();
	registerUpdateMenuHook();
}

void LayerDumper::onDeath()
{

}

void LayerDumper::onIdle()
{
}

DECLARE_ENTRY(LayerDumper, myID)
