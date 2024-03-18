# simple_mesh_unreal
Experimental project to connect HOOPS Exchange With Unreal Engine

Step 1- Clone the project-

Step 2- Download HOOPS exchange version (2024.1.0 and above). dont forget to set the license.

Step 3 - Defind an enviromental variable - HEXCHANGE_INSTALL_DIR pointing to the root folder of HOOPS Exchange. This folder should have bin, include etc ....

Step 4 - Open the project / SlN in Visual Studio 2019 and avove.

Step 5 - look for compiled DLL.


DLL Exports below functions - 
1. getInvertedBool(bool boolState); - Dummy function to test if the DLL is working or not before going in the complexity of HE.
2. initializeAndLoad(const wchar_t* filePath); - Provided a model file path, this should Initialize exchange, Load the model and Traberse the tree. This should also return the meshdata but not implemeneted yet.
3. unInitializeExchange(); - This should be called before closing app.
