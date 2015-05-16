#include <iostream>
#include "KdTree.hpp"

using namespace Kd;

int main(void)
{
    KdTree<double> *tree = new KdTree<double>(6, 2);


    std::vector<double> x(2);

    x[0] = 1.0;
    x[1] = 1.0;
    tree->insert(x);

    x[0] = 1.0;
    x[1] = -1.0;
    tree->insert(x);

    x[0] = -1.0;
    x[1] = 1.0;
    tree->insert(x);

    x[0] = -1.0;
    x[1] = -1.0;
    tree->insert(x);

    x[0] = 2.0;
    x[1] = 2.0;
    tree->insert(x);

    x[0] = 3.0;
    x[1] = 3.0;
    tree->insert(x);


    std::cout << "****************TREE****************" << std::endl;
    tree->print();
    std::cout << "************************************" << std::endl;

    x[0] = 2.2;
    x[1] = 2.3;

    KdNode<double> *n = tree->findNearest(x);

    std::cout << n->data()[0] << " " << n->data()[1] << std::endl;

    x[0] = 2.2;
    x[1] = 2.2;

    std::vector< std::vector<double> > nn = tree->findNearestInRange(x, 5.);

    for(int i = 0; i < nn.size(); ++i)
    {
        std::cout << nn[i][0] << " " << nn[i][1] << std::endl;
    }
}
