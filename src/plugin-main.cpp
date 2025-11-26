#include <obs-module.h>
#include "Plugin.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("cbyte-obs-plugin", "en-US")

bool obs_module_load(void)
{
	Plugin::Get().Initialize();
	return true;
}

void obs_module_unload(void)
{
	Plugin::Get().Shutdown();
}

const char *obs_module_description(void)
{
	return "CByte Modern OBS Plugin";
}
const char *obs_module_name(void)
{
	return "CByte Plugin";
}
