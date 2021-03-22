from conans import ConanFile, CMake


class MicrolithCppConan(ConanFile):
    # todo add gcc and cmake as dependencies.
    settings = "os", "compiler", "build_type", "arch"

    build_requires = (
        "cmake/3.19.7",
        "ninja/1.10.2",
    )

    requires = (
        # "ctti/0.0.2",
        "gtest/1.10.0",
        "spdlog/1.8.2"
    )

    default_options = {"*:shared":True}
    
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


