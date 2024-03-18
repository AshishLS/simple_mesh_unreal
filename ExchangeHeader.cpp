#pragma once

#include "string.h"
#include "ExchangeHeader.h"
#define INPUT_FILE "/prc/_micro engine.prc"


//Exported method that invertes a given boolean.
bool getInvertedBool(bool boolState)
{
	return bool(!boolState);
}

void initializeAndLoad(const wchar_t* filePath)
{
	/////////////////////////////////////////////////////
	// INITIALIZE HOOPS EXCHANGE AND LOAD THE MODEL FILE.
	A3DSDKHOOPSExchangeLoader he_loader(HE_BINARY_DIRECTORY);
	assert(he_loader.m_eSDKStatus == A3D_SUCCESS);

	//A3DImport he_import(filePath);
	A3DImport he_import("/prc/_micro engine.prc");
	A3DStatus status = he_loader.Import(he_import);
	assert(status == A3D_SUCCESS);
	A3DAsmModelFile* model_file = he_loader.m_psModelFile;

	////////////////////////////////////////////////////////
	// TRAVERSE THE MODEL TREE
	//TraverseData     data_traverse;
	A3DTree* hnd_tree = 0;

	status = A3DTreeCompute(model_file, &hnd_tree, 0);
	assert(status == A3D_SUCCESS);

	A3DTreeNode* hnd_root_node = 0;
	status = A3DTreeGetRootNode(hnd_tree, &hnd_root_node);
	assert(status == A3D_SUCCESS);

	he_traverse_tree(hnd_tree, hnd_root_node);

	A3DTreeCompute(0, &hnd_tree, 0);

	/////////////////////////////////////////////////////////
	// Everything is loaded to GPU, Exchange can be released.
	A3DAsmModelFileDelete(model_file);

	//return mesh_data;
}

bool unInitializeExchange()
{
	A3DDllTerminate();
	A3DSDKUnloadLibrary();
	return true;
}

void he_traverse_tree(A3DTree* const hnd_tree, A3DTreeNode* const hnd_node)
{
	// Extract the geometry as an A3DMeshData instance and send it to the GPU
	// if the operation is successful.
	A3DMeshData mesh_data;
	A3D_INITIALIZE_DATA(A3DMeshData, mesh_data);
	A3DStatus code = A3DTreeNodeGetGeometry(hnd_tree, hnd_node, A3D_TRUE, &mesh_data, 0);

	if (code == A3D_SUCCESS) {

		// Search for existing geometry, insert new one if new
		A3DEntity* hnd_ri = 0;
		A3DTreeNodeGetEntity(hnd_node, &hnd_ri);

		/////////////////////////////////////////////////////////
		///	Extract the Points Here and Send Back   /////////////
		/////////////////////////////////////////////////////////

		// Release the mesh data memory
		A3DTreeNodeGetGeometry(0, 0, A3D_TRUE, &mesh_data, 0);

		// Get the net transform of the node
		A3DMiscTransformation* hnd_net_transform = 0;
		A3DTreeNodeGetNetTransformation(hnd_node, &hnd_net_transform);
	}

	// Recursively traverse the child nodes
	A3DUns32 n_children = 0;
	A3DTreeNode** hnd_children = 0;

	code = A3DTreeNodeGetChildren(hnd_tree, hnd_node, &n_children, &hnd_children);
	assert(code == A3D_SUCCESS);
	for (size_t c = 0; c < n_children; ++c) {
		he_traverse_tree(hnd_tree, hnd_children[c]);
	}
	A3DTreeNodeGetChildren(0, 0, &n_children, &hnd_children);
}

