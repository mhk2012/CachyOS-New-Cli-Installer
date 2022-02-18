#include "config.hpp"
#include "definitions.hpp"  // for error_inter

#include <filesystem>  // for exists
#include <memory>      // for unique_ptr, make_unique, operator==

static std::unique_ptr<Config> s_config = nullptr;

namespace fs = std::filesystem;

bool Config::initialize() noexcept {
    if (s_config != nullptr) {
        error_inter("You should only initialize it once!\n");
        return false;
    }
    s_config = std::make_unique<Config>();
    if (s_config) {
        s_config->m_data["hostcache"] = static_cast<std::int32_t>(!fs::exists("/run/miso/bootmnt"));

        s_config->m_data["H_INIT"] = "openrc";
        s_config->m_data["SYSTEM"] = "BIOS";
        s_config->m_data["KEYMAP"] = "us";
        s_config->m_data["XKBMAP"] = "us";

        // file systems
        s_config->m_data["BTRFS"]        = 0;
        s_config->m_data["LUKS"]         = 0;
        s_config->m_data["LUKS_DEV"]     = "";
        s_config->m_data["LUKS_NAME"]    = "";
        s_config->m_data["LUKS_OPT"]     = "";  // Default or user-defined?
        s_config->m_data["LUKS_UUID"]    = "";
        s_config->m_data["LVM"]          = 0;
        s_config->m_data["LVM_LV_NAME"]  = "";  // Name of LV to create or use
        s_config->m_data["LVM_SEP_BOOT"] = 0;

        // Mounting
        s_config->m_data["MOUNTPOINT"] = "/mnt";

        // Installation
        s_config->m_data["GRAPHIC_CARD"] = "";
    }

    return s_config.get();
}

auto Config::instance() -> Config* {
    return s_config.get();
}
