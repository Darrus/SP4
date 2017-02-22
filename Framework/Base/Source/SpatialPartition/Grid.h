#pragma once

#include "EntityBase.h"
#include "Vector3.h"
#include <vector>
using namespace std;

//Include GLEW
#include <GL/glew.h>

class Mesh;

class CGrid
{
protected:
	// We use a Vector3 to store the indices of this Grid within the Spatial Partition array.
	Vector3 index;
	// We use a Vector3 to store the size of this Grid within the Spatial Partition array.
	Vector3 size;
	// We use a Vector3 to store the x- and z-offset of this Grid.
	Vector3 offset;
	// We use a Vector3 to store the x- and z-offset of this Grid.
	Vector3 min, max;
	// List of objects in this grid
	vector<EntityBase*> ListOfObjects;
	// The mesh to represent the grid
	Mesh* theMesh;

	

public:
	// Constructor
	CGrid(void);
	// Destructor
	~CGrid(void);

	// Init
	void Init(	const int xIndex, const int yIndex, 
				const int xGridSize, const int yGridSize,
				const float xOffset = 0, const float yOffset = 0);

	// Set a particular grid's Mesh
	void SetMesh(const std::string& _meshName);

	// Update the grid
	void Update(vector<EntityBase*>* migrationList);
	// Render the grid
	void Render(void);

	// Add a new object to this grid
	void Add(EntityBase* theObject);
	// Remove but not delete all objects from this grid
	void Remove(void);
	// Remove but not delete an object from this grid
	bool Remove(EntityBase* theObject);

	// Check if an object is in this grid
	bool IsHere(EntityBase* theObject) const;

	// Get list of objects in this grid
	vector<EntityBase*> *GetListOfObject(void);

	// Get amount of objects in grid
	inline int GetObjectCount() const { return ListOfObjects.size(); }

	// PrintSelf
	void PrintSelf();

	// Check for collision
	void CheckForCollision();

	// Check if any entity is dead
	void CheckDead();
};
