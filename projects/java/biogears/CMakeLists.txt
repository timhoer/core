###############################################################################
# Policy adjustments
###############################################################################
cmake_minimum_required(VERSION 3.8.0)
cmake_policy(VERSION 3.8.0)
###############################################################################
# Options
###############################################################################

###############################################################################
# Base Variables
###############################################################################
set(PROJECT_NAME Java_BioGears)
set(PREFIX biogears_jar)

set(${PREFIX}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)
set(${PREFIX}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" )
set(${PREFIX}_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" PARENT_SCOPE)
set(${PREFIX}_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set(${PREFIX}_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
set(${PREFIX}_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}" )
set(${PREFIX}_UNIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/unit" PARENT_SCOPE)

###############################################################################
# Requirments
###############################################################################

###############################################################################
#Code Generation
###############################################################################

###############################################################################
#Sorce and Header Defines
###############################################################################
message(STATUS "Configuring ${PROJECT_NAME}")

add_source_files(SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src "*.java"   "Sources\\")

set(${PREFIX}_HEADERS ${HDRS} ${PUBLIC_HDRS} ${GEN_HDRS})
set(${PREFIX}_SOURCES ${SRCS} ${GEN_SRCS})

string(REGEX REPLACE "Java_" "" SHORT_NAME ${PROJECT_NAME})

add_jar(${PROJECT_NAME}
        JARS_AS_SOURCES
        SOURCES
        ${${PREFIX}_SOURCES}
        Java_DataModelBindings
        Java_CommonDataModel
        Java_BioGearsEngine
        Java_BioGearsGUI
        ${PROJECT_SOURCE_DIR}/share/jar/zip4j-1.3.1.jar
        ${PROJECT_SOURCE_DIR}/share/jar/log4j-1.2.17.jar
        ${PROJECT_SOURCE_DIR}/share/jar/jfreechart-1.0.13.jar
        ${PROJECT_SOURCE_DIR}/share/jar/jcommon-1.0.16.jar
        ${PROJECT_SOURCE_DIR}/share/jar/swtgraphics2d.jar
        ${PROJECT_SOURCE_DIR}/share/jar/jchart2d-3.2.2.jar
        ${PROJECT_SOURCE_DIR}/share/jar/dom4j-1.6.1.jar
        ${PROJECT_SOURCE_DIR}/share/jar/gson-1.4.jar
        ${PROJECT_SOURCE_DIR}/share/jar/guava-11.0.2.jar
        ${PROJECT_SOURCE_DIR}/share/jar/javassist-3.16.1-GA.jar
        ${PROJECT_SOURCE_DIR}/share/jar/jsr305-1.3.9.jar
        ${PROJECT_SOURCE_DIR}/share/jar/reflections-0.9.9-RC1-uberjar.jar
        ${PROJECT_SOURCE_DIR}/share/jar/slf4j-api-1.6.1.jar
        ${PROJECT_SOURCE_DIR}/share/jar/slf4j-simple-1.6.1.jar
        ${PROJECT_SOURCE_DIR}/share/jar/xml-apis-1.0.b2.jar
        ${PROJECT_SOURCE_DIR}/share/jar/xmlbeans-2.6.0.jar
        ${PROJECT_SOURCE_DIR}/share/jar/poi-3.17.jar
        ${PROJECT_SOURCE_DIR}/share/jar/poi-ooxml-3.17.jar
        ${PROJECT_SOURCE_DIR}/share/jar/poi-ooxml-schemas-3.17.jar
        ${PROJECT_SOURCE_DIR}/share/jar/commons-math3-3.6.1.jar
        ${PROJECT_SOURCE_DIR}/share/jar/commons-codec-1.11.jar
        ${PROJECT_SOURCE_DIR}/share/jar/commons-collections4-4.1.jar
        OUTPUT_NAME ${SHORT_NAME}
        MANIFEST ${CMAKE_CURRENT_SOURCE_DIR}/BioGears_manifest.txt
        INCLUDE_JARS 
        )
###############################################################################
#Define Logic
###############################################################################
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    FOLDER "Java"
    OUTPUT_NAME ${SHORT_NAME}
    PROJECT_LABEL "${PROJECT_NAME}"
    )
add_dependencies(${PROJECT_NAME} libbiogears_jni
        Java_DataModelBindings
        Java_CommonDataModel
        Java_BioGearsEngine
        Java_BioGearsGUI)
###############################################################################
# COMPILATION & LINKAGE MODIFICATIONS
###############################################################################
 install_jar(${PROJECT_NAME}
     DESTINATION java
  )

function(genClasspath _var)
  if (CMAKE_HOST_WIN32 AND NOT CYGWIN AND CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_JAVA_INCLUDE_FLAG_SEP ";")
  else ()
    message(STATUS "Using Colon Seperator")
    set(CMAKE_JAVA_INCLUDE_FLAG_SEP ":")
  endif()
  string(REPLACE ";" "${CMAKE_JAVA_INCLUDE_FLAG_SEP}" _result "${ARGN}")
  set (${_var} "${_result}" )
  set (${_var} "${_result}" PARENT_SCOPE)
endfunction()


genClasspath(java_classpath
        ${PROJECT_BINARY_DIR}/outputs/jar/BioGears.jar
        ${PROJECT_BINARY_DIR}/outputs/jar/BioGearsEngine.jar 
        ${PROJECT_BINARY_DIR}/outputs/jar/CommonDataModel.jar 
        ${PROJECT_BINARY_DIR}/outputs/jar/DataModelBindings.jar
        ${PROJECT_BINARY_DIR}/runtime/jar/jdom-2.0.2.jar
        ${PROJECT_BINARY_DIR}/runtime/jar/javax.mail-1.6.1.jar
    )

set (args "")
add_custom_target(gen-data
    COMMAND ${CMAKE_COMMAND} -E echo "${Java_JAVA_EXECUTABLE} -classpath \"${java_classpath}\"   mil.tatrc.physiology.datamodel.dataset.DataSetReader ${args}"
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.datamodel.dataset.DataSetReader ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "InitialPatientStates.config")
add_custom_target(gen-states
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
add_custom_target(gen-docs
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.utilities.testing.validation.SystemValidation
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.utilities.testing.validation.PatientValidation
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.datamodel.doxygen.CDM2MD
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.datamodel.doxygen.DoxygenPreprocessor  doc/markdown doc/doxygen/processed_md
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.datamodel.doxygen.DoxygenPreprocessor  doc/methodolgy doc/doxygen/processed_md
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"  mil.tatrc.physiology.datamodel.doxygen.XSDToDoxygen schema/xsd/BioGearsDataModel.xsd docs/doxygen/process_md/xsd.ixx
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "ValidationSystems.config" )
add_custom_target(run-system-validation
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "")
add_custom_target(report-system-validation
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.validation.SystemValidation ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "ValidationPatients.config")
add_custom_target(run-patient-validation
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "ValidationDrugs.config")
add_custom_target(run-drug-validation
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)

set (args "VerificationScenarios.config")
add_custom_target(run-verification
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)

set (args "DebugRun.config")
add_custom_target(run-debug
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"    mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)

set (args "PlotRun.config")
add_custom_target(run-plots
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.csv.plots.PlotDriver  ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "DebugRun.config")
add_custom_target(run-debug-plots
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.csv.plots.PlotDriver  ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "CDMUnitTests.config")
add_custom_target(run-cdm-tests
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "BGEUnitTests.config")
add_custom_target(run-bge-tests
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.TestDriver ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "ALL true")
add_custom_target(rebase-scenarios
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.Rebase ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "DebugRun.config true")
add_custom_target(rebase-debug
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.utilities.testing.Rebase ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)
set (args "ALL false")
add_custom_target(rebase-tests
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"    mil.tatrc.physiology.utilities.testing ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)

set (args "")
add_custom_target(biogears-gui
    COMMAND ${Java_JAVA_EXECUTABLE} -classpath "${java_classpath}"   mil.tatrc.physiology.biogears.gui.Bio ${args}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/runtime
    VERBATIM
    USES_TERMINAL
)

add_dependencies(gen-states  ${PROJECT_NAME})
add_dependencies(gen-data  ${PROJECT_NAME})
add_dependencies(gen-docs  ${PROJECT_NAME})
add_dependencies(run-system-validation  ${PROJECT_NAME})
add_dependencies(report-system-validation  ${PROJECT_NAME})
add_dependencies(run-patient-validation  ${PROJECT_NAME})
add_dependencies(run-drug-validation  ${PROJECT_NAME})
add_dependencies(run-debug  ${PROJECT_NAME})
add_dependencies(run-plots  ${PROJECT_NAME})
add_dependencies(run-debug-plots  ${PROJECT_NAME})
add_dependencies(run-cdm-tests  ${PROJECT_NAME})
add_dependencies(run-bge-tests  ${PROJECT_NAME})
add_dependencies(rebase-scenarios  ${PROJECT_NAME})
add_dependencies(rebase-debug  ${PROJECT_NAME})
add_dependencies(rebase-tests  ${PROJECT_NAME})
add_dependencies(biogears-gui  ${PROJECT_NAME})


if(ARA_STAGE_RUNTIME)
 add_dependencies(gen-states stage_runtime )
 add_dependencies(gen-data stage_runtime )
 add_dependencies(gen-docs stage_runtime )
 add_dependencies(run-system-validation stage_runtime )
 add_dependencies(report-system-validation stage_runtime )
 add_dependencies(run-patient-validation stage_runtime )
 add_dependencies(run-drug-validation stage_runtime )
 add_dependencies(run-debug stage_runtime )
 add_dependencies(run-plots stage_runtime )
 add_dependencies(run-debug-plots stage_runtime )
 add_dependencies(run-cdm-tests stage_runtime )
 add_dependencies(run-bge-tests stage_runtime )
 add_dependencies(rebase-scenarios stage_runtime )
 add_dependencies(rebase-debug stage_runtime )
 add_dependencies(rebase-tests stage_runtime )
 add_dependencies(biogears-gui stage_runtime )
endif()
set_target_properties(Java_BioGears PROPERTIES FOLDER "Java/jar")

set_target_properties(gen-states PROPERTIES FOLDER "Java/Generate" )
set_target_properties(gen-data   PROPERTIES FOLDER "Java/Generate" )
set_target_properties(gen-docs   PROPERTIES FOLDER "Java/Generate" )


set_target_properties(run-system-validation    PROPERTIES FOLDER "Java/Validation" )
set_target_properties(report-system-validation PROPERTIES FOLDER "Java/Validation" )
set_target_properties(run-patient-validation   PROPERTIES FOLDER "Java/Validation" )
set_target_properties(run-drug-validation      PROPERTIES FOLDER "Java/Validation" )
set_target_properties(run-verification         PROPERTIES FOLDER "Java/Validation" )

set_target_properties(run-debug                PROPERTIES FOLDER "Java" )
set_target_properties(run-plots                PROPERTIES FOLDER "Java" )
set_target_properties(run-debug-plots          PROPERTIES FOLDER "Java" )
set_target_properties(run-cdm-tests            PROPERTIES FOLDER "Java/Test" )
set_target_properties(run-bge-tests            PROPERTIES FOLDER "Java/Test" )
set_target_properties(rebase-scenarios         PROPERTIES FOLDER "Java" )
set_target_properties(rebase-debug             PROPERTIES FOLDER "Java" )
set_target_properties(rebase-tests             PROPERTIES FOLDER "Java" )
set_target_properties(biogears-gui             PROPERTIES FOLDER "Java" )

