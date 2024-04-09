#include "Grabba.h"
#include "windows.h"

AEGP_PluginID myID = 3927L;

void GrabbaCommand::execute() {
	try {
		auto item = ItemSuite().GetActiveItem();
		RenderOptionsPtr& renderOptions = RenderOptionsSuite().newFromItem(item);
		RenderOptionsSuite().setTime(renderOptions, ItemSuite().GetItemCurrentTime(item));
		auto frameReceipt = RenderSuite().renderAndCheckoutFrame(renderOptions);
		auto world = RenderSuite().getReceiptWorld(frameReceipt);
		void* mainhwnd = UtilitySuite().getMainHWND();
		OPENFILENAME ofn;
		char szFile[100];
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = HWND(mainhwnd);
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetSaveFileName(&ofn);

		//image->saveImage(ofn.lpstrFile, "png");
		if (ofn.lpstrFile[0] != '\0') {
			auto data = Image::data(world);
			Image::saveImage(ofn.lpstrFile, "png", data);
		}
	}
	catch (const std::exception& e) {
		App::Alert(e.what());
	}
	catch (...) {
		App::Alert("An unknown error occurred.");
		}
}

void GrabbaCommand::updateMenu() {
	auto activeItem = ItemSuite().GetActiveItem();
	if (!activeItem.get()) {
		enableCommand(false);
		return;
	}
	ItemType itemType = ItemSuite().GetItemType(activeItem);
	bool enable = activeItem.get() && (itemType == ItemType::FOOTAGE || itemType == ItemType::COMP);
	enableCommand(enable);
}

void Grabba::onInit() 
{
	addCommand(std::make_unique<GrabbaCommand>());
	registerCommandHook();
	registerUpdateMenuHook();
}

void Grabba::onDeath()
{

}

void Grabba::onIdle()
{
}

DECLARE_ENTRY(Grabba, myID)
