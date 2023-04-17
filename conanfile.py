import os
from conan import ConanFile
from conan.tools.files import save, load, copy
from conan.tools.gnu import AutotoolsToolchain, AutotoolsDeps
from conan.tools.microsoft import unix_path, VCVars, is_msvc
from conan.errors import ConanInvalidConfiguration
from conan.errors import ConanException
from conan.tools.cmake import cmake_layout , CMakeToolchain, CMake

class Khustup(ConanFile):
    name = "khustup"
    # Optional metadata
    author = "azat.manukyan@gmail.com"
    description = ""
    no_copy_source = True
    url = "git@github.com:zapredelom/khustup.git"
    license = "© Zapredelom"
    topics = ("nodeaddon", "node")
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "package.json", "READEME.md", "src/*", "test/*", "include/*"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    def package(self):
        copy(self, "*/*.h", dst = f"./include/{self.name}", src = "src")
        copy(self, "./include/*", dst = f"./include/{self.name}", src = "src")

    def package_id(self):
        pass

    def package_info(self):
        self.cpp_info.names["pkg_config"] = [self.name]
        self.cpp_info.libs = ["models.lib", "services.lib", "utils.lib"]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def requirements(self):
        self.requires("gtest/1.13.0")
        self.requires("boost/1.81.0")
        self.requires("libwebp/1.3.0")
        #self.requires("opencv/4.5.5")

    def layout(self):
        cmake_layout(self, build_folder="build", src_folder=".")

    def imports(self):
        self.copy("*.dll", dst = os.path.join(self.build_folder,"bin"), src="bin")
        self.copy("*.dll", dst = os.path.join(self.build_folder,"bin"), src="lib")
        self.copy("*.exe", dst = os.path.join(self.build_folder,"bin"), src="bin")
        self.copy("*.dylib", dst = os.path.join(self.build_folder,"bin"), src="bin")
        self.copy("*.so", dst = os.path.join(self.build_folder,"bin"), src="bin")
