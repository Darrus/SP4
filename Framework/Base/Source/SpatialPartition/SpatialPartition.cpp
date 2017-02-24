#include "SpatialPartition.h"
#include "stdio.h"
#include "Collider\Collider.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "KeyboardController.h"

template <typename T> vector<T> concat(vector<T> &a, vector<T> &b) {
	vector<T> ret = vector<T>();
	copy(a.begin(), a.end(), back_inserter(ret));
	copy(b.begin(), b.end(), back_inserter(ret));
	return ret;
}



/********************************************************************************
 Constructor
 ********************************************************************************/
CSpatialPartition::CSpatialPartition(void)
	: theGrid(NULL)
	, xSize(0)
	, ySize(0)
	, xGridSize(0)
	, yGridSize(0)
	, xNumOfGrid(0)
	, yNumOfGrid(0)
	, _meshName("")
	, showGrid(false)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CSpatialPartition::~CSpatialPartition(void)
{
	delete [] theGrid;
}

/********************************************************************************
 Initialise the spatial partition
 ********************************************************************************/
bool CSpatialPartition::Init(const int xSize, const int ySize, const int xNumOfGrid, const int yNumOfGrid)
{
	if (xSize < 0 || ySize < 0 || xNumOfGrid < 0 || yNumOfGrid < 0)
		return false;

	// Init variables
	this->xSize = xSize;
	this->ySize = ySize;
	this->xNumOfGrid = xNumOfGrid;
	this->yNumOfGrid = yNumOfGrid;
	xGridSize = (int)(xSize / xNumOfGrid);
	yGridSize = (int)(ySize / yNumOfGrid);

	// Create an array of grids
	theGrid = new CGrid[xNumOfGrid * yNumOfGrid];

	// Create an array of grids
	theGrid = new CGrid[xNumOfGrid * yNumOfGrid];

	// Initialise the array of grids
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			theGrid[i * yNumOfGrid + j].Init(i, j, xGridSize, yGridSize, (xSize >> 1), (ySize >> 1));
		}
	}

	// Assign a Mesh to each Grid if available.
	ApplyMesh();

	// Create a migration list vector
	MigrationList.clear();

	return true;
}

/********************************************************************************
 Set a particular grid's Mesh
 ********************************************************************************/
void CSpatialPartition::SetMesh(const std::string& _meshName)
{
	this->_meshName = _meshName;

	// Assign a Mesh to each Grid if available.
	ApplyMesh();
}

/********************************************************************************
  ApplyMesh
 ********************************************************************************/
void CSpatialPartition::ApplyMesh(void)
{
	if (_meshName.size() != 0)
	{
		for (int i = 0; i<xNumOfGrid; i++)
		{
			for (int j = 0; j<yNumOfGrid; j++)
			{
				theGrid[i*yNumOfGrid + j].SetMesh(_meshName);
			}
		}
	}
}

/********************************************************************************
Update the spatial partition
********************************************************************************/
void CSpatialPartition::Update(void)
{
	if (KeyboardController::GetInstance()->IsKeyDown(VK_MENU) && 
		KeyboardController::GetInstance()->IsKeyPressed('S'))
	{
		showGrid = !showGrid;
	}

	// Update the grids
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			if (theGrid[i * yNumOfGrid + j].GetObjectCount() > 0)
				theGrid[i * yNumOfGrid + j].Update(&MigrationList);
		}
	}

	// If there are objects due for migration, then process them
	if (MigrationList.empty() == false)
	{
		// Check each object to see if they are no longer in this grid
 		for (int i = 0; i < MigrationList.size(); ++i)
		{
			Add(MigrationList[i]);
		}

		MigrationList.clear();
	}

	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			if (theGrid[i * yNumOfGrid + j].GetObjectCount() > 0)
				theGrid[i * yNumOfGrid + j].CheckForCollision();
		}
	}

}

