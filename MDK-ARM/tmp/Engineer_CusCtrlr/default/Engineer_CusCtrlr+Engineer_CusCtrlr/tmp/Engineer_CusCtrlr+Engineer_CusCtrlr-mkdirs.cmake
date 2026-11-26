# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr")
  file(MAKE_DIRECTORY "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr")
endif()
file(MAKE_DIRECTORY
  "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/1"
  "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr"
  "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr/tmp"
  "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr/src/Engineer_CusCtrlr+Engineer_CusCtrlr-stamp"
  "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr/src"
  "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr/src/Engineer_CusCtrlr+Engineer_CusCtrlr-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr/src/Engineer_CusCtrlr+Engineer_CusCtrlr-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/robomaster/test_pid/MDK-ARM/tmp/Engineer_CusCtrlr/default/Engineer_CusCtrlr+Engineer_CusCtrlr/src/Engineer_CusCtrlr+Engineer_CusCtrlr-stamp${cfgdir}") # cfgdir has leading slash
endif()
