# vim: syntax=cmake
include_directories(inc)

add_library(vdpu34x_com STATIC vdpu34x_com.c vdpu382_com.c)
add_library(vdpu383_com STATIC vdpu383_com.c)

if( HAVE_AVSD )
    add_subdirectory(avsd)
endif()

if( HAVE_AVS2D )
    add_subdirectory(avs2d)
endif()

if( HAVE_H264D )
    add_subdirectory(h264d)
endif()

if( HAVE_H265D )
    add_subdirectory(h265d)
endif()

if( HAVE_VP9D )
    add_subdirectory(vp9d)
endif()

if( HAVE_AV1D )
    add_subdirectory(av1d)
endif()