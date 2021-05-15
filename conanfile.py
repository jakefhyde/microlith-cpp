from conans import ConanFile, CMake


class MicrolithCppConan(ConanFile):
    name = "microlith"
    version = "0.0.3"
    description = "C++ subscription-based DI framework"
    url = "https://github.com/dragozir/microlith"
    license = "MIT"
    author = "Jake F Hyde (dragozir@gmail.com)"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        'shared': [True, False],
        'fPIC': [True, False]
    }
    default_options = {'shared': True, 'fPIC': True}
    requires = (
        "ctti/0.0.2",
        "gtest/1.10.0",
        "spdlog/1.8.2"
    )
    build_requires = (
        "cmake/3.19.7",
        "ninja/1.10.2",
    )
    exports_sources = "cmake/*", "CMakeLists.txt", "include/*", "src/*", "test/*"
    generators = "cmake"

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['MICROLITH_VERSION'] = self.version
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
