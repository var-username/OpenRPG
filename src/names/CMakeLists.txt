set(NAMES_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/names/)

set(NAMES_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/names.cpp
)

add_library(names SHARED ${NAMES_SOURCE})

if(MSVC OR WIN32)
GENERATE_EXPORT_HEADER(names           
    EXPORT_FILE_NAME ${NAMES_INCLUDE_DIR}/exports/names_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)
endif()

target_link_libraries(names core)

# if the names library needs a higher standard than C++14 please update here
set_property(TARGET names PROPERTY CXX_STANDARD 14)
set_property(TARGET names PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS names
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT Modules
)

set(NG_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/name-generator.cpp  
)

add_executable(name-generator ${NG_SOURCES})
target_link_libraries(name-generator core names)

# if the name-generator executable needs a higher standard than C++14 please update here
set_property(TARGET name-generator PROPERTY CXX_STANDARD 14)
set_property(TARGET name-generator PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS name-generator
    DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT Programs
)
