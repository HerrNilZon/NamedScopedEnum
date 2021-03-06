# The MIT License (MIT)
# 
# Copyright (c) 2016 Nils Zander, Tino Bog
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

#------------------------------------------------------------------------------
# NAME THE PROJECT -->	ROOT SOURCE: ${($PROJECT)_SOURCE_DIR} 
#						ROOT BINARY: ${($PROJECT)_BINARY_DIR}
#------------------------------------------------------------------------------
PROJECT ( NamedScopedEnum CXX )

#------------------------------------------------------------------------------
# SET OPTIONS
#------------------------------------------------------------------------------
OPTION ( NAMEDSCOPEDENUM_ENABLE_TESTING "Enable tests for NamedScopedEnum library" ON )
  
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

#------------------------------------------------------------------------------
# INCLUDE DIRECTORY
#------------------------------------------------------------------------------
INCLUDE_DIRECTORIES ( . )	

#------------------------------------------------------------------------------
# CREATE EXAMPLES
#------------------------------------------------------------------------------
ADD_EXECUTABLE ( static_map example/static_map.cpp )
ADD_EXECUTABLE ( basic_usage example/basic_usage.cpp )

#------------------------------------------------------------------------------
# CREATE TARGETS THAT BUILD AND START THE TEST RUNNER
#------------------------------------------------------------------------------

IF ( ${NAMEDSCOPEDENUM_ENABLE_TESTING} )

  FILE ( GLOB TESTSOURCES test/*.cpp )

  ADD_EXECUTABLE ( ${PROJECT_NAME}_testrunner ${TESTSOURCES} )
       
  # build target to run tests contained in the runner
	ADD_CUSTOM_TARGET ( 
    run_${PROJECT_NAME}_tests 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_testrunner
    COMMENT "Running tests for ${PROJECT_NAME}" VERBATIM 
	)
  
  # build runner before execution if changes have been made to sources
	ADD_DEPENDENCIES ( run_${PROJECT_NAME}_tests 
	                   ${PROJECT_NAME}_testrunner )

ENDIF ( ${NAMEDSCOPEDENUM_ENABLE_TESTING} )
