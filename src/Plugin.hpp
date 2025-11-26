#pragma once
#include <memory>

class Plugin {
public:
	static Plugin &Get();

	void Initialize();
	void Shutdown();

private:
	Plugin() = default;
	~Plugin() = default;

	void *menuAction = nullptr;
};
