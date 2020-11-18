cmake_minimum_required(VERSION 3.10)

project(numpy-c-extension C)


find_package(Python)

FIND_PACKAGE(
        PythonLibs
        3
    COMPONENTS
        NumPy
    REQUIRED
)

python_add_module(npextension mymodule.c)

message(STATUS "PythonLibs_INCLUDE_DIRS=${PythonLibs_INCLUDE_DIR}")
message(STATUS "Python_INCLUDE_DIRS=${Python_INCLUDE_DIR}")
message(STATUS "PYTHON_INCLUDE_DIRS=${PYTHON_INCLUDE_DIR}")
message(STATUS "PYTHON_LIBRARIES=${PYTHON_LIBRARIES}")
target_include_directories(npextension PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(npextension PRIVATE ${PYTHON_LIBRARIES})

if(${APPLE})
    # Because Numpy header files are in a weird place on Apple
    # /Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/site-packages/numpy/core/include
    # which contains a directory called numpy which has the headers.
    # On Ubuntu 18, we have it in the regular python include directory:
    # /usr/include/python3.6m contains a directory (a link) called numpy, it points to the numpy directory
    # in the .../numpy/core/include
    FIND_PACKAGE(Python3 COMPONENTS NumPy)
    message(STATUS "Python3_NumPy_INCLUDE_DIRS=${Python3_NumPy_INCLUDE_DIRS}")
    message(STATUS "Python3_NumPy_LIBRARIES=${Python3_NumPy_LIBRARIES}")
    message(STATUS "Python3_INCLUDE_DIRS=${Python3_INCLUDE_DIRS}")
    message(STATUS "Python3_LIBRARIES=${Python3_LIBRARIES}")
    target_include_directories(npextension PRIVATE ${Python3_NumPy_INCLUDE_DIRS})
endif()


configure_file(setup.in.sh setup.sh @ONLY)
