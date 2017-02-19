#pragma once

#include "Vector3.h"
#include "Grid.h"
#include "EntityBase.h"
#include "../FPSCamera.h"

class CSpatialPartition
{
protected:
	// Variables
	CGrid* theGrid;
	int xSize;
	int ySize;
	int xGridSize;
	int yGridSize;
	int xNumOfGrid;
	int yNumOfGrid;
	std::string _meshName; // Name of the mesh

	bool showGrid;
public:
	// Constructor
	CSpatialPartition(void);
	~CSpatialPartition(void);

	// Initialise the spatial partition
	bool Init(	const int xGridSize, const int yGridSize, 
				const int xNumOfGrid, const int yNumOfGrid);

	// Set a particular grid's Mesh
	void SetMesh(const std::string& _meshName);

	// ApplyMesh
	void ApplyMesh(void);

	// Update the spatial partition
	void Update(void);
	// Render the spatial partition
	void Render(Vector3* theCameraPosition = NULL);

	// Get xSize of the entire spatial partition
	int GetxSize(void) const;
	// Get zSize of the entire spatial partition
	int GetySize(void) const;
	// Get xSize
	int GetxGridSize(void) const;
	// Get zNumOfGrid
	int GetyGridSize(void) const;
	// Get xNumOfGrid
	int GetxNumOfGrid(void) const;
	// Get zNumOfGrid
	int GetyNumOfGrid(void) const;

	// Get a particular grid
	CGrid* GetGrid(const int xIndex, const int zIndex) const;
	// Get grid from position
	CGrid* GetGrid(Vector3& position) const;
	// Get grid of where object resides in
	CGrid* GetGrid(EntityBase* object);

	// Get vector of objects from this Spatial Partition
	vector<EntityBase*> GetObjects(Vector3 position, const float radius);

	// Add a new object
	void Add(EntityBase* theObject);
	// Remove but not delete object from this grid
	void Remove(EntityBase* theObject);

	//PrintSelf
	void PrintSelf() const;

	// The vector of objects due for migration to another grid
	vector<EntityBase*> MigrationList;
};
