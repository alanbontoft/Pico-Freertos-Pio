class MathClass
{
private:
    /* data */
    int _value;
public:
    MathClass(int i);
    ~MathClass();

    int multiply(int a);
    void inc(void);
    void dec(void);

    int value() { return _value; }
    void setValue(int i) { _value = i; }
};