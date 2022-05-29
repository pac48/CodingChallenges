#include <iostream>
#include <cstring>
#include "vector"
#include <concepts>

template<typename T1, typename T2>
concept Addable = requires (T1 x, T2 y) { x + y; }; // requires-expression

template<typename T1, typename T2>
concept Multable = requires (T1 x, T2 y) { x * y; }; // requires-expression


template <typename T>
class FunctionalArrayOperator{

private:
    unsigned char* data;
    int size;
    int sizeofElement;

public:
    explicit FunctionalArrayOperator(const std::vector<T>& inputIn){
        size = inputIn.size();
        sizeofElement = sizeof(T);
        data = (unsigned char*) malloc(sizeofElement*size);
        memcpy(data, inputIn.data(), size*sizeofElement);
    }

    explicit FunctionalArrayOperator(unsigned char* dataIn, int sizeIn, int sizeofElementIn){
        size = sizeIn;
        sizeofElement = sizeofElementIn;
        data = dataIn;
    }

private:
    template <typename T2, typename std::enable_if_t<std::is_arithmetic_v<T2>, bool> = true>
    static void elementMult(T* element, T2 val, T2* res){
        *res = (T2) (*element * val);
    }

    template <typename T2>
    static void elementAdd(T* element, T2 val, T2* res){
        *res = (T2) (*element + val);
    }

    static void elementPrintf(T* element, const char * fmt){
        printf(fmt, *element);
    }

    void checkSize(int sizeofNewElement){
        if (sizeofElement <= sizeofNewElement){
            auto newData = (unsigned char*) malloc(sizeofNewElement*size);
            for (int i=0 ; i < size; i++){
                auto tmp = newData+i*sizeofNewElement;
                *((T*) tmp) = *((T*) (data+i*sizeofElement));
            }
            free(data);
            data = newData;
            sizeofElement = sizeofNewElement;
        }
    }

    template <typename T2>
    void writeFunc(void (func)(T*, T2, T2*), T2 val){
        int ind = 0;
        while (ind < size*sizeofElement){
            T* element1 = (T*) (data + ind);
            T2* res = (T2*) (data + ind);
            func(element1, val, res);
            ind += sizeofElement;
        }
    }

    template <typename T2>
    void readFunc(void (func)(T*, T2), T2 val) const{
        int ind = 0;
        while (ind < size*sizeofElement){
            T* element1 = (T*) (data + ind);
            func(element1, val);
            ind += sizeofElement;
        }
    }

public:

    template <typename T2>
    requires Addable<T, T2>
    FunctionalArrayOperator<T2> add(T2 n){
        checkSize(sizeof(T2));
        writeFunc<T2>(elementAdd, n);
        FunctionalArrayOperator<T2> out = FunctionalArrayOperator<T2>(data, size, sizeofElement);
        return out;
    }

    template <typename T2>
    requires Multable<T, T2>
    FunctionalArrayOperator<T2> mult(T2 n){
        checkSize(sizeof(T2));
        writeFunc<T2>(elementMult, n);
        FunctionalArrayOperator<T2> out = FunctionalArrayOperator<T2>(data, size, sizeofElement);
        return out;

    }
//
//    FunctionalArrayOperator& extract(T (func)(T)){
//        for (T & i : data){
//            i = func(i);
//        }
//        return *this;
//    }

    FunctionalArrayOperator print(const char * fmt, const char *terminator="\n") const{
        readFunc(elementPrintf, fmt);
        printf("%s", terminator);
        return *this;
    }

    void compressMemory(){
        int sizeofNewElement = sizeof(T);

        if (sizeofElement != sizeofNewElement){
            for (int i=0 ; i < size; i++){
                auto ref = data+i*sizeofNewElement;
                *((T*) ref) = *((T*)(data+i*sizeofElement));
            }
            sizeofElement = sizeofNewElement;
        }
    }

    std::vector<T> terminate(){
        compressMemory();
        return std::vector<T>((T*) data, (T*) (data + size*sizeofElement));
    }
};

//template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>> >

template<typename T>
struct myType{

    T num = 0;

T operator+(const T & x) const{
        return num+x;
}

operator T() const { return num; }

};

template <typename T>
T operator+(const T & x, const myType<T> & me) {
    return x+me.num;
}

template <typename T>
T operator+(const myType<T> & me, const T & x) {
    return x+me.num;
}


int main() {
    std::vector<int> input = {1, 2, 3, 4, 5};

    FunctionalArrayOperator<int> functionalArray(input);

    auto vec = functionalArray.print("%d, ").add(0.2).print("%f, ").mult<float>(-1).print("%f, ").terminate();

    return 0;

}
