#ifndef _JUICE_H_
#define _JUICE_H_

template<typename output_policy_t = lemon::output::cout> class juice : public lemon::test<output_policy_t> {
public:
    juice(const char* object, const char* method) 
        : object_(object), method_(method)
    {
        // increase indentation
        if (indent.empty())
            indent.append(1, '-');
        //else if (indent.size() > 1)
        //    indent.insert(indent.begin(), ' ');
        else
            indent.insert(indent.begin(), '+');

        diag(3, indent.c_str(), object_.c_str(), method_.c_str());
    }
    ~juice() {
        //diag(3, indent.c_str(), object_.c_str(), method_.c_str());

        // remove indentation
        indent.erase(indent.begin());
    }
private:
    static std::string indent;
    std::string object_;
    std::string method_;
};

std::string juice<>::indent;

#define IN InstanceName()
#define EN(name) juice<> j(IN, #name);

#endif