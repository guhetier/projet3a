#ifndef BUCKET_HPP
#define BUCKET_HPP

template<typename K, typename V>
class Bucket {
public:

    virtual ~Bucket();

    virtual void insert (const K& key, const V& val) =0;
    virtual V get (const K& key) const =0;
    virtual V remove (const K& key) =0;

    //To-do : Add iterators
};

#endif
