#include "Utils.h"

std::string Utils::getRoamPath() {
	char* path = NULL;
	size_t length;

	_dupenv_s(&path, &length, "appdata");
	std::string pathReal = std::string(path) + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState");
	return pathReal;
}

std::string Utils::getClientFolderPath() {
	std::string path = getRoamPath() + "\\Kyrie";
	return path;
}

std::string Utils::getConfigsFolderPath() {
	std::string path = getClientFolderPath() + "\\Configs";
	return path;
}

void Utils::DebugF(const char* output, ...) {
	std::string path = getClientFolderPath() + "\\Logs.txt";

	va_list arg;
	va_start(arg, output);
	
	char message[300];
	vsprintf_s(message, 300, output, arg);

	CloseHandle(CreateFileA(path.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

	std::ofstream fStream;
	fStream.open(path.c_str(), std::ios::app);

	if (fStream.is_open()) fStream << message << std::endl;
	fStream.close();

	va_end(arg);
}

uintptr_t Utils::getGameAddress() {
	static uintptr_t address = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));
	return address;
}

uintptr_t Utils::findSignature(std::string_view sig) {
	auto address = hat::parse_signature(sig);
	if (!address.has_value()) {
		return 0;
	}
	auto signature = address.value();

	const auto module = hat::process::get_process_module();
	auto result = hat::find_pattern(signature, ".text", module);

	if (result.has_result())
		return reinterpret_cast<uintptr_t>(result.get());

	return 0;
}

uintptr_t** Utils::getVtableFromSig(std::string_view sig) {
	uintptr_t address = findSignature(sig);

	if (address == 0x0)
		return nullptr;

	int finalOffset = *reinterpret_cast<int*>((address + 3));
	return reinterpret_cast<uintptr_t**>(address + finalOffset + 7);
}
