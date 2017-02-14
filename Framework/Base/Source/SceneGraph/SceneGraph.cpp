#include "SceneGraph.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

CSceneGraph::CSceneGraph(void)
	: ID(0)
	, theRoot(NULL)
{
	theRoot = new CSceneNode();
	// Assign the first ID to the root. Default is 0
	theRoot->SetID(this->GenerateID());
}

CSceneGraph::~CSceneGraph()
{
}

void CSceneGraph::Destroy()
{
	if (theRoot)
	{
		theRoot->Destroy();
		delete theRoot;
	}
	Singleton<CSceneGraph>::Destroy();
}

CSceneNode* CSceneGraph::GetRoot() 
{ 
	return theRoot; 
}

// Add a Node to this Scene Graph
CSceneNode* CSceneGraph::AddNode(EntityBase* theEntity)
{
	CSceneNode* aNewSceneNode = theRoot->AddChild(theEntity);
//	aNewSceneNode->SetID(this->GenerateID());
	return aNewSceneNode;
}

// Delete a Node from this Scene Graph using the pointer to the node
bool CSceneGraph::DeleteNode(EntityBase* theEntity)
{
	return theRoot->DeleteChild(theEntity);
}

// Delete a Node from this Scene Graph using its ID
bool CSceneGraph::DeleteNode(const int ID)
{
	return theRoot->DeleteChild(ID);
}

// Attach a Node to the root
CSceneNode* CSceneGraph::AttachNode(CSceneNode* theNode)
{
	theRoot->AttachNode(theNode);
	return theNode;
}

// Detach a Node from this Scene Graph using the pointer to the node
CSceneNode* CSceneGraph::DetachNode(CSceneNode* theNode)
{
	return NULL;// theRoot->DetachChild(theNode);
}

// Detach a Node from this Scene Graph using its ID
CSceneNode* CSceneGraph::DetachNode(const int ID)
{
	return theRoot->DetachChild(ID);
}

// Get a Node using the pointer to the node
CSceneNode* CSceneGraph::GetNode(EntityBase* theEntity)
{
	return theRoot->GetEntity(theEntity);
}

// Get a Node using its ID
CSceneNode* CSceneGraph::GetNode(const int ID)
{
	return theRoot->GetEntity(ID);
}

// Return the number of nodes in this Scene Graph
int CSceneGraph::GetNumOfNode(void)
{
	return theRoot->GetNumOfChild();
}

// Generate an ID for a Scene Node
int CSceneGraph::GenerateID(void)
{
	// Return the ID and increment the value by 1
	return ID++;
}

// Update the Scene Graph
void CSceneGraph::Update(void)
{
	theRoot->Update();
}
// Render the Scene Graph
void CSceneGraph::Render(void)
{
	theRoot->Render();
}

// PrintSelf for debug purposes
void CSceneGraph::PrintSelf(void)
{
	theRoot->PrintSelf();
}
