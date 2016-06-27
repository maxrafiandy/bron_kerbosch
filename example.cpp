/* 
 * @author Max Rafiandy
 * Create Date: Jun, 28 2016
 * Version 1.0
 */

#include <vector>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include "bron_kerbosch.h"

#define DEFAULT_VERTEX 60

static int NUM_VERTEX;
static char FILE_NAME[256];

std::ifstream in_file;

int main(int argc, char** argv)
{
    std::vector<int> r,p,x,*g;
    
    NUM_VERTEX = DEFAULT_VERTEX;
    strcpy(FILE_NAME,"graph.csv");
    
    int opt;
    /* 
     * v: set number of vertex
     * f: graph representation in csv file
     */
    while ((opt = getopt(argc, argv, "v:f:")) != -1)
    {
        switch (opt)
        {
        case 'v':
        	// set number of vertex
            NUM_VERTEX = atoi(optarg);
            break;
        case 'f':
        	// set input file
            strcpy(FILE_NAME,optarg);
            break;
        }
    }
    // load input file and allocating graph into memory
    in_file.open(FILE_NAME,std::ios_base::in);    
    g = (std::vector<int>*) malloc(sizeof(std::vector<int>)*NUM_VERTEX);
           
    /*
	* In order to use this example, you must write a .csv 
	* file as a graph representation. Wrire down your graph as 
	* 1D vector/array. Example: if your graph representation
	* in 2D matrix is [[0,1,1],[1,0,1],[1,1,0]], it should written
	* as 0,1,1,1,0,1,1,1,0 in your .csv file. 
	*/
	
	std::string value;
    int id=0, it=0;
    while (in_file)
    {
         /*
          * everytime the program hit comma ','
          * load its value
          */
         std::getline (in_file, value, ',');
         const char *c = std::string(value, 0, value.length()).c_str();
         
         /* 
          * if c equals to 1 than, the vertex index of "id"
          * linked to vertex index of "it" 
          */
         if(*c == '1') g[id].push_back(it++);
         else if(*c == '0') it++;

         if(it == NUM_VERTEX)
         {
             it = 0;
             id++;
         }
    }
    
    in_file.close();

	/* init vertexes from 0 to NUM_VERTEX */
    for(int i=0; i<NUM_VERTEX; i++)
    {
        p.push_back(i);
    }
    
    /* create object of Bron_kerbosch
     * the first argument is the graph object.
     * the second just an optional parameter.
     * if you want to print the result into 
     * a text file instead of to screen, pass
     * true as a second argument.
     */ 
    Bron_kerbosch bk(g);
    
    /* execute the bron_kerbosch and exit 
     * and close the program
     */
    
    return bk.execute(r,p,x);
}
