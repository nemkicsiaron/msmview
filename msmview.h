#ifndef MSMVIEW_H
#define MSMVIEW_H

#include <set>
#include <iterator>

template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class multisets_merge_view
{
private:
    std::multiset<T,Compare,Alloc> fstorigin;
    std::multiset<T,Compare,Alloc> sndorigin;
    std::multiset<T,Compare,Alloc>* fst;
    std::multiset<T,Compare,Alloc>* snd;
public:
    multisets_merge_view( std::multiset<T,Compare,Alloc>& param1, std::multiset<T,Compare,Alloc>& param2 ) : fstorigin(param1), sndorigin(param2), fst(&param1), snd(&param2)
    {
        typename std::multiset<T,Compare,Alloc>::iterator it1 = fst->begin();
        typename std::multiset<T,Compare,Alloc>::iterator it2 = snd->begin();

    
        for( ; it1 != fst->end() && it2 != snd->end(); ++it1, ++it2)
        {
            if( Compare{}(*it2,*it1) )
            {
                const T smol = *it2;
                const uint16_t howmanysm = snd->count(smol);
                snd->erase(smol);
                for(uint16_t i = 0; i < howmanysm; ++i)
                    fst->insert(smol);

                const T larg = *it1;
                const uint16_t howmanylg = fst->count(larg);
                fst->erase(larg);
                for(uint16_t i = 0; i < howmanylg; ++i)
                    snd->insert(larg);
            }
        }
    }
    ~multisets_merge_view()
    {
        fst = &fstorigin;
        snd = &sndorigin;
        /*
        delete fst;
        delete snd;
        */
    }

    const unsigned count( const T& elem ) const
    {
        return fst->count(elem) + snd->count(elem);
    }

    const unsigned size() const
    {
        return fst->size() + snd->size();
    }
};

#endif