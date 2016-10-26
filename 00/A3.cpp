// inspiration for the Linked List: http://pumpkinprogrammer.com/2014/06/13/c-tutorial-intro-to-linked-lists/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int available_id;

struct Mesh
{
	int id;	int num_vertices; std::vector<float> center_position; int num_faces; string name; int scale;
  	Mesh * next;

	Mesh()
	{
		id = available_id;
		available_id ++;
	}
	Mesh(int idd, int num_vertices, vector<float> center_position, int num_faces, string name, int scale)
	{
		id = idd;
		num_vertices = num_vertices;
		center_position = center_position;
		num_faces = num_faces;
		name = name;
		scale = scale;
	}
};

class SceneManager
{
private:
    // Head of the list contains no mesh object, 
    // but points to the object playlist.
    Mesh * head;
    int listLength;
    
public:
    // Default Constructor creates the head Mesh.
    SceneManager()
    {
		head -> id = 0;
		head -> num_vertices = 0;
		head -> center_position = {0,0};
		head -> num_faces = 0;
		head -> name = "the head has no name";
		head -> scale = 0;
		head -> next = NULL;
		listLength = 0;
    }
    
    // Setter adds a Mesh to the list at a given position.
    // Takes a Mesh and list position as parameters.
    // Position must be between 1 and the number of data Meshs.
    // Returns true if the operation is successful.
    bool insertMesh( Mesh * newMesh, int position )
    {
	    if ((position <= 0) || (position > listLength + 1))
	    {
	        cout << "nError: the given position is out of range.n";
	        return false;
	    }
	    if (head -> next == NULL) 
	    {
	        head -> next = newMesh;
	        listLength++;
	        return true;
	    } 
	    int count = 0;
	    Mesh * p = head;
	    Mesh * q = head;
	    while (q)
	    { 
	        if (count == position)
	        {
	            p -> next = newMesh;
	            newMesh -> next = q;
	            listLength++;
	            return true;
	        }
	        p = q;
	        q = p -> next;
	        count++;
	    }
	    if (count == position)
	    {
	        p -> next = newMesh;
	        newMesh -> next = q;
	        listLength++;
	        return true;
	    }
	    cout << "nError: Mesh was not added to list.n";
	    return false;
    }

    
    // Setter removes a Mesh by its given position.
    // Returns true if the operation is successful.
    bool removeMesh( int position )
    {
    	if ((position <= 0) || (position > listLength + 1))
	    {
	        cout << "nError: the given position is out of range.n";
	        return false;
	    }
	    if (head -> next == NULL)
	    {
	       cout << "nError: there is nothing to remove.n";
	       return false;
	    }
	    int count = 0;
	    Mesh * p = head;
	    Mesh * q = head;
	    while (q) 
	    {
	        if (count == position)
	        {
	            p -> next = q -> next;
	            delete q;
	            listLength--;
	            return true;
	        }
	        p = q;
	        q = p -> next;
	        count++;
	    }
	    cout << "nError: nothing was removed from the list.n";
	    return false;
    }

    // Prints each Mesh in the list in consecutive order,
    // starting at the head and ending at the tail.
    // Prints list data to the console.
    void printScene()
    {
    	Mesh * p = head;
	    Mesh * q = head;
	    cout << "n---------------------------n";
	    cout << "Mesh Object n";
	    int count = 0;
	    while (q)
	    {
	        p = q;
	        cout << "n-----------------------------n";
	        cout << "t position: " << count << endl;
	        cout << "t object: " << p -> name << endl;
	        q = p -> next;
	        count++;
	    }
    }
    
    // Destructor de-allocates memory used by the list.
    ~SceneManager()
    {
	    Mesh * p = head;
	    Mesh * q = head;
	    while (q)
	    {
	        p = q;
	        q = p -> next;
	        if (q) delete p;
	    }
	}
};


int main () 
{
    // STEP 1: Create some unlinked mesh objects.
    vector<float> position = {2,2};
    Mesh * A = new Mesh(2,2, position,2,"blaName",2);
    
    // Mesh * B = new Mesh;
    // B -> song = "I Stand Alone";
    // B -> artist = "Godsmack";
    
    // Mesh * C = new Mesh;
    // C -> song = "Heir Apparent";
    // C -> artist = "Opeth";
    
    // Mesh * D = new Mesh;
    // D -> song = "Fear of the Dark";
    // D -> artist = "Iron Maiden";
    
    // Mesh * E = new Mesh;
    // E -> song = "Blue Monday";
    // E -> artist = "New Order";
    
    // Mesh * F = new Mesh;
    // F -> song = "The Moth";
    // F -> artist = "Aimee Mann";
    
    // STEP 2: Build a list of three song Meshs by appending to end of list.
    SceneManager myList;
    myList.insertMesh(A, 1);
    // myList.insertMesh(B, 2);
    // myList.insertMesh(C, 3);
    // myList.insertMesh(D, 4);
    myList.printScene();
    
    // // STEP 3: Insert a Mesh into middle of list.
    // myList.insertMesh(E, 2);
    // myList.printScene();
    
    // // STEP 4: Insert Mesh at the front of list.
    // myList.insertMesh(F,1);
    // myList.printScene();
    
    // // STEP 5: Remove the last Mesh from the list.
    // myList.removeMesh(6);
    // myList.printScene();
    
    // // STEP 6: Remove the first Mesh from the list.
    // myList.removeMesh(1);
    // myList.printScene();
    
    // // STEP 7: Remove a Mesh from the middle of the list.
    // myList.removeMesh(3);
    // myList.printScene();
    
    return 0;
}