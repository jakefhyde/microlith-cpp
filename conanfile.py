from conans import ConanFile, CMake


class MicrolithicCppConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    requires = (
        # "ctti/0.0.2",
        "gtest/1.10.0",
        "spdlog/1.8.2"
    )

    default_options = {"*:shared":True}

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


