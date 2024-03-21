#include "AETK/AEGP/AEGP.hpp"

static A_long				S_idle_count = 0L;

class GrabbaCommand : public Command {
	public:
	GrabbaCommand() : Command("Grabba", AE_MenuID::EXPORT) {}
	inline void execute() override {
		auto item = ItemSuite9().GetActiveItem();
		auto renderOptions = RenderOptionsSuite4().newFromItem(item);
		RenderOptionsSuite4().setTime(renderOptions, ItemSuite9().GetItemCurrentTime(item));
		auto frameReceipt = RenderSuite5().renderAndCheckoutFrame(renderOptions);
		auto world = RenderSuite5().getReceiptWorld(frameReceipt);
		Image* image = new Image(world);
		void* mainhwnd = UtilitySuite6().getMainHWND();
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

		image->saveImage(ofn.lpstrFile, "png");
		delete image;
	}

	inline void updateMenu() override {
		auto activeItem = ItemSuite9().GetActiveItem();
		if (!activeItem) {
			enableCommand(false);
			return;
		}
		AE_ItemType itemType = ItemSuite9().GetItemType(activeItem);
		bool enable = activeItem && (itemType == AE_ItemType::FOOTAGE || itemType == AE_ItemType::COMP);
		enableCommand(enable);
	}


};

class Grabba : public Plugin {
	public:
	Grabba(struct SPBasicSuite* pica_basicP,
		AEGP_PluginID aegp_plugin_id,
		AEGP_GlobalRefcon* global_refconV)
		: Plugin(pica_basicP, aegp_plugin_id, global_refconV)
	{
	}

	inline void onInit() override
	{
		addCommand(std::make_unique<GrabbaCommand>());
		registerCommandHook();
		registerUpdateMenuHook();
	}

	void onDeath() override
	{
	}

	void onIdle() override
	{
	}
};
