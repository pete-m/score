set(SCORE_SANITIZE True)
set(SCORE_STATIC_PLUGINS True)
set(SCORE_AUDIO_PLUGINS True CACHE INTERNAL "")

include(all-plugins)

set(SCORE_PCH True)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(SCORE_PCH False)
endif()
