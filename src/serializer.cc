#include "serializer.h"

template <class T>
FileSerializer<T>::FileSerializer(const T& tc)
{
    task_container = tc;
}

template <class T>
FileSerializer<T>::~FileSerializer()
{

}

template <class T>
std::string FileSerializer<T>::operator()()
{

}

template <class T>
std::string FileSerializer<T>::getOutput()
{
    std::pair<std::string, std::string> p;

    for (T::const_iterator i=task_container.begin();
         i != task_container.end();
         ++i)
    {
        p = i->getConfigPair();
    }
}