/********************************************************************************
Render the spatial partition
********************************************************************************/
void CSpatialPartition::Render(Vector3* theCameraPosition)
{
	if (showGrid)
	{
		// Render the Spatial Partitions
		MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
		for (int i = 0; i < xNumOfGrid; i++)
		{
			for (int j = 0; j < yNumOfGrid; j++)
			{
				modelStack.PushMatrix();
				modelStack.Translate(xGridSize * i - (xSize >> 1), yGridSize * j - (ySize >> 1), 1.f);
				modelStack.Scale(xGridSize, yGridSize, 1.f);
				modelStack.Translate(0.5f, 0.5f, 0.f);
				theGrid[i * yNumOfGrid + j].Render();
				modelStack.PopMatrix();
			}
		}
	}
}

/********************************************************************************
 Get xSize of the entire spatial partition
********************************************************************************/
int CSpatialPartition::GetxSize(void) const
{
	return xSize;
}
/********************************************************************************
 Get zSize of the entire spatial partition
********************************************************************************/
int CSpatialPartition::GetySize(void) const
{
	return ySize;
}
/********************************************************************************
 Get xSize
********************************************************************************/
int CSpatialPartition::GetxGridSize(void) const
{
	return xGridSize;
}
/********************************************************************************
 Get zNumOfGrid
********************************************************************************/
int CSpatialPartition::GetyGridSize(void) const
{
	return yGridSize;
}
/********************************************************************************
Get xNumOfGrid
********************************************************************************/
int CSpatialPartition::GetxNumOfGrid(void) const
{
	return xNumOfGrid;
}
/********************************************************************************
Get zNumOfGrid
********************************************************************************/
int CSpatialPartition::GetyNumOfGrid(void) const
{
	return yNumOfGrid;
}

/********************************************************************************
 Get a particular grid
 ********************************************************************************/
CGrid* CSpatialPartition::GetGrid(const int xIndex, const int yIndex) const
{
	if (xIndex < 0 || xIndex > xNumOfGrid || yIndex < 0 || yIndex > yNumOfGrid)
		return nullptr;

	return &theGrid[ xIndex * yNumOfGrid + yIndex ];
}

// Get grid of where object resides in
CGrid* CSpatialPartition::GetGrid(EntityBase* object)
{
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			if (theGrid[i * yNumOfGrid + j].IsHere(object))
			{
				return &theGrid[i * yNumOfGrid + j];
			}
		}

	}
}

// Get grid from position
CGrid* CSpatialPartition::GetGrid(Vector3& position) const
{
	int xIndex = (((int)position.x - (-xSize >> 1)) / xGridSize);
	int yIndex = (((int)position.y - (-ySize >> 1)) / yGridSize);

	if (xIndex < 0 || xIndex > xNumOfGrid || yIndex < 0 || yIndex > yNumOfGrid)
		return nullptr;

	return &theGrid[xIndex * yNumOfGrid + yIndex];
}

/********************************************************************************
 Get vector of objects from this Spatial Partition
 ********************************************************************************/
vector<EntityBase*> *CSpatialPartition::GetObjects(Vector3 position, const float radius)
{
	// Get the indices of the object's position
	int xIndex = (((int)position.x - (-xSize >> 1)) / (xSize / xNumOfGrid));
	int yIndex = (((int)position.y - (-ySize >> 1)) / (ySize / yNumOfGrid));

	return theGrid[xIndex*yNumOfGrid + yIndex].GetListOfObject();
}

/********************************************************************************
 Add a new object model
 ********************************************************************************/
