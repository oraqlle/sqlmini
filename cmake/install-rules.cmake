install(
    TARGETS sqlmini_exe
    RUNTIME COMPONENT sqlmini_runtime
)

if(PROJECT_IS_TOP_LEVEL)
    include(CPack)
endif()
