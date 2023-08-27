#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int NO_PARENT = -1,p[9];
 //array of regions in Ukarine(as ASSUMED)
const char* region[9]= { "Kyiv", "Dnipro", "Sumy", "Lyman","Donbas", "Izyum", "Irpin",
"Lviv","Odesa" };
void printPath(int currentVertex, vector<int> parents) //for printing the path as given by dijkstra's algorithm
{
if (currentVertex == NO_PARENT) {
return;
}
printPath(parents[currentVertex], parents); //function recursively calling itself
cout << region[currentVertex] << " ";
}
void printSolution(int startVertex, vector<int> distances,vector<int> parents,int n) //printing Vertex,time & path
{
int nVertices = distances.size();
cout << "\n" << region[startVertex] << " -> ";
cout << region[n] << " \t\t\t\t\t\t ";
cout << distances[n] << "\t\t\t\t\t\t";
printPath(n, parents); //calling printPath() function
}
void dijkstra(vector<vector<int> > adjacencyMatrix, //code for dijkstra's algorithm
              int startVertex)
{
int nVertices = adjacencyMatrix[0].size();
vector<int> shortestDistances(nVertices);
vector<bool> added(nVertices);
for (int vertexIndex = 0; vertexIndex < nVertices;
vertexIndex++) {
shortestDistances[vertexIndex] = INT_MAX;
added[vertexIndex] = false;
}
shortestDistances[startVertex] = 0;
vector<int> parents(nVertices);
parents[startVertex] = NO_PARENT;
for (int i = 1; i < nVertices; i++) {
int nearestVertex = -1;
int shortestDistance = INT_MAX;
for (int vertexIndex = 0; vertexIndex < nVertices;
vertexIndex++) {
if (!added[vertexIndex]
&& shortestDistances[vertexIndex]
< shortestDistance) {
nearestVertex = vertexIndex;
shortestDistance
= shortestDistances[vertexIndex];
}
}
added[nearestVertex] = true;
for (int vertexIndex = 0; vertexIndex < nVertices;
vertexIndex++) {
int edgeDistance
= adjacencyMatrix[nearestVertex]
[vertexIndex];
if (edgeDistance > 0
&& ((shortestDistance + edgeDistance)
< shortestDistances[vertexIndex])) {
parents[vertexIndex] = nearestVertex;
shortestDistances[vertexIndex]
= shortestDistance + edgeDistance;
}
}
}
 int f=0;
 p[0]=0; //array to check if the region is danger area or not,intially set first element as 0
 for(int i=1;i<9;i++) //running loop 9 times(9 locations)and taking input details of each region
 {
 cout<<endl<<"Is "<<region[i]<<" in danger?"<<endl<<"Press 1 for yes and 0 for no.";
 cin>>p[i];
 if(p[i]!=0 && p[i]!=1)
 {
 cout<<"Wrong input"<<endl; //for all input expect 0,1 program will show wrong input
 return;
 }
 }
 cout << "Vertex\t\t\t\t\t\tTime\t\t\t\t\t\tPath"; //printing vertex,time and path
 for(int i=1;i<9;i++)
 {
 if(p[i]==1)
 {
 f=1;
 printSolution(startVertex, shortestDistances, parents,i); //function calling printSolution();
 }
 }
 if(f==0) //if there is no danger area,medical supply is not needed at that area,hence none will be printed in each case
 cout<<endl << "None\t\t\t\t\t\tNone\t\t\t\t\t\tNone"<<endl<<endl<<"No area is in danger";
}
int max(int a, int b) { return (a > b) ? a : b; }
void printknapSack(int W, int wt[], int val[], int n)
// W(weight of bag) ----- Net soldiers present at bootcamp
// wt( array of weight of each item) ---- array of more soldiers reqd inorder to win the battle
// val(array of cost of each product) ---- array of winning chances at each danger area
// n(no. of objects) ---- no. of wars that could be won
{
 int i, w;
 int K[n + 1][W + 1];
 for (i = 0; i <= n; i++)
 {
 for (w = 0; w <= W; w++)
 {
 if (i == 0 || w == 0)
 K[i][w] = 0;
 else if (wt[i - 1] <= w)
 K[i][w] = max(val[i - 1] +
 K[i - 1][w - wt[i - 1]], K[i - 1][w]);
 else
 K[i][w] = K[i - 1][w];
 }
 }
 int res = K[n][W];
 int x=0;
 w = W;
 for (i = n; i > 0 && res > 0; i--) {
 if (res == K[i - 1][w])
 continue;
 else {
 cout<<wt[i - 1] <<" soldiers to be deployed to "<<region[i-1]<<endl;
 x++;
 res = res - val[i - 1];
 w = w - wt[i - 1];
 }
 }
 if(x==0)
 cout<<"";
}

