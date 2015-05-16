#ifndef _KDNODE_HPP_
#define _KDNODE_HPP_

#include <iostream>
#include <vector>

namespace Kd
{
    template<class T>
    class KdNode
    {
        public:
            /**
             * @brief KdNode<T> a new object KdNode
             * @param _p coordinates
             * @param _dir direction
             * @param _id id of the node
             */
            KdNode<T>(const std::vector<T> &_p, const int &_dir, const int &_id)
                : m_id(_id), m_dir(_dir)
            {
                m_data = NULL;
                setData(_p);
                left = right = -1;
            }
            /**
              * @brief Destructor
              */
            ~KdNode<T>()
            {
                if(m_data != NULL)
                {
                    delete m_data;
                }
            }
            /**
             * @brief data get the coordinates
             * @return a vector of coordinates
             */
            inline std::vector<T> data()
            {
                vec.clear();
                for(int i = 0; i < m_dim; ++i)
                {
                    vec.push_back(m_data[i]);

                }

                return vec;
            }
            /**
             * @brief setData set coordinates
             * @param _p coordinates
             */
            inline void setData(const std::vector<T> &_p)
            {
                if(m_data != NULL)
                {
                    delete m_data;
                }
                m_dim = int(_p.size());
                m_data = new T[sizeof(T) * m_dim];
                constIt it;
                int i = 0;
                for(it = _p.begin(); it != _p.end(); ++it)
                {
                    *(m_data + i) = *it;
                    ++i;
                }
            }
            /**
             * @brief dir return the direction
             * @return the direction
             */
            inline int dir() const
            {
                return m_dir;
            }
            /**
             * @brief setDir set direction
             * @param _dir diretction
             */
            inline void setDir(const int &_dir)
            {
                m_dir = _dir;
            }
            /**
             * @brief dim return the dimension of the node
             * @return the dimension
             */
            inline int dim() const
            {
                return m_dim;
            }
            /**
             * @brief setDim set the dimension of the node
             * @param _dim the dimension
             */
            inline void setDim(const int &_dim)
            {
                m_dim = _dim;
            }
            /**
             * @brief operator = copy a Kdnode in another
             * @param node the node to copy
             * @return the new node
             */
            KdNode<T> &operator =(const KdNode<T> *node)
            {
                setData(node->data());
                left = node->left;
                right = node->right;
                m_dir = node->dir();
            }
            /**
             * @brief operator == compare two nodes
             * @param node to compare
             * @return true or false
             */
            bool &operator ==(const KdNode<T> *node)
            {
                return isDataEqual(node);
            }
            /**
             * @brief id return the id of the node
             * @return the id of the node
             */
            inline int id() const
            {
                return m_id;
            }
            int left;
            int right;
        private:
            /**
             * @brief isDataEqual compare if two positions are equal
             * @param node position to compare
             * @return true or false
             */
            bool isDataEqual(const KdNode<T> *node)
            {
                for(int i = 0; i < m_dim; ++i)
                {
                    if(m_data[i] != node->data()[i])
                    {
                        return false;
                    }
                }
                return true;
            }

            int m_dir;
            int m_dim;
            int m_id;
            std::vector<T> vec;
            T *m_data;
            typedef typename std::vector<T>::const_iterator constIt;
    };

}


#endif
