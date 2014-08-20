#include "SExprReader.hpp"

#include <fstream>


void describe_object(const SExprObject& obj, int indent = 0);


int main(int argc, const char** argv)
{
    std::ifstream in("countries.sx");
    SExprReader reader(in);
    SExprObject* obj;

    reader.read(&obj);
    while (obj != NULL)
    {
        describe_object(*obj, 4);
        delete obj;
        reader.read(&obj);
    }
    
    return 0;
}

void describe_object(const SExprObject& obj, int indent)
{
    for (int i = 0; i < indent; i++)
    {
        std::cout << " ";
    }

    std::cout << "object of type '";
    switch (obj.get_type())
    {
    case SExprObject::TYPE_STRING:
    {
        std::cout << "string': \"" << obj.get_string() << "\"\n";
        break;
    }
    case SExprObject::TYPE_SYMBOL:
    {
        std::cout << "symbol': " << obj.get_symbol_name() << "\n";
        break;
    }
    case SExprObject::TYPE_NUMBER:
    {
        std::cout << "number': " << obj.get_number() << "\n";
        break;
    }
    case SExprObject::TYPE_LIST:
    {
        const SExprObject::SExprObjectList& list = obj.get_list();
        std::cout << "list' of length " << list.size() << ":\n";
        for (SExprObject::SExprObjectList::const_iterator i = list.begin(); i != list.end(); i++)
        {
            describe_object(**i, indent + 4);
        }
        break;
    }
    default:
    {
        std::cout << "Object of unknown type!\n";
    }
    }
}

