from conans import ConanFile, CMake, tools


class MicrolithCppConan(ConanFile):
    name = "microlith"
    version = "0.0.5"
    description = "C++ subscription-based DI framework"
    url = "https://github.com/dragozir/microlith"
    license = "MIT"
    author = "Jake F Hyde (dragozir@gmail.com)"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        'build_type': ['Debug', 'Release'],
        'shared': [True, False],
        'fPIC': [True, False],
        'log': [True, False]
    }
    default_options = {
        'build_type': 'Release',
        'shared': True,
        'fPIC': True,
        'log': True
    }
    requires = (
        "ctti/0.0.2",
    )
    build_requires = (
        "cmake/3.19.7",
        "ninja/1.10.2",
        "gtest/1.10.0"
    )
    exports_sources = "cmake/*", "CMakeLists.txt", "include/*", "src/*", "test/*"
    generators = "cmake", "cmake_find_package", "cmake_paths"

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['MICROLITH_VERSION'] = self.version
        if not self.options.log:
            cmake.definitions['MICROLITH_NO_SPDLOG'] = '1'
        cmake.configure()
        return cmake

    def requirements(self):
        if self.options.log:
            self.requires("spdlog/1.8.2")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test()

    def package(self):
        self.cpp_info.libs = tools.collect_libs(self)
        cmake = self._configure_cmake()
        cmake.install()
