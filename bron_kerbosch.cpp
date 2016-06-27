#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>

#define DEFAULT_VERTEX 60

static int NUM_VERTEX;
static char FILE_NAME[256];
std::vector<int> graph,*g;

void bron_kerbosch(std::vector<int> r, std::vector<int> p, std::vector<int> x);
std::vector<int> neightbour(int vertex, std::vector<int> p);

std::ofstream out_file;
std::ifstream in_file;

int main(int argc, char** argv)
{
    std::vector<int> r,p,x;
    
    NUM_VERTEX = DEFAULT_VERTEX;
    strcpy(FILE_NAME,"bron_kerbosch.csv");
        
    int opt;
    while ((opt = getopt(argc, argv, "s:f:")) != -1)
    {
        switch (opt)
        {
        case 's':
            NUM_VERTEX = atoi(optarg);
            break;
        case 'f':
            strcpy(FILE_NAME,optarg);
            break;
        }
    }
    
    in_file.open(FILE_NAME,std::ios_base::in);
    out_file.open("clique.txt",std::ios_base::out);

    g = (std::vector<int>*) malloc(sizeof(std::vector<int>)*NUM_VERTEX);

    std::string value;

    int id=0, it=0;
    while (in_file)
    {
         std::getline (in_file, value, ',');
         const char *c = std::string(value, 0, value.length()).c_str();

         if(*c == '1') g[id].push_back(it++);
         else if(*c == '0') it++;

         if(it == NUM_VERTEX)
         {
             it = 0;
             id++;
         }
    }
    in_file.close();

    for(int i=0; i<NUM_VERTEX; i++)
    {
        p.push_back(i);
    }

    omp_set_dynamic(0);
    omp_set_nested(1);
    omp_set_num_threads(2);

    #pragma omp parallel shared(r,p,x)
    {
        #pragma omp single
        bron_kerbosch(r,p,x);
    }

    out_file.close();
}

std::vector<int> neightbour(int vertex, std::vector<int> p)
{
    std::vector<int> n;
    std::sort (g[vertex].begin(), g[vertex].end());

	int psize = p.size();
		
    for(int i=0; i<psize; i++)
    {
        int v = p[i];
        if (std::binary_search (g[vertex].begin(), g[vertex].end(), v))
        {
            
            n.push_back(v);
        }
    }
    return n;
}

void bron_kerbosch(std::vector<int> r, std::vector<int> p, std::vector<int> x)
{
    int psize = p.size();

    if(!psize && !x.size())
    {
        #pragma omp task firstprivate(r)
        {
            out_file << "clique: [";
            int rsize = r.size();
            for(int i=0; i<rsize; i++)
            {
                out_file << r[i];
                if(i != rsize-1)
                {
                    out_file << ",";
                }
            }
            out_file << "]" << std::endl;
        }
        return;
    }

    for(int i=0; i<psize; i++)
    {
        int vertex = p[0];
        std::vector<int> new_r = r, new_p, new_x;
        new_r.push_back(vertex);
        
        #pragma omp task shared(new_p) firstprivate(p,vertex)
        new_p = neightbour(vertex,p);
        #pragma omp task shared(new_x) firstprivate(x,vertex)
        new_x = neightbour(vertex,x);
        #pragma omp taskwait
        bron_kerbosch(new_r,new_p,new_x);
        if(p.size()) p.erase(p.begin());
        x.push_back(vertex);
    }
    return;
}
