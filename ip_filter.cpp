#include "ip_filter_class.h"

using namespace std;

void intro() {
    cout << "\nПрограмма из стандартного ввода читает данные. Данные хранятся построчно. Каждая строка\nсостоит из трех полей, разделенных одним символом табуляции, и завершается символом конца\nстроки. Формат строки:\ntext1 \\t text2 \\t text3 \\n\nПоля text2 и text3 игнорируются. Поле text1 имеет следующую структуру (ip4 address):\nn1.n2.n3.n4\nгде n1..4 – целое число от 0 до 255.\nНапример: \n\t113.162.145.156	111	0\n\t157.39.22.224	5	6\n\t79.180.73.190	2	1\n\t...\n" << endl;
    cout << "\nИли данные считываются из файла. Например: ./ip_filter ip_filter.tsv\n" << endl;
}

int main(int argc, char** argv)
{
    try
    {
        istream* in_stream = nullptr;
        if (argc == 2) {
            in_stream = dynamic_cast<istream*>(*make_unique<ifstream*>(new ifstream(argv[1], ios_base::in)));
        }
        else if (argc == 1) {
            in_stream = &cin;
        }
        else {
            intro(); exit(-1);
        }

        auto IpFilterInstance = IpFilter(in_stream);
        
        IpFilterInstance.reverse_lexicographically_sort();
        IpFilterInstance.filter(1);
        IpFilterInstance.filter(46, 70);
        IpFilterInstance.filter_any(46);
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
