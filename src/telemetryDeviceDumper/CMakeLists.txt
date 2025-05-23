# Copyright (C) 2006-2021 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

yarp_configure_plugins_installation(robometry)

yarp_prepare_plugin(telemetryDeviceDumper
                    CATEGORY device
                    TYPE robometry::TelemetryDeviceDumper
                    INCLUDE TelemetryDeviceDumper.h
                    DEFAULT ON)

if(ENABLE_telemetryDeviceDumper)

  yarp_add_plugin(yarp_telemetryDeviceDumper)

  if(MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
  endif()

  target_sources(yarp_telemetryDeviceDumper PRIVATE TelemetryDeviceDumper.cpp
                                                    TelemetryDeviceDumper.h)
                        
  target_link_libraries(yarp_telemetryDeviceDumper PRIVATE YARP::YARP_os
                                                           YARP::YARP_dev
                                                           robometry::robometry
                                                           ICUB::iCubDev)
  list(APPEND YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS YARP_os
                                                      YARP_dev
                                                      robometry)

  yarp_install(TARGETS yarp_telemetryDeviceDumper
               EXPORT YARP_${YARP_PLUGIN_MASTER}
               COMPONENT ${YARP_PLUGIN_MASTER}
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
               YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

  set(YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS ${YARP_${YARP_PLUGIN_MASTER}_PRIVATE_DEPS} PARENT_SCOPE)

  set_property(TARGET yarp_telemetryDeviceDumper PROPERTY FOLDER "Plugins/Device")
endif()
