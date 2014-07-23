# shihchin.weng@gmail.com

set(H_FILES
    Exceptions.h
    Grid.h
    io/Archive.h
    io/Compression.h
    io/File.h
    io/GridDescriptor.h
    io/Queue.h
    io/Stream.h
    math/BBox.h
    math/Coord.h
    math/DDA.h
    math/FiniteDifference.h
    math/Hermite.h
    math/LegacyFrustum.h
    math/Maps.h
    math/Mat.h
    math/Mat3.h
    math/Mat4.h
    math/Math.h
    math/Operators.h
    math/Proximity.h
    math/QuantizedUnitVec.h
    math/Quat.h
    math/Ray.h
    math/Stats.h
    math/Stencils.h
    math/Transform.h
    math/Tuple.h
    math/Vec2.h
    math/Vec3.h
    math/Vec4.h
    Metadata.h
    metadata/Metadata.h
    metadata/MetaMap.h
    metadata/StringMetadata.h
    openvdb.h
    Platform.h
    PlatformConfig.h
    tools/Composite.h
    tools/Dense.h
    tools/DenseSparseTools.h
    tools/Filter.h
    tools/GridOperators.h
    tools/GridTransformer.h
    tools/Interpolation.h
    tools/LevelSetAdvect.h
    tools/LevelSetFilter.h
    tools/LevelSetFracture.h
    tools/LevelSetMeasure.h
    tools/LevelSetMorph.h
    tools/LevelSetRebuild.h
    tools/LevelSetSphere.h
    tools/LevelSetTracker.h
    tools/LevelSetUtil.h
    tools/MeshToVolume.h
    tools/Morphology.h
    tools/ParticlesToLevelSet.h
    tools/PointAdvect.h
    tools/PointScatter.h
    tools/RayIntersector.h
    tools/RayTracer.h
    tools/Statistics.h
    tools/ValueTransformer.h
    tools/VectorTransformer.h
    tools/VolumeToMesh.h
    tools/VolumeToSpheres.h
    tree/InternalNode.h
    tree/Iterator.h
    tree/LeafManager.h
    tree/LeafNode.h
    tree/LeafNodeBool.h
    tree/NodeUnion.h
    tree/RootNode.h
    tree/Tree.h
    tree/TreeIterator.h
    tree/Util.h
    tree/ValueAccessor.h
    Types.h
    util/CpuTimer.h
    util/Formats.h
    util/logging.h
    util/MapsUtil.h
    util/Name.h
    util/NodeMasks.h
    util/NullInterrupter.h
    util/Util.h
    version.h )

set(CXX_FILES
    Grid.cc
    io/Archive.cc
    io/Compression.cc
    io/File.cc
    io/GridDescriptor.cc
    io/Queue.cc
    io/Stream.cc
    math/Hermite.cc
    math/Maps.cc
    math/Proximity.cc
    math/QuantizedUnitVec.cc
    math/Transform.cc
    metadata/Metadata.cc
    metadata/MetaMap.cc
    openvdb.cc
    Platform.cc
    util/Formats.cc
    util/Util.cc )

set(SOURCE_FILES ${H_FILES} ${CXX_FILES})

include_directories(${OPENVDB_INCLUDE_DIRS})

if(BUILD_STATIC)
    add_library(openvdb ${SOURCE_FILES})
else()
    add_library(openvdb MODULE ${SOURCE_FILES})
    target_link_libraries(openvdb ${OPENVDB_LINK_LIBRARIES})
endif()

set_target_properties(openvdb
    PROPERTIES
    COMPILE_FLAGS "-DOPENVDB_PRIVATE /bigobj"
    VERSION ${VERSION})

install(TARGETS openvdb DESTINATION lib)

foreach(HEADER ${H_FILES})
  string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
  install(FILES ${HEADER} DESTINATION include/openvdb/${DIR})
endforeach(HEADER HEADERS)

option(BUILD_OPENVDB_TOOL "Build OpenVDB command line tools" OFF)
option(BUILD_OPENVDB_TEST "BUILD unit tests" OFF)
# option(BUILD_OPENVDB_PYTHON "BUILD Python Binding" OFF)

if(BUILD_OPENVDB_TOOL)
    add_subdirectory(cmd)
endif()

if(BUILD_OPENVDB_TEST)
    add_subdirectory(unittest)
endif()

add_subdirectory(viewer)