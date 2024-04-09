#include <AETK/AEGP/AEGP.hpp>

static A_long				S_idle_count = 0L;

class GrabbaCommand : public Command {
	public:
	GrabbaCommand() : Command("Grabba", MenuID::EXPORT) {}
	inline void execute() override;

	inline void updateMenu() override;

};

class Grabba : public Plugin {
	public:
	Grabba(struct SPBasicSuite* pica_basicP,
		AEGP_PluginID aegp_plugin_id,
		AEGP_GlobalRefcon* global_refconV)
		: Plugin(pica_basicP, aegp_plugin_id, global_refconV)
	{
	}

	inline void onInit();

	void onDeath();

	void onIdle();
};