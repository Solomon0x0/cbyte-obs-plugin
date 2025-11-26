#include "Plugin.hpp"
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QAction>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

Plugin &Plugin::Get()
{
	static Plugin instance;
	return instance;
}

void Plugin::Initialize()
{
	blog(LOG_INFO, "[CByte] Plugin initialize...");

	menuAction = obs_frontend_add_tools_menu_qaction("CByte Plugin Test");

	auto qtAction = static_cast<QAction *>(menuAction);

	QObject::connect(qtAction, &QAction::triggered, []() {
		auto mainWindow = static_cast<QMainWindow *>(obs_frontend_get_main_window());

		QMessageBox::information(mainWindow, "CByte Plugin",
					 "Qt Backend worked.");
	});
}

void Plugin::Shutdown()
{
	blog(LOG_INFO, "[CByte] Plugin shutdown...");
}