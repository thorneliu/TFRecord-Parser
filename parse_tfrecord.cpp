#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "example.pb.h"
using namespace std;

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <streambuf>
#include "example.pb.h"
#include "keys.h"
#include <vector>
using namespace std;

// Iterates though all feature in the example and print them.
void ListEntry(const tensorflow::Example& example) {
    auto features = example.features();
    ostringstream oss;

    // all feature is const ::PROTOBUF_NAMESPACE_ID::Map<std::string, ::tensorflow::Feature>
    auto& all_feature_map = features.feature();
    for (auto& key : vecKeys)
    {
        if (0 == all_feature_map.count(key)) continue;
        auto& cur_feature_value = all_feature_map.at(key);

        if(cur_feature_value.has_bytes_list()) {
            auto& bytes_list = cur_feature_value.bytes_list();
            oss << bytes_list.value_size() << " ";
            for (auto& val : bytes_list.value())
            {
                oss << val << " ";
            }
        }

        if(cur_feature_value.has_int64_list()) {
            auto& int64_list = cur_feature_value.int64_list();
            oss << int64_list.value_size() << " ";
            for (auto& val : int64_list.value())
            {
                oss << val << " ";
            }
        }

        if(cur_feature_value.has_float_list()) {
            auto& float_list = cur_feature_value.float_list();
            oss << float_list.value_size() << " ";
            for (auto& val : float_list.value())
            {
                oss << val << " ";
            }
        }
    }

    cout << oss.str() << std::endl;
}

int main(int argc, char* argv[]) {
    char buffer[50000];
    uint64_t length = 0;
    int crc1 = 0, crc2 = 0;
    int i = 0;
    tensorflow::Example example;
    while (cin)
    {
        cin.read((char *)(&length), sizeof(length));
        if (!cin) break;
        //cin.read((char*)(&crc1), sizeof(crc1));
        //if (!cin) break;
        cin.read(buffer, length + 8);
        //if (!cin) break;
        //cin.read((char*)(&crc2), sizeof(crc2));

        if (example.ParseFromArray((void*)(buffer + 4), length)) {
            ListEntry(example);
        }
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
