/* 
 * @author Max Rafiandy
 * Create Date: Jun, 28 2016
 * Version 1.0
 */

#ifndef BRON_KERBOSCH_H
#define BRON_KERBOSCH_H

#include <vector>
#include <fstream>
#include <stdlib.h>

class Bron_kerbosch
{
public:
    Bron_kerbosch(std::vector<int> *graph);
    Bron_kerbosch(std::vector<int> *graph, bool print_screen);
    int execute(std::vector<int> r, std::vector<int> p, std::vector<int> x);

private:
    std::vector<int> neightbour(int vertex, std::vector<int> p);
    void bron_kerbosch(std::vector<int> r, std::vector<int> p, std::vector<int> x);
    std::ofstream out_file;
    std::vector<int> *graph;
    bool print_screen;
};

#endif // BRON_KERBOSCH_H
