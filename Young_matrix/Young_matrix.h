#ifndef YOUNG_MATRIX_H_INCLUDED
#define YOUNG_MATRIX_H_INCLUDED
class Position
{
private:
    int rrow;
    int lline;
public:
    Position(int r=0,int l=0):rrow(r),lline(l) {};
    int& pr() {return rrow;}
    int& pl() {return lline;}
    const int& pr() const  {return rrow;}
    const int& pl() const {return lline;}
    bool operator!=(const Position pp)
    {
        if(pp.rrow==rrow&&pp.lline==lline)
            return false;
        else
            return true;
    }
};
class Young_matrix
{
private:
    int** p;
    int row;
    int line;
    Position pos;
    void destroy();
public:
    Young_matrix(int* a,int n,int r,int l);
    Young_matrix(const Young_matrix& m);
    Young_matrix& operator=(const Young_matrix& m);
    ~Young_matrix() {destroy();}
    int Young_extract_min();
    void Young_min_heapify(Position i);
    void insert_ele(int x);
    void Young_increase_key(Position ppp,int key);
    bool find_ele(int x);
    void display();
    friend void Young_sort(Young_matrix y,int* a,int n);
};


#endif // YOUNG_MATRIX_H_INCLUDED
