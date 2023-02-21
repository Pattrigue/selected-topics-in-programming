#ifndef SESSION5_BASE_H
#define SESSION5_BASE_H


class Base {
public:
    int value() const { return m_value; }
    
    virtual void increment() = 0;
    
    void decrement();
protected:
    int m_value ;
};


#endif
