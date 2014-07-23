///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012-2013 DreamWorks Animation LLC
//
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
//
// Redistributions of source code must retain the above copyright
// and license notice and the following restrictions and disclaimer.
//
// *     Neither the name of DreamWorks Animation nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// IN NO EVENT SHALL THE COPYRIGHT HOLDERS' AND CONTRIBUTORS' AGGREGATE
// LIABILITY FOR ALL CLAIMS REGARDLESS OF THEIR BASIS EXCEED US$250.00.
//
///////////////////////////////////////////////////////////////////////////

/// @author FX R&D OpenVDB team

#include "OpenVDBPlugin.h"

#include <openvdb_maya/OpenVDBData.h>
#include <openvdb_maya/OpenVDBCopyNode.h>
#include <openvdb_maya/OpenVDBFilterNode.h>
#include <openvdb_maya/OpenVDBFromMayaFluidNode.h>
#include <openvdb_maya/OpenVDBFromPolygonsNode.h>
#include <openvdb_maya/OpenVDBReadNode.h>
#include <openvdb_maya/OpenVDBTransformNode.h>
#include <openvdb_maya/OpenVDBVisualizeNode.h>
#include <openvdb_maya/OpenVDBWriteNode.h>

#include <openvdb/Platform.h>
#include <openvdb/openvdb.h>
#include <openvdb/Types.h> // compiler pragmas

#include <maya/MFnPlugin.h>
#include <maya/MFnPluginData.h>

#include <sstream>

namespace mvdb = openvdb_maya;

////////////////////////////////////////

MStatus
initializePlugin(MObject obj)
{
    openvdb::initialize();

    MStatus status;
    MFnPlugin plugin(obj, "DreamWorks Animation", "0.5", "Any");

#ifdef _WIN32
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::stringstream ss;
        ss << "Failed to initialize glew: " << glewGetErrorString(err) << std::endl;
        status.perror(ss.str().c_str());
        return status;
    }
#endif

    status = plugin.registerData("OpenVDBData", OpenVDBData::id, OpenVDBData::creator);
    if (!status) {
        status.perror("Failed to register 'OpenVDBData'");
        return status;
    }

    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBCopyNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBFilterNode>(plugin));    
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBFromMayaFluidNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBFromPolygonsNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBReadNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBTransformNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBVisualizeNode>(plugin, MPxNode::kLocatorNode));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::registerNode<OpenVDBWriteNode>(plugin));

    return status;
}


MStatus
uninitializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin plugin(obj);

    status = plugin.deregisterData(OpenVDBData::id);
    if (!status) {
        status.perror("Failed to deregister 'OpenVDBData'");
        return status;
    }

    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBCopyNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBFilterNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBFromMayaFluidNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBFromPolygonsNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBReadNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBTransformNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBVisualizeNode>(plugin));
    CHECK_MSTATUS_AND_RETURN_IT(mvdb::deregisterNode<OpenVDBWriteNode>(plugin));

    return status;
}


////////////////////////////////////////


// Copyright (c) 2012-2013 DreamWorks Animation LLC
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
