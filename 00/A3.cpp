// inspiration for the Linked List: http://pumpkinprogrammer.com/2014/06/13/c-tutorial-intro-to-linked-lists/

// compiled with g++ -std=c++11

/*
1. The data structure is a linked list `Scene Manager` that has `Mesh` objects as nodes as seen in the implementation below.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

int available_id = 1;

class Mesh
{   
public:
    int id;
    int num_vertices;
    std::vector<float> center_position;
    int num_faces;
    string name;
    int scale;
    Mesh * next;

    // constructor that assigns automatically an id
    Mesh(int num_vertice, vector<float> center_positio, int num_face, string nam, int scal)
    {   
        id = available_id;
        available_id ++;
        num_vertices = num_vertice;
        center_position = center_positio;
        num_faces = num_face;
        name = nam;
        scale = scal;
        next = NULL;
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
        vector<float> null;
        null = {0,0};
        head = new Mesh(0, null, 0, "a Head has no name", 0);
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
        int count = 001;
        while (q)
        {
            p = q;
            cout << "n-----------------------------n" << endl;
            cout << "t id: " << count << ", object name: <<" << p -> name
                 << ">>, number faces: " << p -> num_faces << ", number vertices: " << p->num_vertices 
                 << ", scale :" << p->scale << endl;
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
    SceneManager myList;
    vector<float> pos = {2,2};
    Mesh * A = new Mesh(2, pos, 2, "Hans", 2);
    myList.insertMesh(A, 1);

    int action;
    cout << "What do you want to do?" << endl;
    cout << "for adding mesh object, type 1" << endl;
    cout << "for removing mesh object, type 2" << endl;
    cout << "for listing objects, type 3" << endl;
    cout << "for exiting the program, type 0" << endl;

    cin >> action;

    while (action != 0)
    {
        if (action == 1)
        {
            int num_vert;
            float x; float y;
            int num_faces;
            string name;
            int scale;

            // STEP 2: Create a mesh object based on user input:
            cout << "Please provide the information for creating a new mesh object:"<<endl;
            cout << "Number of vertices: "; cin >> num_vert;
            cout << "Vector position of center (x, y): "; cin >> x >> y;
            vector<float> position = {x, y};
            cout << "Number of faces: "; cin >> num_faces;
            cout << "Name: "; cin >> name;
            cout << "Scaling properties: "; cin >> scale;

            Mesh * user = new Mesh(num_vert, position, num_faces, name, scale);

            // add the mesh object on position one in the list
            myList.insertMesh(user, 2);
        }
        else
        {
            if (action == 2)
            {   
                int id;
                cout << "Please input the id of the object you want to delete:"; cin >> id;
                myList.removeMesh(id);
            }
            else
            {
                if (action == 3)
                {
                    myList.printScene();
                }

            }
        }
        cout << "What do you want to do next?" << endl;
        cin >> action;
    }    
    return 0;
}