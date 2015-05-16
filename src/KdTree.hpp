#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <math.h>
#include <map>
#include <list>

#include "KdNode.hpp"
#include "KdRes.hpp"

namespace Kd
{
    template<class T>
    class KdTree
    {
        public:
            /**
             * @brief KdTree a new object KdTree
             * @param _size size of the tree
             * @param _dim dimensions of the node
             */
            KdTree(const int &_size, const int &_dim)
                : m_size(_size), m_dim(_dim)
            {
                m_root = NULL;
                m_nodeList = 0;
                m_dir = 0;
                m_id = 1;
                m_nodelist.resize(m_size, NULL);
            }
            /**
             * @brief size return the current size of the tree
             * @return the current size of the tree
             */
            inline int size() const
            {
                return m_nodeList;
            }
            /**
             * @brief insert a new KdNode in the tree
             * @param _pos the position of the new KdNode to insert
             * @return true or false if the KdNode is correctly inserted in the tree
             */
            bool insert(const std::vector<T> &_pos)
            {
                if(m_nodeList == 0)
                {
                    m_nodelist[m_nodeList++] = new KdNode<T>(_pos, 0, m_id++);
                    return true;
                }

                int new_dir;
                
                for(nodeIt it = m_nodelist.begin(); it != m_nodelist.end(); ++it)
                {
                    new_dir = ((*it)->dir() + 1) % m_dim;
                    if(_pos[(*it)->dir()] < (*it)->data()[(*it)->dir()])
                    {
                        if((*it)->left == -1)
                        {
                            m_nodelist[m_nodeList++] = new KdNode<T>(_pos, new_dir, m_id++);
                            (*it)->left = m_nodeList - 1;
                            return true;
                        }
                        else
                        {
                            it = m_nodelist.begin() + (*it)->left - 1;
                            continue;
                        }
                    }

                    if((*it)->right == -1)
                    {
                        m_nodelist[m_nodeList++] = new KdNode<T>(_pos, new_dir, m_id++);
                        (*it)->right = m_nodeList - 1;
                        return true;
                    }
                    else
                    {
                        it = m_nodelist.begin() + (*it)->right - 1;
                        continue;
                    }

                }

                return true;
            }

            /**
             * @brief findNearest the KdNode neearest node
             * @param _pos the nearest position of the node that we are looking for
             * @return the nearest node
             */
            KdNode<T> *findNearest(const std::vector<T> &_pos)
            {
                int new_dir;
                T dist_sq, prev_dist_sq = M_PI;
                KdNode<T> *candidate;
                for(nodeIt it = m_nodelist.begin(); it != m_nodelist.end(); ++it)
                {
                    dist_sq = squareDistance(_pos, (*it)->data());
                    new_dir = ((*it)->dir() + 1) % m_dim;
                    if(_pos[(*it)->dir()] < (*it)->data()[(*it)->dir()])
                    {
                        if(prev_dist_sq == M_PI || dist_sq < prev_dist_sq)
                        {
                            prev_dist_sq = dist_sq;
                            candidate = *it;
                        }

                        if((*it)->left != -1)
                        {
                            it = m_nodelist.begin() + (*it)->left - 1;
                            continue;
                        }
                        return candidate;
                    }


                    if(prev_dist_sq == M_PI || dist_sq < prev_dist_sq)
                    {
                        prev_dist_sq = dist_sq;
                        candidate = *it;
                    }

                    if((*it)->right != -1)
                    {
                        it = m_nodelist.begin() + (*it)->right - 1;
                        continue;
                    }
                    return candidate;
                }
                return candidate;
            }
            /**
             * @brief findNearestInRange find all the nearest points in a sphere with radius _range
             * @param _pos the center of the sphere
             * @param _range the radius
             * @return a list of the nearest poinst
             */
            std::vector< std::vector<T> > findNearestInRange(const std::vector<T> &_pos, const double &_range)
            {
                std::vector< std::vector<T> > nearests;
                nodeIt it = m_nodelist.begin();
                list nodes;

                nodes.push_back(*it);

                bool back = false;
                while(nodes.size() != 0)
                {
                    KdNode<T> *node = nodes.back();

                    T dx = _pos[node->dir()] - node->data()[node->dir()];

                    if(!back)
                    {
                        if(dx <= 0.)
                        {
                            if(node->left != -1)
                            {
                                nodes.push_back(*(m_nodelist.begin() + node->left));
                            }
                            else
                            {
                                back = true;
                            }
                        }
                        else
                        {
                            if(node->right != -1)
                            {
                                nodes.push_back(*(m_nodelist.begin() + node->right));
                            }
                            else
                            {
                                back = true;
                            }
                        }
                    }
                    else
                    {
                        if(fabs(dx) < _range && dx <= 0.0)
                        {
                            T dist_sq = squareDistance(node->data(), _pos);
                            if(dist_sq <= _range * _range)
                            {
                                nearests.push_back(node->data());
                            }
                            int id = node->right;
                            nodes.pop_back();

                            if(id != -1)
                            {
                                nodes.push_back(*(m_nodelist.begin() + id));
                                back = false;
                            }
                        }
                        else if(fabs(dx) < _range && dx > 0.0)
                        {
                            T dist_sq = squareDistance(node->data(), _pos);
                            if(dist_sq <= _range * _range)
                            {
                                nearests.push_back(node->data());
                            }

                            int id = node->left;
                            nodes.pop_back();

                            if(id != -1)
                            {
                                nodes.push_back(*(m_nodelist.begin() + id));
                                back = false;
                            }
                        }
                        else
                        {
                            nodes.pop_back();
                        }
                    }


                }
                return nearests;
            }
            /**
             * @brief print the tree
             */
            void print()
            {
                std::cout << "POS: " << "\tNODE:" << "\tLEFT: " << "\tRIGHT:" << std::endl;
                int  i  = 0;
                for(nodeIt it = m_nodelist.begin(); it != m_nodelist.end(); ++it)
                {
                    std::cout << i++;
                    std::cout << "\t(";
                    for(int i = 0; i < (*it)->dim(); ++i)
                    {
                        std::cout << (*it)->data()[i];
                        if(i != (*it)->dim() - 1){
                            std::cout << ",";
                        }
                    }
                    std::cout << ")";

                    std::cout << "\t" << (*it)->left << "\t" << (*it)->right << std::endl;
                }
            }

        private:
            int m_dim;
            int m_size;
            int m_nodeList;
            int m_dir;
            int m_id;
            KdNode<T> *m_root;
            std::vector< KdNode<T> *> m_nodelist;
            typedef typename std::vector<T>::const_iterator constIt;
            typedef typename std::vector< KdNode<T> *>::iterator nodeIt;
            typedef typename std::list< KdNode<T> *> list;

        private:
            /**
             * @brief squareDistance distance between two different points
             * @param _pos1 point 1
             * @param _pos2 point 2
             * @return the distance
             */
            T squareDistance(const std::vector<T> _pos1, const std::vector<T> _pos2)
            {
                T sqDist = T(0);
                constIt itPos1, itPos2;
                for(itPos1 = _pos1.begin(), itPos2 = _pos2.begin();
                    itPos1 != _pos1.end(); ++itPos1, ++itPos2)
                {
                    sqDist += (*itPos1 - *itPos2) * (*itPos1 - *itPos2);
                }
                return sqDist;
            }

    };
}

#endif
