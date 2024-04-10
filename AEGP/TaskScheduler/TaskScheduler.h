#include <AETK/AEGP/AEGP.hpp>

static A_long				S_idle_count = 0L;

class TaskSchedulerCommand : public Command {
	public:
		TaskSchedulerCommand() : Command("Skeleton", MenuID::FILE) {}
	inline void execute() override;

	inline void updateMenu() override;

};

class TaskScheduler : public Plugin {
	public:
		TaskScheduler(struct SPBasicSuite* pica_basicP,
		AEGP_PluginID aegp_plugin_id,
		AEGP_GlobalRefcon* global_refconV)
		: Plugin(pica_basicP, aegp_plugin_id, global_refconV)
	{
	}

	inline void onInit();

	void onDeath();

	void onIdle();

};