int main()
{
 label: //indicate locations in the code
 vector<vector<int>> adjacencyMatrix //declaring a matrix
= { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
{ 0, 0, 4, 0, 10, 0, 2, 0, 0 },
{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
 int n;
 cout<<endl<<endl<<"WHICH COMMAND TO ENTER"<<endl;
 cout<<"ENTER 1 FOR ROUTE OF MEDICAL SUPPLIES"<<endl;
 cout<<"ENTER 2 FOR TROOP ALLOCATION"<<endl;
 cout<<"ENTER 3 TO KNOW ABOUT THE PROGRAM"<<endl;
 cout<<"ENTER 4 TO EXIT"<<endl;
 cin>>n;
 switch (n) //applying switch-cases as per user's choice
 {
 case 1:
 {
 system("cls"); //used to clear the console screen like clrscr()
 //colour.
 dijkstra(adjacencyMatrix, 0); //calling dijkstra functn and setting source as 0
 break; //using break statement so that no further case could execute
 }
 case 2:
 {
 system("cls"); //used to clear the console screen like clrscr()
 int f=0;
 p[0]=0; //array to check if the region is danger area or not,intially set first element as 0
 for(int i=1;i<9;i++) //running loop 9 times(9 locations)and taking input details of each region
 {
 cout<<endl<<"Is "<<region[i]<<" in danger?"<<endl<<"Press 1 for yes and 0 for no.";
 cin>>p[i];
 if(p[i]!=0 && p[i]!=1)
 {
 cout<<"Wrong input"<<endl; //for all input expect 0,1 program will show wrong input
 return 0;
 }
 }
 cout<<endl<<endl<<"Number of soldiers in Reserves present at the Basecamp (Kyiv)"<<endl;
 int W;
 cin>>W; //taking input number of soldiers at bootcamp(reserved soldiers)
 int s_our, s_opp,cas,ras,dist, wt[9],val[9];
 /*
 s_our: num of soldiers in our army
 s_opp: num of soldiers in opp army
 cas: num of casulaities in war
 ras: num of bullets/bombs
 dist: distance of region from bootcamp
 wt[]: array of more soldiers reqd inorder to win the battle
 val[]: array of winning chances
 */
 for (int i=1;i<9;i++)
 {
 if(p[i]==1)
 {
 cout<<"* Enter details for location "<<region[i]<<" *"<<endl<<endl;
 cout<<"Enter head count of soldiers that are fit to fight in your army :";
 cin>>s_our;
 cout<<"Enter approximation of resistance faced in :"<<region[i];
 cin>>s_opp;
 cout<<"Enter number of casualties :";
 cin>>cas;
 cout<<"Enter ammount of ammunition left in quintals :";
 cin>>ras;
 cout<<"Enter distance of "<<region[i]<<" from base camp in kms :";
 cin>>dist;
 cout<<endl<<endl;
 wt[i]=(3*s_opp)-s_our;
 val[i]=(100*s_our*ras)/(s_opp*cas*dist); //formula for calculation of winning chance
 f=1;
 }
 else val[i]=-1;
 }
 if(f==1)
 {
 int a = sizeof(val) / sizeof(val[0]);
 printknapSack(W, wt, val, a);
 }
 else cout<<endl<<"NO AREA IS IN DANGER"<<endl<<endl;
 break;
 }
 case 3:
 {
 cout<<"";
 break;
 }
 case 4:
 {
 cout<<"THANK YOU.";
 return 0;
 }
 default:
 {
 cout<<"Wrong Input";
 }
 }
 goto label; //unconditional jump to a labeled statement
 return 0;
}
