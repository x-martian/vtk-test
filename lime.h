#ifndef LIME_H_
#define LIME_H_

namespace lime {
    /// represent an intance of a class
    template <class T> class meta
    {
    public:
        meta(const char* name) {
            strncpy_s(instanceName, 16, name, 16);
        }

    private:
        char instanceName[16];
    };
}
#endif // LIME_H_