void CSpatialPartition::Add(EntityBase* theObject)
{
	// Check if the entity has a collider
	if (theObject->HasCollider())
	{
		Vector3 topRight = theObject->GetCollider()->GetMax();
		Vector3 bottomLeft = theObject->GetCollider()->GetMin();
		Vector3 topLeft, bottomRight;
		topLeft.Set(bottomLeft.x, topRight.y, 0.f);
		bottomRight.Set(topRight.x, bottomLeft.y, 0.f);

		topRight.x = (int)(topRight.x - (-xSize >> 1)) / xGridSize;
		topRight.y = (int)(topRight.y - (-ySize >> 1)) / yGridSize;

		topLeft.x = (int)(topLeft.x - (-xSize >> 1)) / xGridSize;
		topLeft.y = (int)(topLeft.y - (-ySize >> 1)) / yGridSize;

		bottomRight.x = (int)(bottomRight.x - (-xSize >> 1)) / xGridSize;
		bottomRight.y = (int)(bottomRight.y - (-ySize >> 1)) / yGridSize;

		bottomLeft.x = (int)(bottomLeft.x - (-xSize >> 1)) / xGridSize;
		bottomLeft.y = (int)(bottomLeft.y - (-ySize >> 1)) / yGridSize;

		if (((topLeft.x >= 0) && (topLeft.x < xNumOfGrid)) &&
			((topLeft.y >= 0) && (topLeft.y < yNumOfGrid)))
			theGrid[(int)topLeft.x *  yNumOfGrid + (int)topLeft.y].Add(theObject);

		if (((topRight.x >= 0) && (topRight.x < xNumOfGrid)) &&
			((topRight.y >= 0) && (topRight.y < yNumOfGrid)))
			theGrid[(int)topRight.x *  yNumOfGrid + (int)topRight.y].Add(theObject);

		if (((bottomLeft.x >= 0) && (bottomLeft.x < xNumOfGrid)) &&
			((bottomLeft.y >= 0) && (bottomLeft.y < yNumOfGrid)))
			theGrid[(int)bottomLeft.x *  yNumOfGrid + (int)bottomLeft.y].Add(theObject);

		if (((bottomRight.x >= 0) && (bottomRight.x < xNumOfGrid)) &&
			((bottomRight.y >= 0) && (bottomRight.y < yNumOfGrid)))
			theGrid[(int)bottomRight.x *  yNumOfGrid + (int)bottomRight.y].Add(theObject);
	}
	else
	{
		int xIndex = (int)(theObject->GetPosition().x - (-xSize >> 1)) / xGridSize;
		int yIndex = (int)(theObject->GetPosition().y - (-ySize >> 1)) / yGridSize;

		// Add them to each grid
		if (((xIndex >= 0) && (xIndex < xNumOfGrid)) && ((yIndex >= 0) && (yIndex < yNumOfGrid)))
		{
			theGrid[xIndex * yNumOfGrid + yIndex].Add(theObject);
		}
	}
}

// Remove but not delete object from this grid
void CSpatialPartition::Remove(EntityBase* theObject)
{
	// Get the indices of the object's position
	int xIndex = (((int)theObject->GetPosition().x - (-xSize >> 1)) / (xSize / xNumOfGrid));
	int yIndex = (((int)theObject->GetPosition().y - (-ySize >> 1)) / (ySize / yNumOfGrid));

	// Add them to each grid
	if (((xIndex >= 0) && (xIndex < xNumOfGrid)) && ((yIndex >= 0) && (yIndex<yNumOfGrid)))
	{
		theGrid[xIndex * yNumOfGrid + yIndex].Remove(theObject);
	}
}

/********************************************************************************
 PrintSelf
 ********************************************************************************/
void CSpatialPartition::PrintSelf() const
{
	cout << "******* Start of CSpatialPartition::PrintSelf() **********************************" << endl;
	cout << "xSize\t:\t" << xSize << "\tzSize\t:\t" << ySize << endl;
	cout << "xNumOfGrid\t:\t" << xNumOfGrid << "\tzNumOfGrid\t:\t" << yNumOfGrid << endl;
	if (theGrid)
	{
		cout << "theGrid : OK" << endl;
		cout << "Printing out theGrid below: " << endl;
		for (int i = 0; i < xNumOfGrid; i++)
		{
			for (int j = 0; j < yNumOfGrid; j++)
			{
				theGrid[ i* yNumOfGrid + j ].PrintSelf();
			}
		}
	}
	else
		cout << "theGrid : NULL" << endl;
	cout << "******* End of CSpatialPartition::PrintSelf() **********************************" << endl;
}