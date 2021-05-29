from conans import ConanFile, CMake, tools
import os


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
        'log': [True, False],
        'embed_ctti': [True, False],
    }
    default_options = {
        'build_type': 'Release',
        'shared': True,
        'fPIC': True,
        'log': True,
        'embed_ctti': False
    }
    build_requires = (
        "cmake/3.19.7",
        "ninja/1.10.2",
        "gtest/1.10.0"
    )
    exports_sources = "cmake/*", "CMakeLists.txt", "include/*", "src/*", "test/*", "3rdparty/*"
    generators = "cmake", "cmake_find_package", "cmake_paths"

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['MICROLITH_VERSION'] = self.version
        cmake.definitions['BUILD_SYSTEM'] = 'CONAN'
        if not self.options.log:
            cmake.definitions['MICROLITH_NO_SPDLOG'] = 'ON'
        if self.options.embed_ctti:
            if os.listdir('3rdparty/ctti') == []:
                git = tools.Git()
                git.run("submodule update --init")
            cmake.definitions['MICROLITH_EMBED_CTTI'] = 'ON'
        cmake.configure()
        return cmake

    def requirements(self):
        if self.options.log:
            self.requires("spdlog/1.8.2")
        if not self.options.embed_ctti:
            self.requires("ctti/[>=0.0.1]")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        if self.options.embed_ctti:
            self.copy('*.hpp', dst='include/', src='3rdparty/ctti/include')

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
