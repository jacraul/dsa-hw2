#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

//a) (1p) Find a suitable representation for a Quad tree.
struct Node
{
    int level;
    char info;
    Node *left, *mid_left, *mid_right, *right;

    Node(char c)
    {
        info = c;
        left=mid_left=mid_right=right=NULL;
    }
};
//b) (1p) Write a function which transforms the preorder traversal you give as an input into the representation you have chosen for Quad trees.representation you have chosen for Quad trees.
Node* Tree(string preorder, int &i)
{
    if(i>=preorder.length()) //if i the counter is more than the length of the string or equal (i starts from 0), we will return NULL
        return NULL;
    char c = preorder[i]; //memorise the letter on position i from string
    i++; //increase the position
    Node* node = new Node(c); //adding the c as node
    if(c=='p') // if c is a parent we attribute to it the left, mid left, mid right, right elements
    {
        node->left=Tree(preorder,i);
        node->mid_left=Tree(preorder,i);
        node->mid_right=Tree(preorder,i);
        node->right=Tree(preorder,i);
        return node; // we return the current node
    }
    return new Node(c); //If the current character "c" is not a parent ('p'), it means that it is a leaf node, so we simply create a new node with "c" as its value and return it.
};
//c) (1.5p) Write a function which receives as arguments two Quad trees and transforms them into another Quad tree, for the final image, based on the algorithm described in the problem.

Node* unify(Node* q1, Node* q2) {
    if (!q1 && !q2) { // if q1 and q2 are both NULL, return NULL
        return NULL;
    }
    if (!q1) {
        return q2;
    }
    if (!q2) {
        return q1;
    }

    Node* node = new Node('p');
    if (q1->info == 'b' || q2->info == 'b') { //check if one of the nodes is black, then it will be black
        node->info = 'b';
        node->left = node->mid_left = node->mid_right = node->right = NULL;
    } else if (q1->info == 'w' && q2->info == 'w') {  //check if they are both white
        node->info = 'w';
        node->left = node->mid_left = node->mid_right = node->right = NULL;
    } else { //we are calling recursively the function
        node->left = unify(q1->left, q2->left);
        node->mid_left = unify(q1->mid_left, q2->mid_left);
        node->mid_right = unify(q1->mid_right, q2->mid_right);
        node->right = unify(q1->right, q2->right);
    }
    return node; // return the new parent node
}


//d) (1p) Write a function which calculates the pixels for a given Quad tree representing an image.


int blackPixels(Node* tree, int level)
{
    int bP=0;
    if(!tree) // Check if the current node is NULL
        return 0;
    if(tree->info == 'b' && level==1) //Check if the current node is a black pixel at the first level and if it is we are adding 4 to pixels because its on the 1st level and he cannot have childrens
        bP=bP+4;
    else if (tree->info == 'b')
        bP++;
    int sum = bP*64; //64 is obtained by dividing 1024 to 16 cells
    sum += blackPixels(tree->left, level+1); //we are calculating recursively the blackpixels
    sum += blackPixels(tree->mid_left, level+1);
    sum += blackPixels(tree->mid_right, level+1);
    sum += blackPixels(tree->right, level+1);
    return sum;
}



//display by levels

void displaySimple(Node* node)
{
    if(node == NULL)
        return;

    cout<<node->info<<" ";
    displaySimple(node->left);
    displaySimple(node->mid_left);
    displaySimple(node->mid_right);
    displaySimple(node->right);
}

void display(Node* node, int level)
{
    if(node == NULL)
        return;
    for(int i=0; i<level; i++)
        cout<<"-";
    cout<<node->info<<endl;
    display(node->left,level+1);
    display(node->mid_left,level+1);
    display(node->mid_right,level+1);
    display(node->right,level+1);
}

int main()
{

    int i,option;
    string preorder1,preorder2;
    Node* q1 = nullptr;
    Node* q2 = nullptr;
    Node* unifyTree = nullptr;

/*
    String1: ppwwwbpbbwwbw
    String2: pwbwpwwbw
    Output: ppwwwbbbpwwbw
*/

//e) (1p) Test your program with various inputs. Display the final Quad tree representation and the number of pixels.
//f) (0.5) Create an interaction menu which allows the user to test the above functionalities (a-e)

    do{
        cout<<endl<<endl<<"1: Add preorder1"<<endl
            <<"2: Add preorder2"<<endl
            <<"3: Show QuadTree 1 linear"<<endl
            <<"4: Show QuadTree 1 by levels"<<endl
            <<"5: Show QuadTree 2 linear"<<endl
            <<"6: Show QuadTree 2 by levels"<<endl
            <<"7: Merge the 2 trees"<<endl
            <<"8: Show merged QuadTree linear"<<endl
            <<"9: Show merged QuadTree by levels"<<endl
            <<"10: Show pixels for QuadTree 1"<<endl
            <<"11: Show pixels for QuadTree 2"<<endl
            <<"12: Show pixels for merged QuadTree"<<endl
            <<"13: Exit"<<endl<<endl
            <<"Your Option: "<<endl;
            cin >> option;
        switch(option){

            case 1:
                {
                    cout<<"Enter the string for 1st tree: ";
                    cin>>preorder1;

                    i=0;
                    q1 = Tree(preorder1,i);
                    cout<<"Added!"<<endl;
                    break;
                }
            case 2:
                {
                    cout<<"Enter the string for 2nd tree: ";
                    cin>>preorder2;

                    i=0;
                    q2 = Tree(preorder2,i);
                    cout<<"Added!"<<endl;
                    break;
                }


            case 3:
                {
                    cout<<"QuadTree 1: "; displaySimple(q1);
                    break;
                }

            case 4:
                {
                    cout<<"QuadTree 1 by levels: "<<endl; display(q1,0);
                    break;
                }

            case 5:
                {
                    cout<<"QuadTree 2: "; displaySimple(q2);
                    break;
                }

            case 6:
                {
                    cout<<"QuadTree 2 by levels: "<<endl; display(q2,0);
                    break;
                }
            case 7:
                {
                    unifyTree=unify(q1,q2);
                    cout<<"Merged!"<<endl;
                    break;
                }
            case 8:
                {
                    cout<<"Merged QuadTree: "; displaySimple(unifyTree);
                    break;
                }

            case 9:
                {
                    cout<<"Merged QuadTree by levels: "<<endl; display(unifyTree,0);
                    break;
                }
            case 10:
                {
                    cout<<"Pixels for QT 1: "<<blackPixels(q1,0)<<endl;
                    break;
                }
            case 11:
                {
                    cout<<"Pixels for QT 2: "<<blackPixels(q2,0)<<endl;
                    break;
                }
            case 12:
                {
                    cout<<"Pixels for merged QT: "<<blackPixels(unifyTree,0)<<endl;
                    break;
                }
            case 13:
                {
                    cout<<"BYE :)";
                    break;
                }
            default:
                {
                    cout<<"Invalid option!"<<endl;
                    break;
                }
        }
    }while(option!=13);
    return 0;
}
