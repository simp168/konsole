

add_library(konsoleprofile
STATIC
    Profile.cpp
    ProfileCommandParser.cpp
    ProfileGroup.cpp
    ProfileList.cpp
    ProfileReader.cpp
    ProfileWriter.cpp
    ProfileManager.cpp
    ${konsoleprofile_SRCS}
)

target_link_libraries(
    konsoleprofile
    ${konsole_LIBS}
    konsoleprivate_core
    konsolecolorscheme
    keyboardtranslator
    konsolehelpers
)
