from setuptools import setup, Extension
import sys
import pybind11

# Detect compiler and set correct flags
if sys.platform == "win32":
    extra_compile_args = ["/O2"]
else:
    extra_compile_args = ["-O3"]

ext_modules = [
    Extension(
        "calculus.calculus_core",
        ["calculus_core.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=extra_compile_args,
    ),
]

setup(
    name="calculus-cpp",
    version="0.1.0",
    author="LegedsDaD",
    description="High-performance calculus library using C++ backend",
    packages=["calculus"],
    ext_modules=ext_modules,
    zip_safe=False,
)
