# Generated from orogen/lib/orogen/templates/tasks/CMakeLists.txt

include(modemdriverTaskLib)
ADD_LIBRARY(${MODEMDRIVER_TASKLIB_NAME} SHARED 
    ${MODEMDRIVER_TASKLIB_SOURCES})
add_dependencies(${MODEMDRIVER_TASKLIB_NAME}
    regen-typekit)

TARGET_LINK_LIBRARIES(${MODEMDRIVER_TASKLIB_NAME}
    ${OrocosRTT_LIBRARIES}
    ${MODEMDRIVER_TASKLIB_DEPENDENT_LIBRARIES})
SET_TARGET_PROPERTIES(${MODEMDRIVER_TASKLIB_NAME}
    PROPERTIES LINK_INTERFACE_LIBRARIES "${MODEMDRIVER_TASKLIB_INTERFACE_LIBRARIES}")

INSTALL(TARGETS ${MODEMDRIVER_TASKLIB_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/orocos)

INSTALL(FILES ${MODEMDRIVER_TASKLIB_HEADERS}
    DESTINATION include/orocos/modemdriver)

