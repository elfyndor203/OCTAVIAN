add_library(Core
	internal/errors/errorHandling.c

    include/CoreErrors.h
	internal/errors/errorCodes.h
    internal/errors/errorHandling.h
    internal/standards/coreStandards.h
)

target_include_directories(Core
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/internal
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)