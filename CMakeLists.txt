# Daniel Sebastian Iliescu, http://dansil.net
# MIT License (MIT), http://opensource.org/licenses/MIT

cmake_minimum_required( VERSION 3.5.2 )

project( Fractals CXX )

# Create the executable given the source directory
set( SOURCE_DIRECTORY Sources )
set( EXECUTABLE_NAME ${PROJECT_NAME}${SOURCE_DIRECTORY} )
add_executable(
	${EXECUTABLE_NAME}
	${SOURCE_DIRECTORY}/main.cpp )

# Include the source headers
set( SOURCE_HEADERS Sources/Includes )
target_include_directories(
	${EXECUTABLE_NAME}
	PRIVATE
		${SOURCE_HEADERS} )

# Enforce C++14 standard and output settings
set_target_properties(
	${EXECUTABLE_NAME}
	PROPERTIES
		CMAKE_CXX_STANDARD 14
		CMAKE_CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Additional compiler options
set( CLANG_GNU_COMPILER_OPTIONS "-Wall" "-Wextra" "-Werror" "-Wshadow" "-Wnon-virtual-dtor" "-pedantic" )
set( CLANG_COMPILER_OPTIONS ${CLANG_GNU_COMPILER_OPTIONS} )
set( GNU_COMPILER_OPTIONS ${CLANG_GNU_COMPILER_OPTIONS} )
set( MSVC_COMPILER_OPTIONS "/W4" "/WX" )

if ( CMAKE_CXX_COMPILER_ID MATCHES Clang )
	set( COMPILER_OPTIONS ${CLANG_COMPILER_OPTIONS} )
elseif( CMAKE_CXX_COMPILER_ID MATCHES GNU )
	set( COMPILER_OPTIONS ${CLANG_GNU_COMPILER_OPTIONS} )
elseif( CMAKE_CXX_COMPILER_ID MATCHES MSVC )
	set( COMPILER_OPTIONS ${MSVC_COMPILER_OPTIONS} )
endif()

target_compile_options(
	${EXECUTABLE_NAME}
	PRIVATE
		${COMPILER_OPTIONS} )