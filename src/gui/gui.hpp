#include <vector>
using namespace std;

class GUI
{
    public:
        GUI();

        void add_element(shared_ptr<Element>);
    private:
        vector<shared_ptr<Elements>> _elements;
};
