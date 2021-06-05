#Copy this file to the application project folder as CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

include(StratifyOS_crt)
include(HalAPI)

set(RAM_SIZE 8192)
project(Blinky CXX C)

sos_sdk_app_target(RELEASE ${PROJECT_NAME} "" release ${SOS_ARCH})
message(STATUS "Stratify API Test Executable ${RELEASE_TARGET}")
add_executable(${RELEASE_TARGET})
target_sources(${RELEASE_TARGET}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/sl_config.h
	${CMAKE_CURRENT_SOURCE_DIR}/sl_settings.json
	)

target_compile_options(${RELEASE_TARGET}
	PRIVATE
	-Os
	)

set_property(TARGET ${RELEASE_TARGET} PROPERTY CXX_STANDARD 17)

set(DEPENDENCIES HalAPI SysAPI VarAPI StratifyOS_crt)

sos_sdk_app_add_arch_targets("${RELEASE_OPTIONS}" "${DEPENDENCIES}" ${RAM_SIZE})
if(SOS_IS_LINK)
	sos_sdk_app_add_arch_targets("${COVERAGE_OPTIONS}" "${DEPENDENCIES}" ${RAM_SIZE})
endif()

target_compile_options(${RELEASE_TARGET}
	PRIVATE
	-Os
	)

