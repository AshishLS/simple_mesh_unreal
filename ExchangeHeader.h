#pragma once  

#define DLL_EXPORT __declspec(dllexport)    //shortens __declspec(dllexport) to DLL_EXPORT

#include <cassert>
#define INITIALIZE_A3D_API
#include <A3DSDKIncludes.h>

#ifdef __cplusplus        //if C++ is used convert it to C to prevent C++'s name mangling of method names
extern "C"
{
#endif

	bool DLL_EXPORT getInvertedBool(bool boolState);
	void DLL_EXPORT initializeAndLoad(const wchar_t* filePath);
	bool DLL_EXPORT unInitializeExchange();

	////////////////////////////////////////////////////////////////////////////////
	// Recursive tree traversal function used to retrieve drawable entities
	void he_traverse_tree(A3DTree* const hnd_tree, A3DTreeNode* const hnd_node);

#ifdef __cplusplus
}
#endif
