// --------------------------------------------------------------------------------------

// Subject		: Computer Graphics
// Project		: Sheet 1 : Exercise 3 Scene Manager Class
// Authors		: Lina Ouro,  Letitia Parcalabescu, Anushalakshmi Manila
// Date		: Oct  26, 2016
// Description	: Compute the area and circumference of a circle with given radius

// --------------------------------------------------------------------------------------

// inspiration for the Linked List: http://pumpkinprogrammer.com/2014/06/13/c-tutorial-intro-to-linked-lists/
// compiled with g++ -std=c++11 -Wno-narrowing 

/*
1. The data structure is a linked list `Scene Manager` that has `Mesh` objects as nodes as seen in the implementation below.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
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
    
public:
    int listLength;
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
                available_id --;
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
    void printScene( bool toFile)
    {   
        if (toFile == 1)
        {
            ofstream myfile;
            myfile.open ("objects.txt");

            Mesh * p = head;
            Mesh * q = head;
            int count = 0;
            while (q)
            {   
                if ( q!= head)
                {
                    p = q;
                    myfile << "object name: " << p -> name << endl;
                    myfile << "number vertices: " << p->num_vertices << endl;
                    myfile << "vector position center x: " << p-> center_position[0] << endl;
                    myfile << "vector position center y: " << p-> center_position[1] << endl;
                    myfile << "number faces: " << p -> num_faces << endl;
                    myfile << "scale : " << p->scale << endl;
                    myfile << "   " << endl;
                    count++;
                }
                else
                    cout << "There are no objects to be printed." << endl;
                q = p -> next;
            }
            
            myfile.close();
        }
        else
        {
            Mesh * p = head;
            Mesh * q = head;
            cout << "n---------------------------n";
            cout << "Mesh Object n";
            int count = 1;
            while (q)
            {   
                if (q != head)
                {
                    p = q;
                    cout << "n-----------------------------n" << endl;
                    cout << "t id: " << count << ", object name: <<" << p -> name
                         << ">>, number faces: " << p -> num_faces << ", number vertices: " << p->num_vertices 
                         << ", scale :" << p->scale << endl;
                    q = p -> next;
                    count++;
                }
                else
                    cout <<"There are no objects to be printed." << endl;
                q = p -> next;

            }
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

    int num_vert;
    float x; float y;
    int num_faces;
    string name;
    int scale;

    string line;
    ifstream myfile ("objects.txt");
    int line_count = 1;
    if (myfile.is_open())
        {   
            cout << "Reading data from file ..." <<endl;
            while ( getline (myfile,line) )
            {   
                if (line_count % 7 == 1)
                    name = line.substr(line.find(":") + 1); ;
                if (line_count % 7 == 2)
                    num_vert = line.back();
                if (line_count % 7 == 3)
                    x = line.back();
                if (line_count % 7 == 4)
                    y = line.back();
                if (line_count % 7 == 5)
                    num_faces = line.back();
                if (line_count % 7 == 6)
                    scale = line.back();
                if (line_count % 7 == 0)
                {   
                    cout << "Inserting object from database..." <<endl;
                    vector<float> position = {x, y};
                    Mesh * user = new Mesh(num_vert, position, num_faces, name, scale);
                    myList.insertMesh(user, myList.listLength+1);
                }
                line_count++;
            }
          myfile.close();
        }

      else cout << "Unable to open file"; 

    // manually introduce an object here. For debugging purposes.
    vector<float> pos = {rand(), rand()};
    Mesh * A = new Mesh(rand(), pos, rand(), "Hans", rand());
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
            myList.insertMesh(user, myList.listLength+1);
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
                    myList.printScene(0);
                }
            }
        }
        cout << "What do you want to do next?" << endl;
        cin >> action;
    }

    // STEP 3. Store current objects in a text file
    if (action == 0)
    {
        myList.printScene(1);
    }

    return 0;
}